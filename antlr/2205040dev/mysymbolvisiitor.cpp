#include "SymbolTableVisitor.h"

#include <algorithm>
#include <functional>
#include <sstream>

using namespace antlr4;
using namespace std;

// ============================================================
// Global error information
// ============================================================

extern std::ofstream errorFile;
extern int errorCount;

// ============================================================
// Common type names
// ============================================================
//
// These strings are used throughout the semantic analyzer.
// Keeping them in one place makes comparisons easier to read
// and prevents repeatedly writing string literals everywhere.
//

static const string TYPE_INT = "int";
static const string TYPE_FLOAT = "float";
static const string TYPE_VOID = "void";
static const string TYPE_ERROR = "error";

// A function argument list contains the type of every argument.
typedef vector<string> ArgVec;

// ============================================================
// Small helper functions
// ============================================================

/*
 * Removes spaces and tabs from the beginning and end of a string.
 *
 * Example:
 *
 *     "   abc   "  ->  "abc"
 *
 * This is mainly used while processing variable declarations.
 */
static string trim(const string &s)
{
    size_t begin = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");

    if (begin == string::npos)
        return "";

    return s.substr(begin, end - begin + 1);
}

/*
 * Convert a string into std::any.
 *
 * The visitor functions return std::any because that is what
 * ANTLR's generated visitor interface expects.
 */
static any makeValue(const string &type)
{
    return any(type);
}

/*
 * Extract a string from std::any.
 *
 * All expression visitors in this program return a string
 * representing a type such as:
 *
 *     int
 *     float
 *     void
 *     error
 */
static string getType(const any &value)
{
    return any_cast<string>(value);
}

/*
 * Convert an argument-type vector into std::any.
 */
static any makeArgumentTypes(const ArgVec &types)
{
    return any(types);
}

/*
 * Extract an argument-type vector from std::any.
 */
static ArgVec getArgumentTypes(const any &value)
{
    return any_cast<ArgVec>(value);
}

/*
 * Check whether a token represents a valid type keyword.
 *
 * This is used while extracting function parameter information.
 */
static bool isTypeToken(size_t tokenType)
{
    return tokenType == id2205040_CSubsetParser::INT ||
           tokenType == id2205040_CSubsetParser::FLOAT ||
           tokenType == id2205040_CSubsetParser::VOID;
}

/*
 * Compare the parameter types of a function with an existing
 * function symbol.
 *
 * Returns:
 *
 *     true  -> parameter types match
 *     false -> at least one parameter type is different
 *
 * Parameter count is checked separately because the original
 * program reports a different error for count mismatch.
 */
static bool parameterTypesMatch(
    const vector<SymbolInfo> &params,
    const SymbolInfo &function)
{
    for (size_t i = 0; i < params.size(); i++)
    {
        if (params[i].type != function.paramTypes[i])
            return false;
    }

    return true;
}

/*
 * Fill a SymbolInfo object with information about a function.
 *
 * This removes the repeated code that originally appeared when
 * inserting a new function into the global scope.
 */
static void setupFunctionSymbol(
    SymbolInfo &function,
    const string &returnType,
    const vector<SymbolInfo> &params,
    bool defined)
{
    function.isFunction = true;
    function.defined = defined;
    function.paramCount = static_cast<int>(params.size());

    for (const SymbolInfo &param : params)
    {
        function.paramTypes.push_back(param.type);
    }
}

// ============================================================
// Constructor / destructor
// ============================================================

/*
 * Constructor.
 *
 * The symbol table always starts with one global scope.
 *
 * scopes[0] = global scope
 */
SymbolTableVisitor::SymbolTableVisitor(ofstream &log)
    : logFile(log)
{
    scopes.push_back(SymbolTable());
}

/*
 * Nothing special needs to be cleaned up manually.
 */
SymbolTableVisitor::~SymbolTableVisitor()
{
}

// ============================================================
// Logging and error reporting
// ============================================================

/*
 * Write the grammar rule and the source text associated with it
 * to the log file.
 */
void SymbolTableVisitor::logRule(
    const string &rule,
    const string &code) const
{
    logFile << "Rule: " << rule
            << "  Code: " << code
            << endl;
}

/*
 * Report a semantic error.
 *
 * errorCount is increased for every semantic error.
 */
