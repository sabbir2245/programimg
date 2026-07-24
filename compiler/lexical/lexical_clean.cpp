#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include "general.h"

using namespace std;

// ===================== Symbol table =====================
unsigned int sdbmHash(const string& p, int mod) {
    unsigned int hash = 0;
    auto *str = (const unsigned char *)p.c_str();
    int c{};
    while ((c = *str++)) {
        hash = (c + (hash << 6) + (hash << 16) - hash) % mod;
    }
    return hash;
}

class SymbolInfo {
    string name;
    string type;
public:
    SymbolInfo() : name(""), type("") {}
    SymbolInfo(const string& name, const string& type) : name(name), type(type) {}
    string getName() const { return name; }
    string getType() const { return type; }
};

class ScopeTable {
    mylist<SymbolInfo>* buckets;
    int totalBuckets;
    string scopeId;
    ScopeTable* parent;
    int childCount;

public:
    ScopeTable(int nBuckets, const string& id, ScopeTable* p)
        : totalBuckets(nBuckets), scopeId(id), parent(p), childCount(0) {
        buckets = new mylist<SymbolInfo>[totalBuckets];
    }

    string getId() const { return scopeId; }
    ScopeTable* getParent() const { return parent; }
    int getNextChildNum() { return ++childCount; }

    pair<int,int> Insert(const string& name, const string& type) {
        unsigned int idx = sdbmHash(name, totalBuckets);
        int pos = 0;
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            pos++;
            if (it->getName() == name) return {-1, -1};
        }
        buckets[idx].push_back(SymbolInfo(name, type));
        return {(int)idx + 1, pos + 1};
    }

    pair<int,int> Lookup(const string& name) {
        unsigned int idx = sdbmHash(name, totalBuckets);
        int pos = 0;
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            pos++;
            if (it->getName() == name) return {(int)idx + 1, pos};
        }
        return {-1, -1};
    }

    void PrintNonEmpty(ostream& out) {
        for (int i = 0; i < totalBuckets; i++) {
            bool first = true;
            string bucketLine;
            for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it) {
                if (first) {
                    bucketLine += to_string(i + 1) + " --> < " + it->getName() + " : " + it->getType() + " >";
                    first = false;
                } else {
                    bucketLine += "< " + it->getName() + " : " + it->getType() + " >";
                }
            }
            if (!first) out << bucketLine << endl;
        }
    }

    ~ScopeTable() { delete[] buckets; }
};

class SymbolTable {
    ScopeTable* current;
    int bucketSize;

public:
    SymbolTable(int bs) : current(nullptr), bucketSize(bs) {
        current = new ScopeTable(bucketSize, "1", nullptr);
    }

    void EnterScope() {
        if (!current) return;
        int childNum = current->getNextChildNum();
        string newId = current->getId() + "." + to_string(childNum);
        current = new ScopeTable(bucketSize, newId, current);
    }

    string getCurrentId() const { return current ? current->getId() : "?"; }

    void ExitScope() {
        if (!current) return;
        ScopeTable* temp = current;
        current = current->getParent();
        delete temp;
    }

    pair<int,int> Insert(const string& name, const string& type) {
        if (!current) return {-1, -1};
        return current->Insert(name, type);
    }

    pair<int,int> LookupAll(const string& name) {
        ScopeTable* s = current;
        while (s) {
            auto res = s->Lookup(name);
            if (res.first != -1) return res;
            s = s->getParent();
        }
        return {-1, -1};
    }

    void PrintAll(ostream& out) {
        vector<ScopeTable*> scopes;
        ScopeTable* s = current;
        while (s) {
            scopes.push_back(s);
            s = s->getParent();
        }
        for (auto* sc : scopes) {
            out << "ScopeTable # " << sc->getId() << endl;
            sc->PrintNonEmpty(out);
        }
    }

    ~SymbolTable() {
        while (current) {
            ScopeTable* temp = current;
            current = current->getParent();
            delete temp;
        }
    }
};

// ===================== Global variables =====================
SymbolTable st(7);
ostringstream flog;
ofstream ftoken;
int errorCount = 0;

string buf;
int startLine = 0;

string decoded;
char charVal;
int charCount;

