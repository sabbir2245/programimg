#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "2205040_general.h"

using namespace std;

ofstream fout;
ostringstream out;

class SymbolInfo {
    string name;
    int value;
    int declLine;
public:
    SymbolInfo(string name, int declLine) {
        this->name = name;
        value = 0;
        this->declLine = declLine;
    }

    string getName() { return name; }
    int getValue() { return value; }
    int getDeclLine() { return declLine; }
    void setValue(int v) { value = v; }
};

class ScopeTable {
    mylist<SymbolInfo>* table;
    int total_buckets;
    int scope_id;
    ScopeTable* parentScope;

    unsigned int SDBMHash(const string& str) {
        unsigned int h = 0;
        for (unsigned int i = 0; i < str.length(); i++) {
            h = ((str[i]) + (h << 6) + (h << 16) - h) % total_buckets;
        }
        return h;
    }

    mylist<SymbolInfo>& getBucket(const string& key) {
        return table[SDBMHash(key)];
    }

    mylist<SymbolInfo>& getBucketByIndex(int i) {
        return table[i];
    }

public:
    ScopeTable(int buckets, int id, ScopeTable* parent = nullptr) {
        total_buckets = buckets;
        scope_id = id;
        parentScope = parent;
        table = new mylist<SymbolInfo>[buckets];
        out << "\tScopeTable# " << scope_id << " created" << endl;
    }

    int getScopeId() { return scope_id; }
    ScopeTable* getParentScope() { return parentScope; }

    bool Insert(string name, int declLine) {
        auto& bucket = getBucket(name);
        int bucketIdx = SDBMHash(name) + 1;
        int pos = 0;
        bool found = false;

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            pos++;
            if (it->getName() == name) {
                found = true;
                break;
            }
        }

        if (found) return false;

        bucket.push_back(SymbolInfo(name, declLine));
        out << "\tInserted in ScopeTable# " << scope_id
            << " at position " << bucketIdx << ", " << pos + 1 << endl;
        return true;
    }

    SymbolInfo* Lookup(string name, int& outBucket, int& outPos) {
        auto& bucket = getBucket(name);
        outBucket = SDBMHash(name) + 1;
        outPos = 1;

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getName() == name) {
                return &(*it);
            }
            outPos++;
        }
        return nullptr;
    }

    ~ScopeTable() {
        delete[] table;
        out << "\tScopeTable# " << scope_id << " removed" << endl;
    }
};

class SymbolTable {
    ScopeTable* currentScope;
    int bucketSize;
    int scopeCounter;

public:
    SymbolTable(int bucketSize) {
        currentScope = nullptr;
        this->bucketSize = bucketSize;
        scopeCounter = 0;
        EnterScope();
    }

    void EnterScope() {
        scopeCounter++;
        currentScope = new ScopeTable(bucketSize, scopeCounter, currentScope);
    }

    void ExitScope() {
        if (!currentScope) return;
        ScopeTable* temp = currentScope;
        currentScope = currentScope->getParentScope();
        delete temp;
    }

    bool Insert(string name, int declLine) {
        if (!currentScope) return false;
        return currentScope->Insert(name, declLine);
    }

    SymbolInfo* Lookup(string name) {
        ScopeTable* sc = currentScope;
        int bucket = 0, pos = 0;
        while (sc) {
            SymbolInfo* found = sc->Lookup(name, bucket, pos);
            if (found) return found;
            sc = sc->getParentScope();
        }
        return nullptr;
    }

    // Lookup returning found scope + bucket/pos info, no printing
    SymbolInfo* LookupWithInfo(string name, ScopeTable*& outScope, int& outBucket, int& outPos) {
        ScopeTable* sc = currentScope;
        while (sc) {
            SymbolInfo* found = sc->Lookup(name, outBucket, outPos);
            if (found) { outScope = sc; return found; }
            sc = sc->getParentScope();
        }
        outScope = nullptr;
        return nullptr;
    }

    bool isRootScope() {
        return currentScope && !currentScope->getParentScope();
    }

