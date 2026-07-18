#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "2205040_general.h"

using namespace std;

ostringstream out;

class SymbolInfo {
    string name;
    string type;
    string extraInfo;
    //SymbolInfo* next;  // dead code — never read

public:
    SymbolInfo(string name, string type, string extraInfo = "") {
        this->name = name ; 
        this->type = type;
        this->extraInfo = extraInfo;
    }

    string getName() { return name; }
    string getType() { return type; }
    string getExtraInfo() { return extraInfo; }
    //SymbolInfo* getNext() { return next; }      // dead code
    //void setNext(SymbolInfo* n) { next = n; }   // dead code
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

    int getBucketIndex(const string& key) {
        return SDBMHash(key);
    }

    int getTotalBuckets() {
        return total_buckets;
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

    bool Insert(string name, string type, string extra = "") {
        unsigned int hash = SDBMHash(name);
        auto& bucket = table[hash];
        int bucketIdx = hash + 1;

        int pos = 0;
        bool found = false;

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            pos++;
            if (it->getName() == name) {
                found = true;
                break;
            }
        }

        if (found) {
            out << "\t'" << name << "' already exists in the current ScopeTable" << endl;
            return false;
        }

        bucket.push_back(SymbolInfo(name, type, extra));
        out << "\tInserted in ScopeTable# " << scope_id
            << " at position " << bucketIdx << ", " << pos + 1 << endl;
        return true;
    }