vector<pair<string, string>> kwTable = {
    {"if", "IF"}, {"else", "ELSE"}, {"for", "FOR"}, {"while", "WHILE"},
    {"do", "DO"}, {"break", "BREAK"}, {"continue", "CONTINUE"}, {"return", "RETURN"},
    {"int", "INT"}, {"float", "FLOAT"}, {"double", "DOUBLE"}, {"char", "CHAR"},
    {"void", "VOID"}, {"short", "SHORT"}, {"long", "LONG"}, {"static", "STATIC"},
    {"unsigned", "UNSIGNED"}, {"switch", "SWITCH"}, {"case", "CASE"},
    {"default", "DEFAULT"}, {"goto", "GOTO"}
};

// ===================== State machine =====================
enum State { INITIAL, COMMENT, STRING, CHAR, LINE_COMMENT };
State state = INITIAL;

string content;
size_t pos = 0;
int lineNo = 1;

int yyinput() {
    if (pos >= content.size()) return EOF;
    return (unsigned char)content[pos++];
}

void unput(int c) {
    if (c != EOF && pos > 0) pos--;
}

int peek() {
    if (pos >= content.size()) return EOF;
    return (unsigned char)content[pos];
}

char resolveEscape(char esc) {
    switch (esc) {
        case 'n':  return '\n'; case 't':  return '\t'; case 'r':  return '\r';
        case '0':  return '\0'; case '\\': return '\\'; case '\'': return '\'';
        case '"':  return '"';  case 'a':  return '\a'; case 'b':  return '\b';
        case 'f':  return '\f'; case 'v':  return '\v';
        default:   return esc;
    }
}

// ===================== Forward declarations =====================
void printLog(const string& tokenType, const string& lexeme);
void printError(const string& msg);
void handleSymbolInsert(const string& name, const string& type);
void scanNumber();

// ===================== State helpers =====================

void handleStringEscape() {
    int c = yyinput();
    if (c == EOF) return;
    switch (c) {
        case 'n':  decoded += '\n'; buf += "\\n"; break;
        case 't':  decoded += '\t'; buf += "\\t"; break;
        case 'r':  decoded += '\r'; buf += "\\r"; break;
        case '0':  decoded += '\0'; buf += "\\0"; break;
        case '\\': decoded += '\\'; buf += "\\\\"; break;
        case '\"': decoded += '"';  buf += "\\\""; break;
        case '\'': decoded += '\''; buf += "\\\'"; break;
        case 'a':  decoded += '\a'; buf += "\\a"; break;
        case 'b':  decoded += '\b'; buf += "\\b"; break;
        case 'f':  decoded += '\f'; buf += "\\f"; break;
        case 'v':  decoded += '\v'; buf += "\\v"; break;
        case '\n': buf += "\\\n"; lineNo++; break;
        default:   decoded += (char)c; buf += '\\'; buf += (char)c; break;
    }
}

void handleCharEscape() {
    int c = yyinput();
    if (c == EOF) return;
    charVal = resolveEscape((char)c);
    buf += '\\';
    buf += (char)c;
    charCount++;
}

// ===================== Lexer =====================

