// Generated from /home/s/auniversity/programimg/antlr/2205040dev/id2205040_CSubset.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link id2205040_CSubsetParser}.
 */
public interface id2205040_CSubsetListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(id2205040_CSubsetParser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(id2205040_CSubsetParser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(id2205040_CSubsetParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(id2205040_CSubsetParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#unit}.
	 * @param ctx the parse tree
	 */
	void enterUnit(id2205040_CSubsetParser.UnitContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#unit}.
	 * @param ctx the parse tree
	 */
	void exitUnit(id2205040_CSubsetParser.UnitContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void enterFunc_declaration(id2205040_CSubsetParser.Func_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#func_declaration}.
	 * @param ctx the parse tree
	 */
	void exitFunc_declaration(id2205040_CSubsetParser.Func_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#func_definition}.
	 * @param ctx the parse tree
	 */
	void enterFunc_definition(id2205040_CSubsetParser.Func_definitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#func_definition}.
	 * @param ctx the parse tree
	 */
	void exitFunc_definition(id2205040_CSubsetParser.Func_definitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void enterParameter_list(id2205040_CSubsetParser.Parameter_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#parameter_list}.
	 * @param ctx the parse tree
	 */
	void exitParameter_list(id2205040_CSubsetParser.Parameter_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void enterCompound_statement(id2205040_CSubsetParser.Compound_statementContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#compound_statement}.
	 * @param ctx the parse tree
	 */
	void exitCompound_statement(id2205040_CSubsetParser.Compound_statementContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#var_declaration}.
	 * @param ctx the parse tree
	 */
	void enterVar_declaration(id2205040_CSubsetParser.Var_declarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#var_declaration}.
	 * @param ctx the parse tree
	 */
	void exitVar_declaration(id2205040_CSubsetParser.Var_declarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void enterType_specifier(id2205040_CSubsetParser.Type_specifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#type_specifier}.
	 * @param ctx the parse tree
	 */
	void exitType_specifier(id2205040_CSubsetParser.Type_specifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration_list(id2205040_CSubsetParser.Declaration_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#declaration_list}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration_list(id2205040_CSubsetParser.Declaration_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#statements}.
	 * @param ctx the parse tree
	 */
	void enterStatements(id2205040_CSubsetParser.StatementsContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#statements}.
	 * @param ctx the parse tree
	 */
	void exitStatements(id2205040_CSubsetParser.StatementsContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(id2205040_CSubsetParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(id2205040_CSubsetParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void enterExpression_statement(id2205040_CSubsetParser.Expression_statementContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#expression_statement}.
	 * @param ctx the parse tree
	 */
	void exitExpression_statement(id2205040_CSubsetParser.Expression_statementContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#variable}.
	 * @param ctx the parse tree
	 */
	void enterVariable(id2205040_CSubsetParser.VariableContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#variable}.
	 * @param ctx the parse tree
	 */
	void exitVariable(id2205040_CSubsetParser.VariableContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(id2205040_CSubsetParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(id2205040_CSubsetParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void enterLogic_expression(id2205040_CSubsetParser.Logic_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#logic_expression}.
	 * @param ctx the parse tree
	 */
	void exitLogic_expression(id2205040_CSubsetParser.Logic_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void enterRel_expression(id2205040_CSubsetParser.Rel_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#rel_expression}.
	 * @param ctx the parse tree
	 */
	void exitRel_expression(id2205040_CSubsetParser.Rel_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void enterSimple_expression(id2205040_CSubsetParser.Simple_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#simple_expression}.
	 * @param ctx the parse tree
	 */
	void exitSimple_expression(id2205040_CSubsetParser.Simple_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(id2205040_CSubsetParser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(id2205040_CSubsetParser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void enterUnary_expression(id2205040_CSubsetParser.Unary_expressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#unary_expression}.
	 * @param ctx the parse tree
	 */
	void exitUnary_expression(id2205040_CSubsetParser.Unary_expressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactor(id2205040_CSubsetParser.FactorContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactor(id2205040_CSubsetParser.FactorContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#argument_list}.
	 * @param ctx the parse tree
	 */
	void enterArgument_list(id2205040_CSubsetParser.Argument_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#argument_list}.
	 * @param ctx the parse tree
	 */
	void exitArgument_list(id2205040_CSubsetParser.Argument_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link id2205040_CSubsetParser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArguments(id2205040_CSubsetParser.ArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link id2205040_CSubsetParser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArguments(id2205040_CSubsetParser.ArgumentsContext ctx);
}