    SymbolInfo* Lookup(string name, int& outBucket, int& outPos) {
        unsigned int hash = SDBMHash(name);
        auto& bucket = table[hash];
        outBucket = hash + 1;
        outPos = 1;

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getName() == name) {
                return &(*it);
            }
            outPos++;
        }

        return nullptr;
    }

    bool Delete(string name) {
        unsigned int hash = SDBMHash(name);
        int bucketIdx = hash + 1;
        int pos;

        if (table[hash].remove(name, pos)) {
            out << "\tDeleted '" << name
                << "' from ScopeTable# " << scope_id
                << " at position " << bucketIdx
                << ", " << pos << endl;
            return true;
        }

        out << "\tNot found in the current ScopeTable" << endl;
        return false;
    }

    void DeleteByType(const string& type) {
        for (int i = 0; i < total_buckets; i++) {
            auto& bucket = table[i];
            int bucketIdx = i + 1;

            while (true) {
                int pos = 0;
                string name;
                bool found = false;

                for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                    pos++;
                    if (it->getType() == type) {
                        name = it->getName();
                        found = true;
                        break;
                    }
                }

                if (!found) break;

                int removePos;
                bucket.remove(name, removePos);
                out << "\tDeleted '" << name << "' from ScopeTable# " << scope_id << " at position " << bucketIdx << ", " << pos << endl;
            }
        }
    }

    void Clear() {
        for (int i = 0; i < total_buckets; i++) {
            auto& bucket = table[i];
            int bucketIdx = i + 1;

            while (true) {
                string name;
                bool found = false;

                for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                    name = it->getName();
                    found = true;
                    break;
                }

                if (!found) break;

                int removePos;
                bucket.remove(name, removePos);
                out << "\tDeleted '" << name << "' from ScopeTable# " << scope_id << " at position " << bucketIdx << ", " << removePos << endl;
            }
        }
    }

    int Count(const string& name) {
        int count = 0;
        unsigned int hash = SDBMHash(name);
        auto& bucket = table[hash];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getName() == name) count++;
        }
        return count;
    }

    bool Find(const string& search) {
        bool any = false;
        for (int i = 0; i < total_buckets; i++) {
            auto& bucket = table[i];
            bucket.for_each([&](SymbolInfo& si) {
                if (si.getName().find(search) != string::npos) {
                    out << "\tFound in ScopeTable# " << scope_id << ": " << si.getName() << " (" << si.getType() << ")" << endl;
                    any = true;
                }
            });
        }
        return any;
    }

    void ReplaceAllInScope(const string& search, const string& replace, bool& anyFound) {
        for (int i = 0; i < total_buckets; i++) {
            auto& bucket = table[i];
            int bucketIdx = i + 1;

            while (true) {
                string oldName, oldType, oldExtra;
                bool found = false;

                for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                    if (it->getName().find(search) != string::npos) {
                        oldName = it->getName();
                        oldType = it->getType();
                        oldExtra = it->getExtraInfo();
                        found = true;
                        break;
                    }
                }

                if (!found) break;

                string newName = oldName;
                size_t p = 0;
                while ((p = newName.find(search, p)) != string::npos) {
                    newName.replace(p, search.length(), replace);
                    p += replace.length();
                }

                unsigned int newHash = SDBMHash(newName);
                bool conflict = false;
                for (auto it = table[newHash].begin(); it != table[newHash].end(); ++it) {
                    if (it->getName() == newName) {
                        conflict = true;
                        break;
                    }
                }

                int removePos;
                bucket.remove(oldName, removePos);

                if (conflict) {
                    unsigned int oldHash = SDBMHash(oldName);
                    table[oldHash].push_back(SymbolInfo(oldName, oldType, oldExtra));
                    out << "\tConflict: '" << oldName << "' -> '" << newName << "' skipped in ScopeTable# " << scope_id << endl;
                } else {
                    table[newHash].push_back(SymbolInfo(newName, oldType, oldExtra));
                    anyFound = true;
                    out << "\tDeleted '" << oldName << "' from ScopeTable# " << scope_id << " at position " << bucketIdx << ", " << removePos << endl;
                    int insertPos = 1;
                    for (auto it = table[newHash].begin(); it != table[newHash].end(); ++it) {
                        if (it->getName() == newName && it->getType() == oldType) break;
                        insertPos++;
                    }
                    out << "\tInserted in ScopeTable# " << scope_id << " at position " << (newHash + 1) << ", " << insertPos << endl;
                }
            }
        }
    }

    void Print(int depth, bool showAll) {
        for (int j = 0; j < depth; j++) out << "\t";
        out << "ScopeTable# " << scope_id << endl;

        for (int i = 0; i < getTotalBuckets(); i++) {
            for (int j = 0; j < depth; j++) out << "\t";
            out << (i + 1) << "--> ";

            getBucketByIndex(i).for_each([&](SymbolInfo& si) {
                out << "<" << si.getName() << "," << si.getType();
                if (!si.getExtraInfo().empty()) out << "," << si.getExtraInfo();
                out << "> ";
            });

            out << endl;
        }

        if (showAll && parentScope) {
            parentScope->Print(depth + 1, true);
        }
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

    bool Insert(string name, string type, string extra = "") {
        if (!currentScope) return false;
        return currentScope->Insert(name, type, extra);
    }

    bool Remove(string name) {
        if (!currentScope) return false;
        return currentScope->Delete(name);
    }

    SymbolInfo* Lookup(string name) {
        ScopeTable* sc = currentScope;
        int bucket = 0, pos = 0;
        while (sc) {
            SymbolInfo* found = sc->Lookup(name, bucket, pos);
            if (found) {
                out << "\t'" << name << "' found in ScopeTable# " << sc->getScopeId() << " at position " << bucket << ", " << pos << endl;
                return found;
            }
            sc = sc->getParentScope();
        }
        out << "\t'" << name << "' not found in any of the ScopeTables" << endl;
        return nullptr;
    }

    bool isRootScope() {
        return currentScope && !currentScope->getParentScope();
    }

    void DeleteType(string type) {
        if (!currentScope) return;
        ScopeTable* sc = currentScope;
        while (sc) {
            sc->DeleteByType(type);
            sc = sc->getParentScope();
        }
    }

    void DeleteCurrentType(string type) {
        if (currentScope) currentScope->DeleteByType(type);
    }

    void Clear() {
        if (currentScope) currentScope->Clear();
    }

    int Count(string name) {
        int total = 0;
        ScopeTable* sc = currentScope;
        while (sc) {
            total += sc->Count(name);
            sc = sc->getParentScope();
        }
        return total;
    }

    bool Rename(string oldName, string newName) {
        ScopeTable* sc = currentScope;
        while (sc) {
            int bucket = 0, pos = 0;
            SymbolInfo* si = sc->Lookup(oldName, bucket, pos);
            if (si) {
                // Check conflict in this scope
                int dummyBucket = 0, dummyPos = 0;
                SymbolInfo* conflict = sc->Lookup(newName, dummyBucket, dummyPos);
                if (conflict) {
                    out << "\t'" << newName << "' already exists in the current ScopeTable" << endl;
                    return false;
                }

                string type = si->getType();
                string extra = si->getExtraInfo();
                sc->Delete(oldName);
                sc->Insert(newName, type, extra);
                return true;
            }
            sc = sc->getParentScope();
        }
        out << "\t'" << oldName << "' not found in any of the ScopeTables" << endl;
        return false;
    }

    void SearchAndReplaceAll(string oldName, string newName) {
        bool anyFound = false;
        ScopeTable* sc = currentScope;
        while (sc) {
            int bucket = 0, pos = 0;
            SymbolInfo* si = sc->Lookup(oldName, bucket, pos);
            if (si) {
                anyFound = true;
                int dummyBucket = 0, dummyPos = 0;
                SymbolInfo* conflict = sc->Lookup(newName, dummyBucket, dummyPos);
                if (conflict) {
                    out << "\tConflict: '" << oldName << "' -> '" << newName << "' skipped in ScopeTable# " << sc->getScopeId() << endl;
                } else {
                    string type = si->getType();
                    string extra = si->getExtraInfo();
                    sc->Delete(oldName);
                    sc->Insert(newName, type, extra);
                }
            }
            sc = sc->getParentScope();
        }
        if (!anyFound) {
            out << "\t'" << oldName << "' not found in any of the ScopeTables" << endl;
        }
    }

    void Find(const string& search) {
        bool anyFound = false;
        ScopeTable* sc = currentScope;
        while (sc) {
            if (sc->Find(search)) anyFound = true;
            sc = sc->getParentScope();
        }
        if (!anyFound) {
            out << "\tNo matches found for '" << search << "'" << endl;
        }
    }

    void ReplaceAll(const string& search, const string& replace) {
        bool anyFound = false;
        ScopeTable* sc = currentScope;
        while (sc) {
            sc->ReplaceAllInScope(search, replace, anyFound);
            sc = sc->getParentScope();
        }
        if (!anyFound) {
            out << "\tNo matches found for '" << search << "'" << endl;
        }
    }

    void PrintCurrent() {
        if (currentScope) currentScope->Print(1, false);
    }

    void PrintAll() {
        if (currentScope) currentScope->Print(1, true);
    }

    ~SymbolTable() {
        while (currentScope) ExitScope();
    }
};

