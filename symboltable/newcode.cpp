// =============================================================================
// NEW CODE COLLECTION — extracted from A1/B1/C1 online solutions
// All additions build on top of 2205040_general.h (mylist<T> linked list)
// =============================================================================

#include <string>
#include <sstream>
#include "2205040_general.h"
using namespace std;
extern ostringstream out;

// =============================================================================
// 1. HIERARCHICAL SCOPE IDs  (A1 — replaces int scope_id)
// =============================================================================
// Instead of int scope_id, use string scope_id with a child_counter:
//   ScopeTable stores string scope_id + int child_counter
//   generateChildId() returns "scope_id.child_counter++"
//   SymbolTable constructor creates root scope with id "1"

// --- In ScopeTable class (replaces 'int scope_id'): ---
    string scope_id;
    int child_counter;

    // constructor changes:
    // ScopeTable(int buckets, string id, ScopeTable* parent = nullptr)
    //     : total_buckets(buckets), scope_id(id), child_counter(1), parentScope(parent)
    // { ... }

    string generateChildId() {
        return scope_id + "." + to_string(child_counter++);
    }

    // getScopeId() now returns string (not int)
    string getScopeId() { return scope_id; }

// --- In SymbolTable class: ---
    // constructor creates root "1" instead of EnterScope with int id
    // SymbolTable(int bucketSize) : currentScope(nullptr), bucketSize(bucketSize) {
    //     currentScope = new ScopeTable(bucketSize, "1", nullptr);
    // }

    void EnterScope() {
        string newId = currentScope->generateChildId();
        currentScope = new ScopeTable(bucketSize, newId, currentScope);
    }


// =============================================================================
// 2. MERGE COMMAND  (A1)
// =============================================================================

// --- In ScopeTable, add conflict-check helper: ---
    bool canInsert(const string& name) {
        auto& bucket = getBucket(name);
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getName() == name) return false;
        }
        return true;
    }

    // make getBucketByIndex and getTotalBuckets public:
    //   (move to public section in the class)
    // mylist<SymbolInfo>& getBucketByIndex(int i) { return table[i]; }
    // int getTotalBuckets() { return total_buckets; }

// --- In SymbolTable, add Merge(): ---
    bool Merge() {
        if (!currentScope || !currentScope->getParentScope()) return false;

        ScopeTable* child = currentScope;
        ScopeTable* parent = currentScope->getParentScope();

        bool conflict = false;
        for (int i = 0; i < bucketSize && !conflict; i++) {
            child->getBucketByIndex(i).for_each([&](SymbolInfo& si) {
                if (!parent->canInsert(si.getName())) {
                    out << "\tMerge failed: '" << si.getName()
                        << "' already exists in parent ScopeTable" << endl;
                    conflict = true;
                }
            });
        }
        if (conflict) return false;

        for (int i = 0; i < bucketSize; i++) {
            child->getBucketByIndex(i).for_each([&](SymbolInfo& si) {
                parent->Insert(si.getName(), si.getType(), si.getExtraInfo());
            });
        }

        currentScope = parent;
        out << "\tScopeTable# " << child->getScopeId()
            << " merged with ScopeTable# " << parent->getScopeId() << endl;
        delete child;
        return true;
    }

// --- In processCommand, handle 'M': ---
    // } else if (cmd == "M") {
    //     st.Merge();
    // }

// --- In main's command validation, add 'M': ---
    // } else if (cmd != "I" && cmd != "L" && cmd != "D" && cmd != "S"
    //            && cmd != "E" && cmd != "M") {
    //     continue;
    // }


// =============================================================================
// 3. MICKEY LANG — SymbolInfo with value/declLine  (B1)
// =============================================================================

// B1's SymbolInfo replaces type/extraInfo with integer value + declaration line:
class SymbolInfo_B1 {
    string name;
    int value;
    int declLine;
public:
    SymbolInfo_B1(string name, int declLine)
        : name(name), value(0), declLine(declLine) {}

    string getName() { return name; }
    int getValue() { return value; }
    int getDeclLine() { return declLine; }
    void setValue(int v) { value = v; }
};