void SymbolTableVisitor::semError(
    int line,
    const string &msg)
{
    errorCount++;

    errorFile << "Line no " << line
              << ": " << msg
              << endl;
}

/*
 * Report a warning.
 *
 * Warnings do not increase errorCount.
 */
void SymbolTableVisitor::semWarning(
    int line,
    const string &msg)
{
    errorFile << "Line no " << line
              << ": Warning: " << msg
              << endl;
}

// ============================================================
// Symbol-table lookup functions
// ============================================================

/*
 * Find a symbol starting from the current scope and moving
 * outward toward the global scope.
 *
 * The last scope is the innermost scope, so we search backwards.
 */
SymbolInfo *SymbolTableVisitor::findSymbol(const string &name)
{
    for (size_t scopeIndex = scopes.size(); scopeIndex-- > 0;)
    {
        for (SymbolInfo &symbol : scopes[scopeIndex].table)
        {
            if (symbol.name == name)
                return &symbol;
        }
    }

    return nullptr;
}

/*
 * Search only the global scope.
 *
 * Function declarations and definitions are stored globally,
 * so they specifically need this lookup behavior.
 */
SymbolInfo *SymbolTableVisitor::findGlobal(const string &name)
{
    if (scopes.empty())
        return nullptr;

    for (SymbolInfo &symbol : scopes[0].table)
    {
        if (symbol.name == name)
            return &symbol;
    }

    return nullptr;
}

// ============================================================
// Symbol-table printing
// ============================================================

/*
 * Print every currently active scope.
 *
 * Scope 0 is the global scope.
 * Larger scope numbers represent nested scopes.
 */
void SymbolTableVisitor::printSymbolTable()
{
    logFile << "Symbol Table:" << endl;

    for (size_t i = 0; i < scopes.size(); i++)
    {
        logFile << "Scope " << i << ":" << endl;
        scopes[i].print(logFile);
    }
}

// ============================================================
// Parameter processing
// ============================================================

/*
 * Extract parameter information from an ANTLR parameter_list.
 *
 * The grammar tree can contain several nested nodes, so we first
 * collect every terminal token recursively.
 *
 * Then we sort them according to their original token position.
 *
 * Finally:
 *
 *     int a, float b
 *
 * becomes approximately:
 *
 *     [
 *         SymbolInfo("a", "int"),
 *         SymbolInfo("b", "float")
 *     ]
 *
 * If a parameter has no identifier, its name remains empty.
 */
vector<SymbolInfo> SymbolTableVisitor::makeParamList(
    id2205040_CSubsetParser::Parameter_listContext *ctx)
{
    vector<SymbolInfo> parameters;

    // No parameter list means there are no parameters.
    if (!ctx)
        return parameters;

    // --------------------------------------------------------
    // Step 1: Collect all terminal tokens from the parse tree.
    // --------------------------------------------------------

    vector<tree::TerminalNode *> terminals;

    function<void(antlr4::tree::ParseTree *)> collectTerminals;

    collectTerminals = [&](antlr4::tree::ParseTree *node)
    {
        // If this node is an actual token, save it.
        if (auto terminal =
                dynamic_cast<tree::TerminalNode *>(node))
        {
            terminals.push_back(terminal);
            return;
        }

        // Otherwise recursively inspect all children.
        for (auto child : node->children)
        {
            collectTerminals(child);
        }
    };

    // Start walking from every child of parameter_list.
    for (auto child : ctx->children)
    {
        collectTerminals(child);
    }

    // --------------------------------------------------------
    // Step 2: Restore source-code order.
    // --------------------------------------------------------
    //
    // ANTLR already gives us the parse tree, but sorting by
    // token index makes the intended source order explicit.
    //

    sort(
        terminals.begin(),
        terminals.end(),
        [](const tree::TerminalNode *a,
           const tree::TerminalNode *b)
        {
            return a->getSymbol()->getTokenIndex() < b->getSymbol()->getTokenIndex();
        });

    // --------------------------------------------------------
    // Step 3: Separate types and identifiers.
    // --------------------------------------------------------

    vector<string> types;
    vector<string> ids;

    for (auto terminal : terminals)
    {
        size_t tokenType =
            terminal->getSymbol()->getType();

        if (isTypeToken(tokenType))
        {
            types.push_back(terminal->getText());
        }
        else if (tokenType ==
                 id2205040_CSubsetParser::ID)
        {
            ids.push_back(terminal->getText());
        }
    }

    // --------------------------------------------------------
    // Step 4: Combine each type with its corresponding ID.
    // --------------------------------------------------------

    for (size_t i = 0; i < types.size(); i++)
    {
        string name;

        if (i < ids.size())
            name = ids[i];

        SymbolInfo parameter(name, types[i]);
        parameters.push_back(parameter);
    }

    return parameters;
}