void processCommand(string line, SymbolTable& st) {
    stringstream ss(line);
    string cmd, token1, token2;
    ss >> cmd;

    if (cmd == "I") {
        ss >> token1 >> token2;
        if (token1.empty() || token2.empty()) {
            out << "\tNumber of parameters mismatch for the command I" << endl;
            return;
        }
        string remaining, word;
        while (ss >> word) {
            if (!remaining.empty()) remaining += ",";
            remaining += word;
        }
        if (token2 == "FUNCTION") {
            if (!remaining.empty()) {
                size_t first_comma = remaining.find(',');
                string retType = remaining.substr(0, first_comma);
                string params = remaining.substr(first_comma + 1);
                string formattedParams = "(";
                stringstream pss(params);
                string p;
                while (getline(pss, p, ',')) {
                    if (formattedParams != "(") formattedParams += ",";
                    formattedParams += p;
                }
                formattedParams += ")";
                st.Insert(token1, token2, retType + "<==" + formattedParams);
                return;
            }
        } else if (token2 == "STRUCT" || token2 == "UNION") {
            string formatted = "{";
            stringstream pss(remaining);
            string type, name;
            bool first = true;
            while (getline(pss, type, ',') && getline(pss, name, ',')) {
                if (!first) formatted += ",";
                formatted += "(" + type + "," + name + ")";
                first = false;
            }
            formatted += "}";
            st.Insert(token1, token2, formatted);
            return;
        }
        st.Insert(token1, token2, remaining);
    } else if (cmd == "L") {
        ss >> token1;
        if (ss >> token2) {
            out << "\tNumber of parameters mismatch for the command L" << endl;
        } else {
            st.Lookup(token1);
        }
    } else if (cmd == "D") {
        if (!(ss >> token1)) {
            out << "\tNumber of parameters mismatch for the command D" << endl;
        } else {
            st.Remove(token1);
        }
    } else if (cmd == "S") {
        st.EnterScope();
    } else if (cmd == "E") {
        st.ExitScope();
    } else if (cmd == "P") {
        ss >> token1;
        if (token1 == "C") st.PrintCurrent();
        else if (token1 == "A") st.PrintAll();
    } else if (cmd == "DT") {
        if (!(ss >> token1)) {
            out << "\tNumber of parameters mismatch for the command DT" << endl;
        } else {
            st.DeleteType(token1);
        }
    } else if (cmd == "DD") {
        if (!(ss >> token1)) {
            out << "\tNumber of parameters mismatch for the command DD" << endl;
        } else {
            st.DeleteCurrentType(token1);
        }
    } else if (cmd == "RN") {
        ss >> token1 >> token2;
        if (token1.empty() || token2.empty()) {
            out << "\tNumber of parameters mismatch for the command RN" << endl;
        } else {
            st.Rename(token1, token2);
        }
    } else if (cmd == "COUNT") {
        if (!(ss >> token1)) {
            out << "\tNumber of parameters mismatch for the command COUNT" << endl;
        } else {
            int c = st.Count(token1);
            out << "\t'" << token1 << "' found in " << c << " ScopeTable(s)" << endl;
        }
    } else if (cmd == "CLEAR") {
        st.Clear();
    } else if (cmd == "SRA") {
        ss >> token1 >> token2;
        if (token1.empty() || token2.empty()) {
            out << "\tNumber of parameters mismatch for the command SRA" << endl;
        } else {
            st.SearchAndReplaceAll(token1, token2);
        }
    } else if (cmd == "FIND") {
        if (!(ss >> token1)) {
            out << "\tNumber of parameters mismatch for the command FIND" << endl;
        } else {
            st.Find(token1);
        }
    } else if (cmd == "REPLACEALL") {
        ss >> token1 >> token2;
        if (token1.empty() || token2.empty()) {
            out << "\tNumber of parameters mismatch for the command REPLACEALL" << endl;
        } else {
            st.ReplaceAll(token1, token2);
        }
    }
}