void runLexer() {
    state = INITIAL;

    while (true) {
        int c;

        if (state == INITIAL) {
            c = yyinput();
            if (c == EOF) break;

            if (c == ' ' || c == '\t') continue;
            if (c == '\n') { lineNo++; continue; }

            if (c == '/') {
                int n = yyinput();
                if (n == '/') {
                    buf = "//"; state = LINE_COMMENT; continue;
                } else if (n == '*') {
                    buf = "/*"; startLine = lineNo; state = COMMENT; continue;
                } else {
                    if (n != EOF) unput(n);
                }
            }

            if (c == '"') {
                buf = "\""; decoded = ""; startLine = lineNo; state = STRING; continue;
            }

            if (c == '\'') {
                buf = "'"; charVal = 0; charCount = 0; startLine = lineNo; state = CHAR; continue;
            }

            // two-char operators
            {
                int n = yyinput();
                string s;
                s += (char)c;
                s += (char)n;
                string ty;
                if (s == "<=" || s == ">=" || s == "==" || s == "!=") ty = "RELOP";
                else if (s == "&&" || s == "||") ty = "LOGICOP";
                else if (s == "++" || s == "--") ty = "INCOP";
                if (!ty.empty()) {
                    ftoken << "<" << ty << ", " << s << "> ";
                    printLog(ty, s);
                    continue;
                }
                if (n != EOF) unput(n);
            }

            // single-char operators
            {
                string ty;
                switch (c) {
                    case '+': case '-': ty = "ADDOP"; break;
                    case '*': case '/': case '%': ty = "MULOP"; break;
                    case '=': ty = "ASSIGNOP"; break;
                    case '!': ty = "NOT"; break;
                    case '<': case '>': ty = "RELOP"; break;
                    case '(': ty = "LPAREN"; break;
                    case ')': ty = "RPAREN"; break;
                    case '{': ty = "LCURL"; break;
                    case '}': ty = "RCURL"; break;
                    case '[': ty = "LTHIRD"; break;
                    case ']': ty = "RTHIRD"; break;
                    case ',': ty = "COMMA"; break;
                    case ';': ty = "SEMICOLON"; break;
                }
                if (!ty.empty()) {
                    string lexeme(1, (char)c);
                    ftoken << "<" << ty << ", " << lexeme << "> ";
                    printLog(ty, lexeme);
                    if (c == '{') st.EnterScope();
                    else if (c == '}') st.ExitScope();
                    continue;
                }
            }

            // identifiers / keywords
            if (isalpha(c) || c == '_') {
                string tok;
                tok += (char)c;
                while ((c = yyinput()) != EOF && (isalnum(c) || c == '_')) tok += (char)c;
                if (c != EOF) unput(c);
                bool isKw = false;
                for (auto& p : kwTable) {
                    if (p.first == tok) {
                        printLog(p.second, tok);
                        ftoken << "<" << p.second << "> ";
                        isKw = true;
                        break;
                    }
                }
                if (!isKw) {
                    ftoken << "<ID, " << tok << "> ";
                    printLog("ID", tok);
                    handleSymbolInsert(tok, "ID");
                }
                continue;
            }

            // numbers
            if (isdigit(c)) {
                unput(c);
                scanNumber();
                continue;
            }
            if (c == '.') {
                int n = yyinput();
                if (n != EOF && isdigit(n)) {
                    unput(c);
                    unput(n);
                    scanNumber();
                    continue;
                }
                if (n != EOF) unput(n);
            }

            // unrecognized
            {
                string err(1, (char)c);
                printError("Unrecognized character " + err);
            }

        } else if (state == LINE_COMMENT) {
            c = yyinput();
            if (c == '\\' && (c = yyinput()) == '\n') {
                buf += "\\\n"; lineNo++;
            } else if (c == '\n') {
                state = INITIAL; lineNo++;
                printLog("COMMENT", buf);
            } else if (c == EOF) {
                state = INITIAL;
                printLog("COMMENT", buf);
                break;
            } else {
                buf += (char)c;
            }

        } else if (state == COMMENT) {
            c = yyinput();
            if (c == '*') {
                if (peek() == '/') { yyinput(); buf += "*/"; state = INITIAL; printLog("COMMENT", buf); }
                else { buf += '*'; }
            } else if (c == EOF) {
                flog << "Error at line no " << startLine << ": Unterminated comment " << buf << endl << endl;
                errorCount++; state = INITIAL; break;
            } else if (c == '\n') {
                buf += '\n'; lineNo++;
            } else {
                buf += (char)c;
            }

        } else if (state == STRING) {
            c = yyinput();
            if (c == '"') {
                buf += '"'; state = INITIAL;
                ftoken << "<STRING, " << decoded << "> ";
                flog << "Line no " << startLine << ": Token <STRING> Lexeme " << buf
                     << " found --> <STRING, " << decoded << ">" << endl << endl;
            } else if (c == '\\') {
                handleStringEscape();
            } else if (c == '\n') {
                unput('\n'); state = INITIAL;
                flog << "Error at line no " << startLine << ": Unterminated string " << buf << endl << endl;
                errorCount++;
            } else if (c == EOF) {
                state = INITIAL;
                flog << "Error at line no " << startLine << ": Unterminated string " << buf << endl << endl;
                errorCount++; break;
            } else {
                decoded += (char)c; buf += (char)c;
            }

        } else if (state == CHAR) {
            c = yyinput();
            if (c == '\\') {
                handleCharEscape();
            } else if (c == '\n') {
                state = INITIAL;
                flog << "Error at line no " << startLine << ": Unterminated character " << buf << endl << endl;
                errorCount++;
            } else if (c == '\'') {
                state = INITIAL; buf += '\'';
                if (charCount == 0) {
                    flog << "Error at line no " << startLine << ": Empty character constant error ''" << endl << endl;
                    errorCount++;
                } else if (charCount == 1) {
                    string actualStr(1, charVal);
                    ftoken << "<CONST_CHAR, " << actualStr << "> ";
                    flog << "Line no " << startLine << ": Token <CONST_CHAR> Lexeme " << buf
                         << " found --> <CONST_CHAR, " << actualStr << ">" << endl << endl;
                    handleSymbolInsert(buf, "CONST_CHAR");
                } else {
                    flog << "Error at line no " << startLine << ": Multi character constant error " << buf << endl << endl;
                    errorCount++;
                }
            } else if (c == EOF) {
                state = INITIAL;
                flog << "Error at line no " << startLine << ": Unterminated character " << buf << endl << endl;
                errorCount++; break;
            } else {
                if (charCount == 0) charVal = (char)c;
                buf += (char)c; charCount++;
            }
        }
    }

    // Handle EOF states: any remaining LINE_COMMENT, COMMENT, STRING, CHAR
    if (state == LINE_COMMENT) { state = INITIAL; printLog("COMMENT", buf); }
    if (state == COMMENT) {
        flog << "Error at line no " << startLine << ": Unterminated comment " << buf << endl << endl;
        errorCount++; state = INITIAL;
    }
    if (state == STRING) {
        flog << "Error at line no " << startLine << ": Unterminated string " << buf << endl << endl;
        errorCount++; state = INITIAL;
    }
    if (state == CHAR) {
        flog << "Error at line no " << startLine << ": Unterminated character " << buf << endl << endl;
        errorCount++; state = INITIAL;
    }

    flog << "Total lines: " << lineNo << endl;
    flog << "Total errors: " << errorCount << endl;
}