// ============================================================
// Simple visitor functions
// ============================================================
//
// These rules do not perform semantic analysis themselves.
// They simply log the rule and continue visiting their children.
// Keeping them together makes the visitor easier to scan.
//

any SymbolTableVisitor::visitStart(
    id2205040_CSubsetParser::StartContext *ctx)
{
    return visitChildren(ctx);
}

any SymbolTableVisitor::visitProgram(
    id2205040_CSubsetParser::ProgramContext *ctx)
{
    return visitChildren(ctx);
}

any SymbolTableVisitor::visitUnit(
    id2205040_CSubsetParser::UnitContext *ctx)
{
    return visitChildren(ctx);
}

any SymbolTableVisitor::visitParameter_list(
    id2205040_CSubsetParser::Parameter_listContext *ctx)
{
    logRule("parameter_list", ctx->getText());

    return visitChildren(ctx);
}

any SymbolTableVisitor::visitType_specifier(
    id2205040_CSubsetParser::Type_specifierContext *ctx)
{
    logRule("type_specifier", ctx->getText());

    return visitChildren(ctx);
}

any SymbolTableVisitor::visitDeclaration_list(
    id2205040_CSubsetParser::Declaration_listContext *ctx)
{
    logRule("declaration_list", ctx->getText());

    return visitChildren(ctx);
}

any SymbolTableVisitor::visitStatements(
    id2205040_CSubsetParser::StatementsContext *ctx)
{
    logRule("statements", ctx->getText());

    return visitChildren(ctx);
}

any SymbolTableVisitor::visitStatement(
    id2205040_CSubsetParser::StatementContext *ctx)
{
    logRule("statement", ctx->getText());

    return visitChildren(ctx);
}

any SymbolTableVisitor::visitExpression_statement(
    id2205040_CSubsetParser::Expression_statementContext *ctx)
{
    logRule("expression_statement", ctx->getText());

    return visitChildren(ctx);
}

// ============================================================
// Variable handling
// ============================================================

/*
 * Process a variable usage.
 *
 * There are two important cases:
 *
 *     x
 *
 * and
 *
 *     x[index]
 *
 * For an indexed variable we verify:
 *
 * 1. The variable actually exists.
 * 2. It is an array.
 * 3. The index has integer type.
 */
any SymbolTableVisitor::visitVariable(
    id2205040_CSubsetParser::VariableContext *ctx)
{
    int line = ctx->getStart()->getLine();
    string name = ctx->ID()->getText();

    logRule("variable", ctx->getText());

    SymbolInfo *symbol = findSymbol(name);

    // Variable does not exist in any visible scope.
    if (!symbol)
    {
        semError(
            line,
            "Undeclared variable '" + name + "'");

        return makeValue(TYPE_ERROR);
    }

    // --------------------------------------------------------
    // Indexed variable: array[index]
    // --------------------------------------------------------

    if (ctx->LTHIRD())
    {
        // x[5] is invalid if x is not an array.
        if (!symbol->isArray)
        {
            semError(
                line,
                "Index used with non-array variable '" +
                    name + "'");
        }

        // The default index type is int.
        string indexType = TYPE_INT;

        // If an actual expression exists, evaluate it.
        if (ctx->expression())
        {
            indexType = getType(
                visit(ctx->expression()));
        }

        // Array indices must be integers.
        //
        // "error" is allowed here so that one earlier semantic
        // error does not create another unrelated error.
        if (indexType != TYPE_INT &&
            indexType != TYPE_ERROR)
        {
            semError(
                line,
                "Array index of '" + name +
                    "' must be an integer");
        }

        return makeValue(symbol->type);
    }

    // Normal variable access.
    return makeValue(symbol->type);
}

