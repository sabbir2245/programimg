#include "SymbolTableVisitor.h"

#include <algorithm>
#include <functional>
#include <sstream>

using namespace antlr4;
using namespace std;

extern std::ofstream errorFile;
extern int errorCount;

static const string TYPE_INT   = "int";
static const string TYPE_FLOAT = "float";
static const string TYPE_VOID  = "void";
static const string TYPE_ERROR = "error";

typedef vector<string> ArgVec;

static string trim(const string &s)
{
    size_t begin = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");

    if (begin == string::npos)
        return "";

    return s.substr(begin, end - begin + 1);
}

static any makeValue(const string &type)
{
    return any(type);
}

static string getType(const any &value)
{
    return any_cast<string>(value);
}

static any makeArgumentTypes(const ArgVec &types)
{
    return any(types);
}

static ArgVec getArgumentTypes(const any &value)
{
    return any_cast<ArgVec>(value);
}

static bool isTypeToken(size_t tokenType)
{
    return tokenType == id2205040_CSubsetParser::INT ||
           tokenType == id2205040_CSubsetParser::FLOAT ||
           tokenType == id2205040_CSubsetParser::VOID;
}

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

SymbolTableVisitor::SymbolTableVisitor(ofstream &log)
    : logFile(log)
{
    scopes.push_back(SymbolTable());
}

SymbolTableVisitor::~SymbolTableVisitor()
{
}

void SymbolTableVisitor::logRule(
    const string &rule,
    const string &code) const
{
    logFile << "Rule: " << rule
            << "  Code: " << code
            << endl;
}

void SymbolTableVisitor::semError(
    int line,
    const string &msg)
{
    errorCount++;

    errorFile << "Line no " << line
              << ": " << msg
              << endl;
}

void SymbolTableVisitor::semWarning(
    int line,
    const string &msg)
{
    errorFile << "Line no " << line
              << ": Warning: " << msg
              << endl;
}

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

void SymbolTableVisitor::printSymbolTable()
{
    logFile << "Symbol Table:" << endl;

    for (size_t i = 0; i < scopes.size(); i++)
    {
        logFile << "Scope " << i << ":" << endl;
        scopes[i].print(logFile);
    }
}

