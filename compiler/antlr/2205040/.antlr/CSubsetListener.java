// Generated from /home/s/auniversity/programimg/compiler/antlr/2205040/CSubset.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link CSubsetParser}.
 */
public interface CSubsetListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(CSubsetParser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(CSubsetParser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(CSubsetParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(CSubsetParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#unit}.
	 * @param ctx the parse tree
	 */
	void enterUnit(CSubsetParser.UnitContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#unit}.
	 * @param ctx the parse tree
	 */
	void exitUnit(CSubsetParser.UnitContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void enterFunc_declaration(CSubsetParser.Func_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void exitFunc_declaration(CSubsetParser.Func_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#func_definition}.
	 * @param ctx the parse tree
	 */
	void enterFunc_definition(CSubsetParser.Func_definitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#func_definition}.
	 * @param ctx the parse tree
	 */
	void exitFunc_definition(CSubsetParser.Func_definitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParameter_list(CSubsetParser.Parameter_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParameter_list(CSubsetParser.Parameter_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void enterCompound_statement(CSubsetParser.Compound_statementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void exitCompound_statement(CSubsetParser.Compound_statementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#var_declaration}.
	 * @param ctx the parse tree
	 */
	void enterVar_declaration(CSubsetParser.Var_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#var_declaration}.
	 * @param ctx the parse tree
	 */
	void exitVar_declaration(CSubsetParser.Var_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void enterType_specifier(CSubsetParser.Type_specifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void exitType_specifier(CSubsetParser.Type_specifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration_list(CSubsetParser.Declaration_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration_list(CSubsetParser.Declaration_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#statements}.
	 * @param ctx the parse tree
	 */
	void enterStatements(CSubsetParser.StatementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#statements}.
	 * @param ctx the parse tree
	 */
	void exitStatements(CSubsetParser.StatementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(CSubsetParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(CSubsetParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void enterExpression_statement(CSubsetParser.Expression_statementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void exitExpression_statement(CSubsetParser.Expression_statementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#variable}.
	 * @param ctx the parse tree
	 */
	void enterVariable(CSubsetParser.VariableContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#variable}.
	 * @param ctx the parse tree
	 */
	void exitVariable(CSubsetParser.VariableContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(CSubsetParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(CSubsetParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void enterLogic_expression(CSubsetParser.Logic_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void exitLogic_expression(CSubsetParser.Logic_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void enterRel_expression(CSubsetParser.Rel_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void exitRel_expression(CSubsetParser.Rel_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void enterSimple_expression(CSubsetParser.Simple_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void exitSimple_expression(CSubsetParser.Simple_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(CSubsetParser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(CSubsetParser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void enterUnary_expression(CSubsetParser.Unary_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void exitUnary_expression(CSubsetParser.Unary_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactor(CSubsetParser.FactorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactor(CSubsetParser.FactorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#argument_list}.
	 * @param ctx the parse tree
	 */
	void enterArgument_list(CSubsetParser.Argument_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#argument_list}.
	 * @param ctx the parse tree
	 */
	void exitArgument_list(CSubsetParser.Argument_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSubsetParser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArguments(CSubsetParser.ArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSubsetParser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArguments(CSubsetParser.ArgumentsContext ctx);
}