// ============================================================
// Variable declaration
// ============================================================

/*
 * Process a declaration such as:
 *
 *     int a, b, c;
 *
 * or:
 *
 *     float x, arr[10];
 *
 * The declaration_list text is split by commas and each
 * declaration is converted into a SymbolInfo.
 */
any SymbolTableVisitor::visitVar_declaration(
    id2205040_CSubsetParser::Var_declarationContext *ctx)
{
    int line = ctx->getStart()->getLine();

    string type =
        ctx->type_specifier()->getText();

    string declarationText =
        ctx->declaration_list()->getText();

    stringstream stream(declarationText);
    string declaration;

    // --------------------------------------------------------
    // Process each comma-separated declaration.
    // --------------------------------------------------------

    while (getline(stream, declaration, ','))
    {
        string token = trim(declaration);

        string name;

        bool isArray = false;
        int arraySize = 0;

        // Look for '[' to determine whether this is an array.
        size_t leftBracket =
            token.find('[');

        if (leftBracket != string::npos)
        {
            // This declaration represents an array.
            isArray = true;

            // Everything before '[' is the variable name.
            name =
                token.substr(0, leftBracket);

            // Find the numeric array size.
            size_t numberStart =
                token.find_first_of(
                    "0123456789",
                    leftBracket);

            size_t rightBracket =
                token.find(']',
                           leftBracket);

            // Only parse the size if both parts exist.
            if (numberStart != string::npos &&
                rightBracket != string::npos)
            {
                arraySize = stoi(
                    token.substr(
                        numberStart,
                        rightBracket - numberStart));
            }
        }
        else
        {
            // Normal scalar variable.
            name = token;
        }

        // Create the symbol.
        SymbolInfo symbol(name, type);

        symbol.isArray = isArray;
        symbol.arraySize = arraySize;

        // Insert into the current scope.
        bool inserted =
            scopes.back().insert(symbol);

        // insert() returns false if the same name already
        // exists in the current scope.
        if (!inserted)
        {
            semError(
                line,
                "Multiple declaration of '" +
                    name +
                    "' in the same scope");
        }
    }

    logRule(
        "var_declaration",
        ctx->getText());

    return visitChildren(ctx);
}

// ============================================================
// Scope handling
// ============================================================

/*
 * A compound statement creates a new scope.
 *
 * Example:
 *
 *     {
 *         int x;
 *     }
 *
 * When entering '{':
 *
 *     push new scope
 *
 * When leaving '}':
 *
 *     print scope
 *     pop scope
 */
any SymbolTableVisitor::visitCompound_statement(
    id2205040_CSubsetParser::Compound_statementContext *ctx)
{
    // --------------------------------------------------------
    // Create a new local scope.
    // --------------------------------------------------------

    scopes.push_back(SymbolTable());

    // --------------------------------------------------------
    // Function parameters belong to the function's first
    // compound-statement scope.
    // --------------------------------------------------------

    for (SymbolInfo &parameter : pendingParams)
    {
        // Parameters without a name are not inserted.
        if (!parameter.name.empty())
        {
            scopes.back().insert(parameter);
        }
    }

    // Parameters are only needed for this compound statement.
    pendingParams.clear();

    logRule(
        "compound_statement",
        ctx->getText());

    // Visit everything inside the scope.
    visitChildren(ctx);

    // Print the scope before removing it.
    logFile << "Exiting scope. Symbol table:"
            << endl;

    printSymbolTable();

    // Remove the scope after processing the body.
    scopes.pop_back();

    return makeValue(TYPE_VOID);
}

// ============================================================
// Function declaration
// ============================================================

/*
 * Process a function declaration such as:
 *
 *     int foo(int a, float b);
 *
 * A declaration tells the symbol table that the function exists,
 * but it does not define the function body.
 *
 * If the function already exists, its signature is checked.
 */