bool check_diff(string file1, string file2) {
    ifstream f1(file1), f2(file2);
    if (!f1.is_open() || !f2.is_open()) {
        cout << "\tCould not open one or both files" << endl;
        return true;
    }

    string l1, l2;
    int lineNum = 1;
    bool diffFound = false;

    while (getline(f1, l1) && getline(f2, l2)) {
        if (l1 != l2) {
            cout << "\tDifference at line " << lineNum << ":" << endl;
            cout << "\tFile1: " << l1 << endl;
            cout << "\tFile2: " << l2 << endl;
            diffFound = true;
        }
        lineNum++;
    }

    while (getline(f1, l1)) {
        cout << "\tExtra line in " << file1 << " at line " << lineNum << ": " << l1 << endl;
        diffFound = true;
        lineNum++;
    }

    while (getline(f2, l2)) {
        cout << "\tExtra line in " << file2 << " at line " << lineNum << ": " << l2 << endl;
        diffFound = true;
        lineNum++;
    }

    if (!diffFound) {
        cout << "\tFiles are identical (" << (lineNum - 1) << " lines)" << endl;
    }

    return diffFound;
}

int main(int argc, char* argv[]) {
    string inputFile = (argc >= 2) ? argv[1] : "sample_input.txt";
    string outputFile = (argc >= 3) ? argv[2] : "new_output.txt";

    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "Unable to open " << inputFile << endl;
        return 1;
    }

    string line;
    getline(inFile, line);
    int bucketSize = stoi(line);
    if (bucketSize <= 0) {
        out << "\tInvalid bucket size " << bucketSize << ", defaulting to 1" << endl;
        bucketSize = 1;
    }

    {
        SymbolTable st(bucketSize);
        int cmdCount = 1;

        while (getline(inFile, line)) {
            if (line.empty()) continue;
            size_t end = line.find_last_not_of(" \t\n\r");
            if (end != string::npos) line = line.substr(0, end + 1);
            if (line[0] == 'Q') {
                out << "Cmd " << cmdCount << ": Q" << endl;
                break;
            }
            if (line[0] == 'E' && st.isRootScope()) continue;

            stringstream ss(line);
            string cmd;
            ss >> cmd;
            if (cmd == "P") {
                string sub;
                ss >> sub;
                if (sub != "C" && sub != "A") continue;
            } else if (cmd != "I" && cmd != "L" && cmd != "D" && cmd != "S" && cmd != "E"
                && cmd != "DT" && cmd != "DD" && cmd != "RN" && cmd != "COUNT"
                && cmd != "CLEAR" && cmd != "SRA" && cmd != "FIND" && cmd != "REPLACEALL") {
                continue;
            }

            out << "Cmd " << cmdCount << ": " << line << endl;
            processCommand(line, st);
            cmdCount++;
        }
    }

    ofstream fout(outputFile);
    fout << out.str();
    fout.close();

    cout << "--- Comparing with sample output ---" << endl;
   check_diff("sample_output.txt", outputFile);

    inFile.close();
    return 0;
}
