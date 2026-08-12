#pragma once

#include <any>
#include <fstream>
#include <string>
#include <vector>
#include "CSubsetBaseVisitor.h"
#include "SymbolTable.h"

class SymbolTableVisitor : public CSubsetBaseVisitor {
public:
    SymbolTableVisitor(std::ofstream &logFile, std::ofstream &errorFile);
    ~SymbolTableVisitor();

    void printScopeTable();

    std::any visitStart(CSubsetParser::StartContext *ctx) override;
    std::any visitProgram(CSubsetParser::ProgramContext *ctx) override;
    std::any visitUnit(CSubsetParser::UnitContext *ctx) override;
    std::any visitFunc_declaration(CSubsetParser::Func_declarationContext *ctx) override;
    std::any visitFunc_definition(CSubsetParser::Func_definitionContext *ctx) override;
    std::any visitParameter_list(CSubsetParser::Parameter_listContext *ctx) override;
    std::any visitCompound_statement(CSubsetParser::Compound_statementContext *ctx) override;
    std::any visitVar_declaration(CSubsetParser::Var_declarationContext *ctx) override;
    std::any visitType_specifier(CSubsetParser::Type_specifierContext *ctx) override;
    std::any visitDeclaration_list(CSubsetParser::Declaration_listContext *ctx) override;
    std::any visitStatements(CSubsetParser::StatementsContext *ctx) override;
    std::any visitStatement(CSubsetParser::StatementContext *ctx) override;
    std::any visitExpression_statement(CSubsetParser::Expression_statementContext *ctx) override;
    std::any visitVariable(CSubsetParser::VariableContext *ctx) override;
    std::any visitExpression(CSubsetParser::ExpressionContext *ctx) override;
    std::any visitLogic_expression(CSubsetParser::Logic_expressionContext *ctx) override;
    std::any visitRel_expression(CSubsetParser::Rel_expressionContext *ctx) override;
    std::any visitSimple_expression(CSubsetParser::Simple_expressionContext *ctx) override;
    std::any visitTerm(CSubsetParser::TermContext *ctx) override;
    std::any visitUnary_expression(CSubsetParser::Unary_expressionContext *ctx) override;
    std::any visitFactor(CSubsetParser::FactorContext *ctx) override;
    std::any visitArgument_list(CSubsetParser::Argument_listContext *ctx) override;
    std::any visitArguments(CSubsetParser::ArgumentsContext *ctx) override;

private:
    std::ofstream &logFile;
    std::ofstream &errorFile;
    int errorCount;
    std::vector<SymbolTable> scopes;
    std::vector<SymbolInfo> pendingParams;

    void logRule(const std::string &rule, const std::string &code) const;
    void semError(int line, const std::string &msg);
    void semWarning(int line, const std::string &msg);
    SymbolInfo *findSymbol(const std::string &name);
    SymbolInfo *findGlobal(const std::string &name);
    std::vector<SymbolInfo> makeParamList(id2205040_CSubsetParser::Parameter_listContext *ctx);
};