any SymbolTableVisitor::visitFunc_declaration(
    id2205040_CSubsetParser::Func_declarationContext *ctx)
{
    int line = ctx->getStart()->getLine();

    string returnType =
        ctx->type_specifier()->getText();

    string functionName =
        ctx->ID()->getText();

    logRule(
        "func_declaration",
        ctx->getText());

    // Extract all parameters from the grammar tree.
    vector<SymbolInfo> parameters =
        makeParamList(ctx->parameter_list());

    // Functions live in the global scope.
    SymbolInfo *existing =
        findGlobal(functionName);

    if (existing)
    {
        // ----------------------------------------------------
        // A symbol with this name already exists.
        // ----------------------------------------------------

        if (existing->isFunction)
        {
            // Check return type.
            if (existing->type != returnType)
            {
                semError(
                    line,
                    "Return type mismatch in declaration of function '" +
                        functionName + "'");
            }

            // Check parameter count.
            if (static_cast<int>(parameters.size()) !=
                existing->paramCount)
            {
                semError(
                    line,
                    "Parameter count mismatch in declaration of function '" +
                        functionName + "'");
            }
            else
            {
                // Only compare types when the number of parameters
                // is the same.
                if (!parameterTypesMatch(
                        parameters,
                        *existing))
                {
                    semError(
                        line,
                        "Parameter type mismatch in declaration of function '" +
                            functionName + "'");
                }
            }

            // A declaration after an existing definition is
            // considered an error according to the original logic.
            if (existing->defined)
            {
                semError(
                    line,
                    "Function '" +
                        functionName +
                        "' is already defined");
            }
        }
        else
        {
            // A variable and function cannot share this name
            // in the same global scope.
            semError(
                line,
                "'" + functionName +
                    "' conflicts with an existing variable in the same scope");
        }
    }
    else
    {
        // ----------------------------------------------------
        // This is the first time we see this function.
        // ----------------------------------------------------

        SymbolInfo functionSymbol(
            functionName,
            returnType);

        setupFunctionSymbol(
            functionSymbol,
            returnType,
            parameters,
            false);

        scopes[0].insert(functionSymbol);
    }

    // A declaration does not need parameters when entering a
    // compound statement.
    pendingParams.clear();

    return visitChildren(ctx);
}

// ============================================================
// Function definition
// ============================================================

/*
 * Process a complete function definition such as:
 *
 *     int foo(int a)
 *     {
 *         ...
 *     }
 *
 * This is similar to a declaration, but the function is marked
 * as defined and its parameters are saved in pendingParams.
 *
 * visitCompound_statement() later inserts those parameters into
 * the newly-created function scope.
 */
any SymbolTableVisitor::visitFunc_definition(
    id2205040_CSubsetParser::Func_definitionContext *ctx)
{
    int line = ctx->getStart()->getLine();

    string returnType =
        ctx->type_specifier()->getText();

    string functionName =
        ctx->ID()->getText();

    logRule(
        "func_definition",
        ctx->getText());

    vector<SymbolInfo> parameters =
        makeParamList(ctx->parameter_list());

    // Look for an existing global function declaration.
    SymbolInfo *existing =
        findGlobal(functionName);

    if (existing)
    {
        // ----------------------------------------------------
        // A symbol with this name already exists.
        // ----------------------------------------------------

        if (existing->isFunction)
        {
            // Check return type.
            if (existing->type != returnType)
            {
                semError(
                    line,
                    "Return type mismatch for function '" +
                        functionName + "'");
            }

            // Check number of parameters.
            if (static_cast<int>(parameters.size()) !=
                existing->paramCount)
            {
                semError(
                    line,
                    "Parameter count mismatch for function '" +
                        functionName + "'");
            }
            else
            {
                // Check parameter types.
                if (!parameterTypesMatch(
                        parameters,
                        *existing))
                {
                    semError(
                        line,
                        "Parameter type mismatch for function '" +
                            functionName + "'");
                }
            }

            // The function cannot be defined twice.
            if (existing->defined)
            {
                semError(
                    line,
                    "Multiple definitions of function '" +
                        functionName + "'");
            }
            else
            {
                // This definition completes the previous
                // declaration.
                existing->defined = true;
            }
        }
        else
        {
            // A global variable already uses this name.
            semError(
                line,
                "Function name '" +
                    functionName +
                    "' conflicts with an existing variable");
        }
    }
    else
    {
        // ----------------------------------------------------
        // No previous declaration exists.
        // Create the function directly.
        // ----------------------------------------------------

        SymbolInfo functionSymbol(
            functionName,
            returnType);

        setupFunctionSymbol(
            functionSymbol,
            returnType,
            parameters,
            true);

        scopes[0].insert(functionSymbol);
    }

    // The next compound_statement belongs to this function.
    pendingParams = parameters;

    return visitChildren(ctx);
}