vector<SymbolInfo> SymbolTableVisitor::makeParamList(
    id2205040_CSubsetParser::Parameter_listContext *ctx)
{
    vector<SymbolInfo> parameters;

    if (!ctx)
        return parameters;

    vector<tree::TerminalNode *> terminals;

    function<void(antlr4::tree::ParseTree *)> collectTerminals;

    collectTerminals = [&](antlr4::tree::ParseTree *node)
    {
        if (auto terminal =
                dynamic_cast<tree::TerminalNode *>(node))
        {
            terminals.push_back(terminal);
            return;
        }

        for (auto child : node->children)
        {
            collectTerminals(child);
        }
    };

    for (auto child : ctx->children)
    {
        collectTerminals(child);
    }

    sort(
        terminals.begin(),
        terminals.end(),
        [](const tree::TerminalNode *a,
           const tree::TerminalNode *b)
        {
            return a->getSymbol()->getTokenIndex()
                 < b->getSymbol()->getTokenIndex();
        });

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

any SymbolTableVisitor::visitVariable(
    id2205040_CSubsetParser::VariableContext *ctx)
{
    int line = ctx->getStart()->getLine();
    string name = ctx->ID()->getText();

    logRule("variable", ctx->getText());

    SymbolInfo *symbol = findSymbol(name);

    if (!symbol)
    {
        semError(
            line,
            "Undeclared variable '" + name + "'");

        return makeValue(TYPE_ERROR);
    }

    if (ctx->LTHIRD())
    {
        if (!symbol->isArray)
        {
            semError(
                line,
                "Index used with non-array variable '" +
                name + "'");
        }

        string indexType = TYPE_INT;

        if (ctx->expression())
        {
            indexType = getType(
                visit(ctx->expression()));
        }

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

    return makeValue(symbol->type);
}

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

    while (getline(stream, declaration, ','))
    {
        string token = trim(declaration);

        string name;

        bool isArray = false;
        int arraySize = 0;

        size_t leftBracket =
            token.find('[');

        if (leftBracket != string::npos)
        {
            isArray = true;

            name =
                token.substr(0, leftBracket);

            size_t numberStart =
                token.find_first_of(
                    "0123456789",
                    leftBracket);

            size_t rightBracket =
                token.find(']',
                           leftBracket);

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
            name = token;
        }

        SymbolInfo symbol(name, type);

        symbol.isArray = isArray;
        symbol.arraySize = arraySize;

        bool inserted =
            scopes.back().insert(symbol);

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

any SymbolTableVisitor::visitCompound_statement(
    id2205040_CSubsetParser::Compound_statementContext *ctx)
{
    scopes.push_back(SymbolTable());

    for (SymbolInfo &parameter : pendingParams)
    {
        if (!parameter.name.empty())
        {
            scopes.back().insert(parameter);
        }
    }

    pendingParams.clear();

    logRule(
        "compound_statement",
        ctx->getText());

    visitChildren(ctx);

    logFile << "Exiting scope. Symbol table:"
            << endl;

    printSymbolTable();

    scopes.pop_back();

    return makeValue(TYPE_VOID);
}

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

    vector<SymbolInfo> parameters =
        makeParamList(ctx->parameter_list());

    SymbolInfo *existing =
        findGlobal(functionName);

    if (existing)
    {
        if (existing->isFunction)
        {
            if (existing->type != returnType)
            {
                semError(
                    line,
                    "Return type mismatch in declaration of function '" +
                    functionName + "'");
            }

            if (static_cast<int>(parameters.size()) !=
                existing->paramCount)
            {
                semError(
                    line,
                    "Parameter count mismatch in declaration of function '" +
                    functionName + "'");
            }
            else if (!parameterTypesMatch(
                         parameters,
                         *existing))
            {
                semError(
                    line,
                    "Parameter type mismatch in declaration of function '" +
                    functionName + "'");
            }

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
            semError(
                line,
                "'" + functionName +
                "' conflicts with an existing variable in the same scope");
        }
    }
    else
    {
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

    pendingParams.clear();

    return visitChildren(ctx);
}

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

    SymbolInfo *existing =
        findGlobal(functionName);

    if (existing)
    {
        if (existing->isFunction)
        {
            if (existing->type != returnType)
            {
                semError(
                    line,
                    "Return type mismatch for function '" +
                    functionName + "'");
            }

            if (static_cast<int>(parameters.size()) !=
                existing->paramCount)
            {
                semError(
                    line,
                    "Parameter count mismatch for function '" +
                    functionName + "'");
            }
            else if (!parameterTypesMatch(
                         parameters,
                         *existing))
            {
                semError(
                    line,
                    "Parameter type mismatch for function '" +
                    functionName + "'");
            }

            if (existing->defined)
            {
                semError(
                    line,
                    "Multiple definitions of function '" +
                    functionName + "'");
            }
            else
            {
                existing->defined = true;
            }
        }
        else
        {
            semError(
                line,
                "Function name '" +
                functionName +
                "' conflicts with an existing variable");
        }
    }
    else
    {
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

    pendingParams = parameters;

    return visitChildren(ctx);
}

any SymbolTableVisitor::visitExpression(
    id2205040_CSubsetParser::ExpressionContext *ctx)
{
    logRule(
        "expression",
        ctx->getText());

    if (ctx->ASSIGNOP())
    {
        int line =
            ctx->getStart()->getLine();

        string leftType =
            getType(visit(ctx->variable()));

        string rightType =
            getType(
                visit(ctx->logic_expression()));

        if (leftType == TYPE_ERROR ||
            rightType == TYPE_ERROR)
        {
            return makeValue(TYPE_ERROR);
        }

        if (leftType == TYPE_VOID)
        {
            semError(
                line,
                "Cannot assign to a function");

            return makeValue(leftType);
        }

        if (rightType == TYPE_VOID)
        {
            semError(
                line,
                "Cannot assign a void value");

            return makeValue(TYPE_ERROR);
        }

        if (leftType != rightType)
        {
            if (leftType == TYPE_INT &&
                rightType == TYPE_FLOAT)
            {
                semWarning(
                    line,
                    "Possible loss of data: assigning float to int");
            }
            else if (leftType == TYPE_FLOAT &&
                     rightType == TYPE_INT)
            {
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

        return makeValue(leftType);
    }

    return visit(ctx->logic_expression());
}

any SymbolTableVisitor::visitLogic_expression(
    id2205040_CSubsetParser::Logic_expressionContext *ctx)
{
    logRule(
        "logic_expression",
        ctx->getText());

    if (ctx->LOGICOP())
    {
        getType(
            visit(ctx->rel_expression(0)));

        getType(
            visit(ctx->rel_expression(1)));

        return makeValue(TYPE_INT);
    }

    return visit(ctx->rel_expression(0));
}

any SymbolTableVisitor::visitRel_expression(
    id2205040_CSubsetParser::Rel_expressionContext *ctx)
{
    logRule(
        "rel_expression",
        ctx->getText());

    if (ctx->RELOP())
    {
        getType(
            visit(ctx->simple_expression(0)));

        getType(
            visit(ctx->simple_expression(1)));

        return makeValue(TYPE_INT);
    }

    return visit(ctx->simple_expression(0));
}

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

        if (leftType == TYPE_FLOAT ||
            rightType == TYPE_FLOAT)
        {
            return makeValue(TYPE_FLOAT);
        }

        return makeValue(TYPE_INT);
    }

    return visit(ctx->term());
}

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

        if (leftType == TYPE_FLOAT ||
            rightType == TYPE_FLOAT)
        {
            return makeValue(TYPE_FLOAT);
        }

        return makeValue(TYPE_INT);
    }

    return visit(ctx->unary_expression());
}

any SymbolTableVisitor::visitUnary_expression(
    id2205040_CSubsetParser::Unary_expressionContext *ctx)
{
    logRule(
        "unary_expression",
        ctx->getText());

    if (ctx->NOT())
    {
        getType(
            visit(ctx->unary_expression()));

        return makeValue(TYPE_INT);
    }

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

any SymbolTableVisitor::visitArguments(
    id2205040_CSubsetParser::ArgumentsContext *ctx)
{
    logRule(
        "arguments",
        ctx->getText());

    ArgVec argumentTypes;

    if (ctx->arguments())
    {
        argumentTypes =
            getArgumentTypes(
                visit(ctx->arguments()));
    }

    argumentTypes.push_back(
        getType(
            visit(ctx->logic_expression())));

    return makeArgumentTypes(argumentTypes);
}

any SymbolTableVisitor::visitFactor(
    id2205040_CSubsetParser::FactorContext *ctx)
{
    int line =
        ctx->getStart()->getLine();

    logRule(
        "factor",
        ctx->getText());

    if (ctx->CONST_INT())
    {
        return makeValue(TYPE_INT);
    }

    if (ctx->CONST_FLOAT())
    {
        return makeValue(TYPE_FLOAT);
    }

    if (ctx->LPAREN() &&
        ctx->expression())
    {
        return visit(ctx->expression());
    }

    if (ctx->ID())
    {
        string functionName =
            ctx->ID()->getText();

        SymbolInfo *function =
            findSymbol(functionName);

        if (!function)
        {
            semError(
                line,
                "Undeclared function '" +
                functionName +
                "'");

            return makeValue(TYPE_ERROR);
        }

        if (!function->isFunction)
        {
            semError(
                line,
                "'" +
                functionName +
                "' is not a function");

            return makeValue(TYPE_ERROR);
        }

        ArgVec argumentTypes;

        if (ctx->argument_list())
        {
            argumentTypes =
                getArgumentTypes(
                    visit(ctx->argument_list()));
        }

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

                    break;
                }
            }
        }

        if (function->type == TYPE_VOID)
        {
            semError(
                line,
                "Void function '" +
                functionName +
                "' used in an expression");
        }

        return makeValue(function->type);
    }

    if (ctx->variable())
    {
        string variableName =
            ctx->variable()->ID()->getText();

        SymbolInfo *symbol =
            findSymbol(variableName);

        if (symbol && symbol->isFunction)
        {
            semError(
                line,
                "'" +
                variableName +
                "' is a function used as a variable");

            return makeValue(TYPE_ERROR);
        }

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

    return makeValue(TYPE_ERROR);
}