// ===================== Helper implementations =====================

void printLog(const string& tokenType, const string& lexeme) {
    flog << "Line no " << lineNo << ": Token <" << tokenType << "> Lexeme " << lexeme << " found" << endl << endl;
}

void printError(const string& msg) {
    flog << "Error at line no " << lineNo << ": " << msg << endl << endl;
    errorCount++;
}

void handleSymbolInsert(const string& name, const string& type) {
    auto lookup = st.LookupAll(name);
    if (lookup.first != -1) {
        flog << "< " << name << " : " << type << " > already exists in ScopeTable# "
             << st.getCurrentId() << " at position " << lookup.first << ", " << lookup.second << endl << endl;
    } else {
        st.Insert(name, type);
    }
    st.PrintAll(flog);
    flog << endl;
}

void scanNumber() {
    string buf;
    buf += (char)yyinput();

    bool isFloat = false;
    int dotCount = 0;
    bool hasExponent = false;
    string errorType;

    int c;
    while ((c = yyinput()) != EOF) {
        if (isdigit(c)) {
            buf += (char)c;

        } else if (c == '.') {
            buf += (char)c;
            if (hasExponent) {
                while ((c = yyinput()) != EOF && isdigit(c)) buf += (char)c;
                if (c != EOF) unput(c);
                errorType = "ill formed";
                break;
            }
            isFloat = true;
            dotCount++;
            if (dotCount > 1) { errorType = "multiple decimal"; break; }

        } else if ((c == 'E' || c == 'e') && !hasExponent) {
            buf += (char)c;
            hasExponent = true;
            isFloat = true;
            int d = yyinput();
            if (d == '+' || d == '-') buf += (char)d;
            else if (d != EOF) unput(d);

        } else if (c == '_' || (isalpha(c) && c != 'E' && c != 'e')) {
            buf += (char)c;
            while ((c = yyinput()) != EOF && (isalnum(c) || c == '.' || c == '_')) buf += (char)c;
            if (c != EOF) unput(c);
            errorType = "invalid suffix";
            break;

        } else {
            if (c != EOF) unput(c);
            break;
        }
    }

    if (!errorType.empty()) {
        while ((c = yyinput()) != EOF && !isspace(c) && c != '\n') buf += (char)c;
        if (c != EOF) unput(c);
        if (errorType == "multiple decimal") printError("Too many decimal points " + buf);
        else if (errorType == "ill formed") printError("Ill formed number " + buf);
        else printError("Invalid prefix on ID or invalid suffix on Number " + buf);
    } else {
        string type = isFloat ? "CONST_FLOAT" : "CONST_INT";
        ftoken << "<" << type << ", " << buf << "> ";
        printLog(type, buf);
        handleSymbolInsert(buf, type);
    }
}

// ===================== main =====================

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string baseName = "2205040";
    string tokenFile = baseName + "_token.txt";
    string logFile = baseName + "_log.txt";

    ifstream fin(inputFile);
    if (!fin) { cerr << "Cannot open input file: " << inputFile << endl; return 1; }

    content.assign((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    ftoken.open(tokenFile);

    runLexer();

    ofstream fout(logFile);
    fout << flog.str();
    fout.close();
    ftoken.close();

    return 0;
}