// ============================================================
// Expression handling
// ============================================================

/*
 * Process an assignment:
 *
 *     variable = expression
 *
 * The visitor checks:
 *
 *     left type
 *     right type
 *     void usage
 *     int/float compatibility
 */
any SymbolTableVisitor::visitExpression(
    id2205040_CSubsetParser::ExpressionContext *ctx)
{
    logRule(
        "expression",
        ctx->getText());

    // --------------------------------------------------------
    // Assignment expression
    // --------------------------------------------------------

    if (ctx->ASSIGNOP())
    {
        int line =
            ctx->getStart()->getLine();

        // Type of the left-hand side.
        string leftType =
            getType(visit(ctx->variable()));

        // Type of the right-hand side.
        string rightType =
            getType(
                visit(ctx->logic_expression()));

        // If either side already contains an error,
        // avoid generating additional errors.
        if (leftType == TYPE_ERROR ||
            rightType == TYPE_ERROR)
        {
            return makeValue(TYPE_ERROR);
        }

        // A function cannot be used as an assignment target.
        if (leftType == TYPE_VOID)
        {
            semError(
                line,
                "Cannot assign to a function");

            return makeValue(leftType);
        }

        // A void expression cannot be assigned.
        if (rightType == TYPE_VOID)
        {
            semError(
                line,
                "Cannot assign a void value");

            return makeValue(TYPE_ERROR);
        }

        // ----------------------------------------------------
        // Type compatibility.
        // ----------------------------------------------------

        if (leftType != rightType)
        {
            if (leftType == TYPE_INT &&
                rightType == TYPE_FLOAT)
            {
                // float -> int may lose information.
                semWarning(
                    line,
                    "Possible loss of data: assigning float to int");
            }
            else if (leftType == TYPE_FLOAT &&
                     rightType == TYPE_INT)
            {
                // int -> float is implicitly allowed.
            }
            else
            {
                semError(
                    line,
                    "Assignment type mismatch between '" +
                        leftType +
                        "' and '" +
                        rightType +
                        "'");
            }
        }

        // The assignment expression has the type of its
        // left-hand side.
        return makeValue(leftType);
    }

    // Not an assignment.
    return visit(ctx->logic_expression());
}

// ============================================================
// Logical expression
// ============================================================

/*
 * Logical expressions have the form:
 *
 *     a && b
 *     a || b
 *
 * The result of a logical operation is always int.
 */
any SymbolTableVisitor::visitLogic_expression(
    id2205040_CSubsetParser::Logic_expressionContext *ctx)
{
    logRule(
        "logic_expression",
        ctx->getText());

    if (ctx->LOGICOP())
    {
        // Visit both operands so that their semantic errors
        // are still detected.
        getType(
            visit(ctx->rel_expression(0)));

        getType(
            visit(ctx->rel_expression(1)));

        // Logical operators produce int.
        return makeValue(TYPE_INT);
    }

    return visit(ctx->rel_expression(0));
}

// ============================================================
// Relational expression
// ============================================================

/*
 * Relational expressions have forms such as:
 *
 *     a < b
 *     a > b
 *     a == b
 *
 * A relational expression always produces int.
 */
any SymbolTableVisitor::visitRel_expression(
    id2205040_CSubsetParser::Rel_expressionContext *ctx)
{
    logRule(
        "rel_expression",
        ctx->getText());

    if (ctx->RELOP())
    {
        // Visit both sides for semantic checking.
        getType(
            visit(ctx->simple_expression(0)));

        getType(
            visit(ctx->simple_expression(1)));

        // Relational result is int.
        return makeValue(TYPE_INT);
    }

    return visit(ctx->simple_expression(0));
}

// ============================================================
// Simple expression
// ============================================================

/*
 * Handles addition and subtraction:
 *
 *     a + b
 *     a - b
 *
 * If either operand is float, the result is float.
 * Otherwise the result is int.
 */