// B1's ScopeTable::Insert takes (name, declLine) instead of (name, type, extra):
// bool Insert(string name, int declLine) { ... return false on conflict; ... }

// B1's SymbolTable::Lookup is quiet (no printing):
// SymbolInfo* Lookup(string name) { ... returns nullptr if not found; ... }

// B1's SymbolTable::LookupWithInfo returns scope + bucket/pos info:
// SymbolInfo* LookupWithInfo(string name, ScopeTable*& outScope,
//                             int& outBucket, int& outPos) { ... }

// B1's SymbolTable adds:
    ScopeTable* getCurrentScope() { return currentScope; }
    int getCurrentScopeId() {
        return currentScope ? currentScope->getScopeId() : 0;
    }

// B1 main loop — token-by-token each-line parsing:
// int main(int argc, char* argv[]) {
//     ...
//     SymbolTable st(bucketSize);
//     int lineNum = 1;
//     while (getline(code, line)) {
//         if (line.empty()) continue;
//         lineNum++;
//         stringstream ss(line); string opcode; ss >> opcode;
//
//         if (opcode == "{")  st.EnterScope();
//         else if (opcode == "}")  st.ExitScope();
//         else if (opcode == "declare") {
//             string var; ss >> var;
//             // check scope-level duplicate, else insert
//         }
//         else if (opcode == "set") {
//             string var; int val; ss >> var >> val;
//             // quiet lookup, set value or error
//         }
//         else if (opcode == "+") {
//             string dst, op1, op2;  ss >> dst >> op1 >> op2;
//             // lookup op1 -> lookup op2 -> lookup dst
//             // print found messages, then set dst = op1 + op2
//         }
//         else if (opcode == "print") {
//             string var; ss >> var;
//             // quiet lookup, print value or error
//         }
//     }
// }


// =============================================================================
// 4. SCOPE-LOCAL SYMBOLS  (C1)
// =============================================================================

// --- In SymbolInfo class, add scopeLocal flag: ---
    bool scopeLocal;

    // Constructor extended:
    // SymbolInfo(string name, string type, string extraInfo = "",
    //            bool scopeLocal = false)
    //     : name(name), type(type), extraInfo(extraInfo), scopeLocal(scopeLocal) {}

    bool isScopeLocal() { return scopeLocal; }

// --- In ScopeTable::Insert, accept scopeLocal parameter: ---
    // bool Insert(string name, string type, string extra = "",
    //             bool scopeLocal = false) {
    //     ...
    //     bucket.push_back(SymbolInfo(name, type, extra, scopeLocal));
    //     ...
    // }

    // make getTotalBuckets() public:
    //   int getTotalBuckets() { return total_buckets; }

// --- In SymbolTable, modified Lookup skips scope-local from other scopes: ---
    SymbolInfo* Lookup(string name) {
        ScopeTable* sc = currentScope;
        int bucket = 0, pos = 0;
        while (sc) {
            SymbolInfo* found = sc->Lookup(name, bucket, pos);
            if (found) {
                if (found->isScopeLocal() && sc != currentScope) {
                    sc = sc->getParentScope();
                    continue;
                }
                out << "\t'" << name << "' found in ScopeTable# "
                    << sc->getScopeId() << " at position "
                    << bucket << ", " << pos << endl;
                return found;
            }
            sc = sc->getParentScope();
        }
        out << "\t'" << name << "' not found in any of the ScopeTables" << endl;
        return nullptr;
    }

// --- In SymbolTable, add InsertScopeLocal: ---
    bool InsertScopeLocal(string name, string type, string extra = "") {
        if (!currentScope) return false;
        return currentScope->Insert(name, type, extra, true);
    }

// --- In processCommand, handle 'IS': ---
    // } else if (cmd == "IS") {
    //     ss >> token1 >> token2;
    //     if (token1.empty() || token2.empty()) {
    //         out << "\tNumber of parameters mismatch for the command IS" << endl;
    //         return;
    //     }
    //     string remaining, word;
    //     while (ss >> word) {
    //         if (!remaining.empty()) remaining += ",";
    //         remaining += word;
    //     }
    //     st.InsertScopeLocal(token1, token2, remaining);
    // }