    ScopeTable* getCurrentScope() { return currentScope; }

    int getCurrentScopeId() {
        return currentScope ? currentScope->getScopeId() : 0;
    }

    ~SymbolTable() {
        while (currentScope) ExitScope();
    }
};

int main(int argc, char* argv[]) {
    string inputFile = (argc >= 2) ? argv[1] : "code.txt";
    string outputFile = (argc >= 3) ? argv[2] : "new_output.txt";

    ifstream code(inputFile);
    if (!code) {
        cerr << "Unable to open " << inputFile << endl;
        return 1;
    }

    string line;
    getline(code, line);
    int bucketSize = stoi(line);
    if (bucketSize <= 0) bucketSize = 1;

    SymbolTable st(bucketSize);
    int lineNum = 1;

    while (getline(code, line)) {
        if (line.empty()) continue;
        lineNum++;

        stringstream ss(line);
        string opcode;
        ss >> opcode;

        if (opcode == "{") {
            st.EnterScope();
        } else if (opcode == "}") {
            st.ExitScope();
        } else if (opcode == "declare") {
            string var;
            ss >> var;

            int bucket = 0, pos = 0;
            ScopeTable* sc = st.getCurrentScope();
            SymbolInfo* found = sc ? sc->Lookup(var, bucket, pos) : nullptr;

            if (found) {
                out << "> ERROR in line " << lineNum << ": '" << var << "' already declared in this scope in line " << found->getDeclLine() << endl;
            } else {
                st.Insert(var, lineNum);
            }
        } else if (opcode == "set") {
            string var;
            int val;
            ss >> var >> val;

            SymbolInfo* si = st.Lookup(var);
            if (!si) {
                out << "> ERROR in line " << lineNum << ": '" << var << "' not found in any of the ScopeTables" << endl;
            } else {
                si->setValue(val);
                out << "> Set '" << var << "' = " << val << " in ScopeTable# " << st.getCurrentScopeId() << endl;
            }
        } else if (opcode == "+") {
            string dst, op1, op2;
            ss >> dst >> op1 >> op2;

            int bucket = 0, pos = 0;
            ScopeTable* sc = nullptr;

            SymbolInfo* sop1 = st.LookupWithInfo(op1, sc, bucket, pos);
            if (!sop1) {
                out << "> ERROR in line " << lineNum << ": '" << op1 << "' not found in any of the ScopeTables" << endl;
            } else {
                out << "\t'" << op1 << "' found in ScopeTable# " << sc->getScopeId() << " at position " << bucket << ", " << pos << endl;

                SymbolInfo* sop2 = st.LookupWithInfo(op2, sc, bucket, pos);
                if (!sop2) {
                    out << "> ERROR in line " << lineNum << ": '" << op2 << "' not found in any of the ScopeTables" << endl;
                } else {
                    out << "\t'" << op2 << "' found in ScopeTable# " << sc->getScopeId() << " at position " << bucket << ", " << pos << endl;

                    SymbolInfo* sdst = st.LookupWithInfo(dst, sc, bucket, pos);
                    if (!sdst) {
                        out << "> ERROR in line " << lineNum << ": '" << dst << "' not found in any of the ScopeTables" << endl;
                    } else {
                        out << "\t'" << dst << "' found in ScopeTable# " << sc->getScopeId() << " at position " << bucket << ", " << pos << endl;

                        int result = sop1->getValue() + sop2->getValue();
                        sdst->setValue(result);
                        out << "> Set '" << dst << "' = " << result << " in ScopeTable# " << st.getCurrentScopeId() << endl;
                    }
                }
            }
        } else if (opcode == "print") {
            string var;
            ss >> var;

            SymbolInfo* si = st.Lookup(var);
            if (si) {
                out << "> " << si->getValue() << endl;
            } else {
                out << "> ERROR in line " << lineNum << ": '" << var << "' not found in any of the ScopeTables" << endl;
            }
        }
    }

    ofstream fout(outputFile);
    fout << out.str();
    fout.close();

    code.close();
    return 0;
}