any SymbolTableVisitor::visitSimple_expression(
    id2205040_CSubsetParser::Simple_expressionContext *ctx)
{
    logRule(
        "simple_expression",
        ctx->getText());

    if (ctx->ADDOP())
    {
        string leftType =
            getType(
                visit(ctx->simple_expression()));

        string rightType =
            getType(
                visit(ctx->term()));

        // float + anything -> float
        // anything + float -> float
        if (leftType == TYPE_FLOAT ||
            rightType == TYPE_FLOAT)
        {
            return makeValue(TYPE_FLOAT);
        }

        return makeValue(TYPE_INT);
    }

    return visit(ctx->term());
}

// ============================================================
// Term
// ============================================================

/*
 * Handles multiplication, division and modulus:
 *
 *     a * b
 *     a / b
 *     a % b
 *
 * Modulus is special because both operands must be int.
 */
any SymbolTableVisitor::visitTerm(
    id2205040_CSubsetParser::TermContext *ctx)
{
    logRule(
        "term",
        ctx->getText());

    if (ctx->MULOP())
    {
        int line =
            ctx->getStart()->getLine();

        string leftType =
            getType(
                visit(ctx->term()));

        string rightType =
            getType(
                visit(ctx->unary_expression()));

        string operatorText =
            ctx->MULOP()->getText();

        // ----------------------------------------------------
        // Modulus operator.
        // ----------------------------------------------------

        if (operatorText == "%")
        {
            if (leftType != TYPE_INT ||
                rightType != TYPE_INT)
            {
                semError(
                    line,
                    "Operands of modulus operator must be integers");
            }

            return makeValue(TYPE_INT);
        }

        // ----------------------------------------------------
        // Multiplication / division.
        // ----------------------------------------------------

        if (leftType == TYPE_FLOAT ||
            rightType == TYPE_FLOAT)
        {
            return makeValue(TYPE_FLOAT);
        }

        return makeValue(TYPE_INT);
    }

    return visit(ctx->unary_expression());
}

// ============================================================
// Unary expression
// ============================================================

/*
 * Handles unary operators:
 *
 *     !x
 *     +x
 *     -x
 *
 * Logical NOT always returns int.
 *
 * Unary + and - preserve float; otherwise they produce int.
 */
any SymbolTableVisitor::visitUnary_expression(
    id2205040_CSubsetParser::Unary_expressionContext *ctx)
{
    logRule(
        "unary_expression",
        ctx->getText());

    // Logical NOT.
    if (ctx->NOT())
    {
        // Visit the operand so its semantic checks still occur.
        getType(
            visit(ctx->unary_expression()));

        return makeValue(TYPE_INT);
    }

    // Unary + or -.
    if (ctx->ADDOP())
    {
        string type =
            getType(
                visit(ctx->unary_expression()));

        if (type == TYPE_FLOAT)
            return makeValue(TYPE_FLOAT);

        return makeValue(TYPE_INT);
    }

    return visit(ctx->factor());
}

// ============================================================
// Argument list
// ============================================================

/*
 * An empty argument list produces an empty vector.
 *
 * Otherwise the visitor delegates to "arguments".
 */
any SymbolTableVisitor::visitArgument_list(
    id2205040_CSubsetParser::Argument_listContext *ctx)
{
    logRule(
        "argument_list",
        ctx->getText());

    if (ctx->arguments())
    {
        return visit(ctx->arguments());
    }

    return makeArgumentTypes(ArgVec{});
}

// ============================================================
// Arguments
// ============================================================

/*
 * Build a list containing the types of all function-call
 * arguments.
 *
 * For example:
 *
 *     foo(a, 10, x + 2.5)
 *
 * could produce:
 *
 *     ["int", "int", "float"]
 *
 * The recursive call handles all arguments except the final
 * logic_expression, which is appended afterward.
 */
any SymbolTableVisitor::visitArguments(
    id2205040_CSubsetParser::ArgumentsContext *ctx)
{
    logRule(
        "arguments",
        ctx->getText());

    ArgVec argumentTypes;

    // Process previous arguments first.
    if (ctx->arguments())
    {
        argumentTypes =
            getArgumentTypes(
                visit(ctx->arguments()));
    }

    // Process the current/final argument.
    argumentTypes.push_back(
        getType(
            visit(ctx->logic_expression())));

    return makeArgumentTypes(argumentTypes);
}

// ============================================================
// Factor
// ============================================================