// --- In main's command validation, add 'IS': ---
    // } else if (cmd != "I" && cmd != "L" && cmd != "D" && cmd != "S"
    //            && cmd != "E" && cmd != "DT" && cmd != "IS") {
    //     continue;
    // }


// =============================================================================
// 5. DELETE-BY-TYPE  (C1)
// =============================================================================

// --- In ScopeTable, add DeleteByType: ---
    void DeleteByType(const string& type) {
        for (int i = 0; i < total_buckets; i++) {
            auto& bucket = table[i];
            int bucketIdx = i + 1;

            while (true) {
                string name;
                int pos = 0;
                mylist<SymbolInfo>::Node* node = bucket.find_if([&](SymbolInfo& si) {
                    pos++;
                    if (si.getType() == type) {
                        name = si.getName();
                        return true;
                    }
                    return false;
                });
                if (!node) break;

                bucket.remove_if([&](SymbolInfo& si) {
                    return si.getName() == name;
                });

                out << "\tDeleted '" << name << "' from ScopeTable# "
                    << scope_id << " at position " << bucketIdx
                    << ", " << pos << endl;
            }
        }
    }

// --- In SymbolTable, add DeleteType (walks all scopes): ---
    void DeleteType(string type) {
        if (!currentScope) return;
        ScopeTable* sc = currentScope;
        while (sc) {
            sc->DeleteByType(type);
            sc = sc->getParentScope();
        }
    }

// --- In processCommand, handle 'DT': ---
    // } else if (cmd == "DT") {
    //     if (!(ss >> token1)) {
    //         out << "\tNumber of parameters mismatch for the command DT" << endl;
    //     } else {
    //         st.DeleteType(token1);
    //     }
    // }

// --- In main's command validation, add 'DT': ---
    // } else if (cmd != "I" && cmd != "L" && cmd != "D" && cmd != "S"
    //            && cmd != "E" && cmd != "DT" && cmd != "IS") {
    //     continue;
    // }


// =============================================================================
// 6. BUCKET SIZE VALIDATION  (common fix applied to all solutions)
// =============================================================================

    // After reading bucketSize from input:
    // int bucketSize = stoi(line);
    // if (bucketSize <= 0) {
    //     out << "\tInvalid bucket size " << bucketSize << ", defaulting to 1" << endl;
    //     bucketSize = 1;
    // }


// =============================================================================
// 7. I COMMAND ARG VALIDATION  (common fix applied to all solutions)
// =============================================================================

    // In processCommand, after ss >> token1 >> token2:
    // if (token1.empty() || token2.empty()) {
    //     out << "\tNumber of parameters mismatch for the command I" << endl;
    //     return;
    // }

// =============================================================================
// 8. SDBMHash SINGLE-COMPUTE OPTIMIZATION  (Insert/Lookup/Delete)
// =============================================================================

    // Instead of calling getBucket(name) and getBucketIndex(name)
    // (both call SDBMHash), compute hash once:
    //
    //   unsigned int hash = SDBMHash(name);
    //   auto& bucket = table[hash];
    //   int bucketIdx = hash + 1;

// =============================================================================
// 9. RULE OF THREE  (mylist<T> — 2205040_general.h)
// =============================================================================

    // Added to mylist<T> class:
    //
    // mylist(const mylist& other) : head(nullptr) {
    //     Node** last = &head;
    //     for (Node* cur = other.head; cur; cur = cur->next) {
    //         *last = new Node(cur->data);
    //         last = &((*last)->next);
    //     }
    // }
    //
    // mylist& operator=(const mylist& other) {
    //     if (this != &other) {
    //         Node* cur = head;
    //         while (cur) { Node* tmp = cur; cur = cur->next; delete tmp; }
    //         head = nullptr;
    //         Node** last = &head;
    //         for (Node* cur2 = other.head; cur2; cur2 = cur2->next) {
    //             *last = new Node(cur2->data);
    //             last = &((*last)->next);
    //         }
    //     }
    //     return *this;
    // }

// =============================================================================
// 10. SYMBOLINFO DEAD CODE REMOVED
// =============================================================================

    // SymbolInfo::next / getNext() / setNext() — commented out as dead code
    // (never read anywhere — mylist manages its own Node internal next pointers)