/*
 * A factor can represent several things:
 *
 *     10
 *     3.14
 *     (expression)
 *     function(...)
 *     variable
 *
 * This is one of the most important parts of the semantic
 * analyzer because function calls and variable usage are
 * checked here.
 */
any SymbolTableVisitor::visitFactor(
    id2205040_CSubsetParser::FactorContext *ctx)
{
    int line =
        ctx->getStart()->getLine();

    logRule(
        "factor",
        ctx->getText());

    // --------------------------------------------------------
    // Integer constant.
    // --------------------------------------------------------

    if (ctx->CONST_INT())
    {
        return makeValue(TYPE_INT);
    }

    // --------------------------------------------------------
    // Floating-point constant.
    // --------------------------------------------------------

    if (ctx->CONST_FLOAT())
    {
        return makeValue(TYPE_FLOAT);
    }

    // --------------------------------------------------------
    // Parenthesized expression.
    //
    // Example:
    //
    //     (a + b)
    // --------------------------------------------------------

    if (ctx->LPAREN() &&
        ctx->expression())
    {
        return visit(ctx->expression());
    }

    // --------------------------------------------------------
    // Function call.
    //
    // Example:
    //
    //     foo(a, b)
    // --------------------------------------------------------

    if (ctx->ID())
    {
        string functionName =
            ctx->ID()->getText();

        SymbolInfo *function =
            findSymbol(functionName);

        // The function name does not exist.
        if (!function)
        {
            semError(
                line,
                "Undeclared function '" +
                    functionName +
                    "'");

            return makeValue(TYPE_ERROR);
        }

        // The name exists, but belongs to a variable.
        if (!function->isFunction)
        {
            semError(
                line,
                "'" +
                    functionName +
                    "' is not a function");

            return makeValue(TYPE_ERROR);
        }

        // ----------------------------------------------------
        // Evaluate the argument expressions.
        // ----------------------------------------------------

        ArgVec argumentTypes;

        if (ctx->argument_list())
        {
            argumentTypes =
                getArgumentTypes(
                    visit(ctx->argument_list()));
        }

        // ----------------------------------------------------
        // Check argument count.
        // ----------------------------------------------------

        if (static_cast<int>(argumentTypes.size()) !=
            function->paramCount)
        {
            semError(
                line,
                "Function '" +
                    functionName +
                    "' expects " +
                    to_string(function->paramCount) +
                    " arguments but " +
                    to_string(argumentTypes.size()) +
                    " given");
        }
        else
        {
            // ------------------------------------------------
            // Check argument types.
            // ------------------------------------------------

            for (size_t i = 0;
                 i < argumentTypes.size();
                 i++)
            {
                if (argumentTypes[i] !=
                    function->paramTypes[i])
                {
                    semError(
                        line,
                        "Type mismatch for argument " +
                            to_string(i + 1) +
                            " in call to '" +
                            functionName +
                            "'");

                    // Keep the original behavior:
                    // report only the first mismatch.
                    break;
                }
            }
        }

        // A void function cannot be used as a value.
        if (function->type == TYPE_VOID)
        {
            semError(
                line,
                "Void function '" +
                    functionName +
                    "' used in an expression");
        }

        // The function call has the function's return type.
        return makeValue(function->type);
    }

    // --------------------------------------------------------
    // Variable usage inside an expression.
    //
    // Example:
    //
    //     x
    //     arr[i]
    // --------------------------------------------------------

    if (ctx->variable())
    {
        string variableName =
            ctx->variable()->ID()->getText();

        SymbolInfo *symbol =
            findSymbol(variableName);

        // A function cannot be used directly as a variable.
        if (symbol && symbol->isFunction)
        {
            semError(
                line,
                "'" +
                    variableName +
                    "' is a function used as a variable");

            return makeValue(TYPE_ERROR);
        }

        // An array must normally be indexed.
        //
        // The original code intentionally allows the special
        // cases involving ++ and --, so we preserve those checks.
        if (symbol &&
            symbol->isArray &&
            !ctx->INCOP() &&
            !ctx->DECOP() &&
            !ctx->variable()->LTHIRD())
        {
            semError(
                line,
                "Array '" +
                    variableName +
                    "' used without an index");
        }

        return visit(ctx->variable());
    }

    // No recognized factor.
    return makeValue(TYPE_ERROR);
}