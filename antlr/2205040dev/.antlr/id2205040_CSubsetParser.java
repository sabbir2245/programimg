// Generated from /home/s/auniversity/programimg/antlr/2205040dev/id2205040_CSubset.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class id2205040_CSubsetParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		LINE_COMMENT=1, BLOCK_COMMENT=2, STRING=3, WS=4, IF=5, ELSE=6, FOR=7, 
		WHILE=8, PRINTLN=9, RETURN=10, INT=11, FLOAT=12, VOID=13, LPAREN=14, RPAREN=15, 
		LCURL=16, RCURL=17, LTHIRD=18, RTHIRD=19, SEMICOLON=20, COMMA=21, ADDOP=22, 
		MULOP=23, INCOP=24, DECOP=25, NOT=26, RELOP=27, LOGICOP=28, ASSIGNOP=29, 
		ID=30, CONST_INT=31, CONST_FLOAT=32;
	public static final int
		RULE_start = 0, RULE_program = 1, RULE_unit = 2, RULE_func_declaration = 3, 
		RULE_func_definition = 4, RULE_parameter_list = 5, RULE_compound_statement = 6, 
		RULE_var_declaration = 7, RULE_type_specifier = 8, RULE_declaration_list = 9, 
		RULE_statements = 10, RULE_statement = 11, RULE_expression_statement = 12, 
		RULE_variable = 13, RULE_expression = 14, RULE_logic_expression = 15, 
		RULE_rel_expression = 16, RULE_simple_expression = 17, RULE_term = 18, 
		RULE_unary_expression = 19, RULE_factor = 20, RULE_argument_list = 21, 
		RULE_arguments = 22;
	private static String[] makeRuleNames() {
		return new String[] {
			"start", "program", "unit", "func_declaration", "func_definition", "parameter_list", 
			"compound_statement", "var_declaration", "type_specifier", "declaration_list", 
			"statements", "statement", "expression_statement", "variable", "expression", 
			"logic_expression", "rel_expression", "simple_expression", "term", "unary_expression", 
			"factor", "argument_list", "arguments"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, null, null, "'if'", "'else'", "'for'", "'while'", "'printf'", 
			"'return'", "'int'", "'float'", "'void'", "'('", "')'", "'{'", "'}'", 
			"'['", "']'", "';'", "','", null, null, "'++'", "'--'", "'!'", null, 
			null, "'='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "LINE_COMMENT", "BLOCK_COMMENT", "STRING", "WS", "IF", "ELSE", 
			"FOR", "WHILE", "PRINTLN", "RETURN", "INT", "FLOAT", "VOID", "LPAREN", 
			"RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "SEMICOLON", "COMMA", 
			"ADDOP", "MULOP", "INCOP", "DECOP", "NOT", "RELOP", "LOGICOP", "ASSIGNOP", 
			"ID", "CONST_INT", "CONST_FLOAT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "id2205040_CSubset.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public id2205040_CSubsetParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StartContext extends ParserRuleContext {
		public ProgramContext program() {
			return getRuleContext(ProgramContext.class,0);
		}
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterStart(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitStart(this);
		}
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_start);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(46);
			program(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public UnitContext unit() {
			return getRuleContext(UnitContext.class,0);
		}
		public ProgramContext program() {
			return getRuleContext(ProgramContext.class,0);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitProgram(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		return program(0);
	}

	private ProgramContext program(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ProgramContext _localctx = new ProgramContext(_ctx, _parentState);
		ProgramContext _prevctx = _localctx;
		int _startState = 2;
		enterRecursionRule(_localctx, 2, RULE_program, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(49);
			unit();
			}
			_ctx.stop = _input.LT(-1);
			setState(55);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new ProgramContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_program);
					setState(51);
					if (!(precpred(_ctx, 2))) throw new FailedPredicateException(this, "precpred(_ctx, 2)");
					setState(52);
					unit();
					}
					} 
				}
				setState(57);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class UnitContext extends ParserRuleContext {
		public Var_declarationContext var_declaration() {
			return getRuleContext(Var_declarationContext.class,0);
		}
		public Func_declarationContext func_declaration() {
			return getRuleContext(Func_declarationContext.class,0);
		}
		public Func_definitionContext func_definition() {
			return getRuleContext(Func_definitionContext.class,0);
		}
		public UnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unit; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterUnit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitUnit(this);
		}
	}

	public final UnitContext unit() throws RecognitionException {
		UnitContext _localctx = new UnitContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_unit);
		try {
			setState(61);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(58);
				var_declaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(59);
				func_declaration();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(60);
				func_definition();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Func_declarationContext extends ParserRuleContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(id2205040_CSubsetParser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(id2205040_CSubsetParser.LPAREN, 0); }
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(id2205040_CSubsetParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(id2205040_CSubsetParser.SEMICOLON, 0); }
		public Func_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_func_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterFunc_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitFunc_declaration(this);
		}
	}

	public final Func_declarationContext func_declaration() throws RecognitionException {
		Func_declarationContext _localctx = new Func_declarationContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_func_declaration);
		try {
			setState(76);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(63);
				type_specifier();
				setState(64);
				match(ID);
				setState(65);
				match(LPAREN);
				setState(66);
				parameter_list(0);
				setState(67);
				match(RPAREN);
				setState(68);
				match(SEMICOLON);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(70);
				type_specifier();
				setState(71);
				match(ID);
				setState(72);
				match(LPAREN);
				setState(73);
				match(RPAREN);
				setState(74);
				match(SEMICOLON);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Func_definitionContext extends ParserRuleContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(id2205040_CSubsetParser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(id2205040_CSubsetParser.LPAREN, 0); }
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(id2205040_CSubsetParser.RPAREN, 0); }
		public Compound_statementContext compound_statement() {
			return getRuleContext(Compound_statementContext.class,0);
		}
		public Func_definitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_func_definition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterFunc_definition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitFunc_definition(this);
		}
	}

	public final Func_definitionContext func_definition() throws RecognitionException {
		Func_definitionContext _localctx = new Func_definitionContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_func_definition);
		try {
			setState(91);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(78);
				type_specifier();
				setState(79);
				match(ID);
				setState(80);
				match(LPAREN);
				setState(81);
				parameter_list(0);
				setState(82);
				match(RPAREN);
				setState(83);
				compound_statement();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(85);
				type_specifier();
				setState(86);
				match(ID);
				setState(87);
				match(LPAREN);
				setState(88);
				match(RPAREN);
				setState(89);
				compound_statement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Parameter_listContext extends ParserRuleContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public TerminalNode ID() { return getToken(id2205040_CSubsetParser.ID, 0); }
		public Parameter_listContext parameter_list() {
			return getRuleContext(Parameter_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(id2205040_CSubsetParser.COMMA, 0); }
		public Parameter_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parameter_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterParameter_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitParameter_list(this);
		}
	}

	public final Parameter_listContext parameter_list() throws RecognitionException {
		return parameter_list(0);
	}

	private Parameter_listContext parameter_list(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Parameter_listContext _localctx = new Parameter_listContext(_ctx, _parentState);
		Parameter_listContext _prevctx = _localctx;
		int _startState = 10;
		enterRecursionRule(_localctx, 10, RULE_parameter_list, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(98);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				{
				setState(94);
				type_specifier();
				setState(95);
				match(ID);
				}
				break;
			case 2:
				{
				setState(97);
				type_specifier();
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(110);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(108);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
					case 1:
						{
						_localctx = new Parameter_listContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_parameter_list);
						setState(100);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(101);
						match(COMMA);
						setState(102);
						type_specifier();
						setState(103);
						match(ID);
						}
						break;
					case 2:
						{
						_localctx = new Parameter_listContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_parameter_list);
						setState(105);
						if (!(precpred(_ctx, 3))) throw new FailedPredicateException(this, "precpred(_ctx, 3)");
						setState(106);
						match(COMMA);
						setState(107);
						type_specifier();
						}
						break;
					}
					} 
				}
				setState(112);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Compound_statementContext extends ParserRuleContext {
		public TerminalNode LCURL() { return getToken(id2205040_CSubsetParser.LCURL, 0); }
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public TerminalNode RCURL() { return getToken(id2205040_CSubsetParser.RCURL, 0); }
		public Compound_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compound_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterCompound_statement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitCompound_statement(this);
		}
	}

	public final Compound_statementContext compound_statement() throws RecognitionException {
		Compound_statementContext _localctx = new Compound_statementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_compound_statement);
		try {
			setState(119);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(113);
				match(LCURL);
				setState(114);
				statements(0);
				setState(115);
				match(RCURL);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(117);
				match(LCURL);
				setState(118);
				match(RCURL);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Var_declarationContext extends ParserRuleContext {
		public Type_specifierContext type_specifier() {
			return getRuleContext(Type_specifierContext.class,0);
		}
		public Declaration_listContext declaration_list() {
			return getRuleContext(Declaration_listContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(id2205040_CSubsetParser.SEMICOLON, 0); }
		public Var_declarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var_declaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterVar_declaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitVar_declaration(this);
		}
	}

	public final Var_declarationContext var_declaration() throws RecognitionException {
		Var_declarationContext _localctx = new Var_declarationContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_var_declaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			type_specifier();
			setState(122);
			declaration_list(0);
			setState(123);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_specifierContext extends ParserRuleContext {
		public TerminalNode INT() { return getToken(id2205040_CSubsetParser.INT, 0); }
		public TerminalNode FLOAT() { return getToken(id2205040_CSubsetParser.FLOAT, 0); }
		public TerminalNode VOID() { return getToken(id2205040_CSubsetParser.VOID, 0); }
		public Type_specifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_specifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterType_specifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitType_specifier(this);
		}
	}

	public final Type_specifierContext type_specifier() throws RecognitionException {
		Type_specifierContext _localctx = new Type_specifierContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_type_specifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(125);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 14336L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Declaration_listContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(id2205040_CSubsetParser.ID, 0); }
		public TerminalNode LTHIRD() { return getToken(id2205040_CSubsetParser.LTHIRD, 0); }
		public TerminalNode CONST_INT() { return getToken(id2205040_CSubsetParser.CONST_INT, 0); }
		public TerminalNode RTHIRD() { return getToken(id2205040_CSubsetParser.RTHIRD, 0); }
		public Declaration_listContext declaration_list() {
			return getRuleContext(Declaration_listContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(id2205040_CSubsetParser.COMMA, 0); }
		public Declaration_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterDeclaration_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitDeclaration_list(this);
		}
	}

	public final Declaration_listContext declaration_list() throws RecognitionException {
		return declaration_list(0);
	}

	private Declaration_listContext declaration_list(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Declaration_listContext _localctx = new Declaration_listContext(_ctx, _parentState);
		Declaration_listContext _prevctx = _localctx;
		int _startState = 18;
		enterRecursionRule(_localctx, 18, RULE_declaration_list, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(133);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				{
				setState(128);
				match(ID);
				}
				break;
			case 2:
				{
				setState(129);
				match(ID);
				setState(130);
				match(LTHIRD);
				setState(131);
				match(CONST_INT);
				setState(132);
				match(RTHIRD);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(146);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(144);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
					case 1:
						{
						_localctx = new Declaration_listContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_declaration_list);
						setState(135);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(136);
						match(COMMA);
						setState(137);
						match(ID);
						}
						break;
					case 2:
						{
						_localctx = new Declaration_listContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_declaration_list);
						setState(138);
						if (!(precpred(_ctx, 3))) throw new FailedPredicateException(this, "precpred(_ctx, 3)");
						setState(139);
						match(COMMA);
						setState(140);
						match(ID);
						setState(141);
						match(LTHIRD);
						setState(142);
						match(CONST_INT);
						setState(143);
						match(RTHIRD);
						}
						break;
					}
					} 
				}
				setState(148);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementsContext extends ParserRuleContext {
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public StatementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statements; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterStatements(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitStatements(this);
		}
	}

	public final StatementsContext statements() throws RecognitionException {
		return statements(0);
	}

	private StatementsContext statements(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		StatementsContext _localctx = new StatementsContext(_ctx, _parentState);
		StatementsContext _prevctx = _localctx;
		int _startState = 20;
		enterRecursionRule(_localctx, 20, RULE_statements, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(150);
			statement();
			}
			_ctx.stop = _input.LT(-1);
			setState(156);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new StatementsContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_statements);
					setState(152);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(153);
					statement();
					}
					} 
				}
				setState(158);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,11,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public Var_declarationContext var_declaration() {
			return getRuleContext(Var_declarationContext.class,0);
		}
		public List<Expression_statementContext> expression_statement() {
			return getRuleContexts(Expression_statementContext.class);
		}
		public Expression_statementContext expression_statement(int i) {
			return getRuleContext(Expression_statementContext.class,i);
		}
		public Compound_statementContext compound_statement() {
			return getRuleContext(Compound_statementContext.class,0);
		}
		public TerminalNode FOR() { return getToken(id2205040_CSubsetParser.FOR, 0); }
		public TerminalNode LPAREN() { return getToken(id2205040_CSubsetParser.LPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(id2205040_CSubsetParser.RPAREN, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public TerminalNode IF() { return getToken(id2205040_CSubsetParser.IF, 0); }
		public TerminalNode ELSE() { return getToken(id2205040_CSubsetParser.ELSE, 0); }
		public TerminalNode WHILE() { return getToken(id2205040_CSubsetParser.WHILE, 0); }
		public TerminalNode PRINTLN() { return getToken(id2205040_CSubsetParser.PRINTLN, 0); }
		public TerminalNode ID() { return getToken(id2205040_CSubsetParser.ID, 0); }
		public TerminalNode SEMICOLON() { return getToken(id2205040_CSubsetParser.SEMICOLON, 0); }
		public TerminalNode RETURN() { return getToken(id2205040_CSubsetParser.RETURN, 0); }
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitStatement(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_statement);
		try {
			setState(199);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(159);
				var_declaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(160);
				expression_statement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(161);
				compound_statement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(162);
				match(FOR);
				setState(163);
				match(LPAREN);
				setState(164);
				expression_statement();
				setState(165);
				expression_statement();
				setState(166);
				expression();
				setState(167);
				match(RPAREN);
				setState(168);
				statement();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(170);
				match(IF);
				setState(171);
				match(LPAREN);
				setState(172);
				expression();
				setState(173);
				match(RPAREN);
				setState(174);
				statement();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(176);
				match(IF);
				setState(177);
				match(LPAREN);
				setState(178);
				expression();
				setState(179);
				match(RPAREN);
				setState(180);
				statement();
				setState(181);
				match(ELSE);
				setState(182);
				statement();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(184);
				match(WHILE);
				setState(185);
				match(LPAREN);
				setState(186);
				expression();
				setState(187);
				match(RPAREN);
				setState(188);
				statement();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(190);
				match(PRINTLN);
				setState(191);
				match(LPAREN);
				setState(192);
				match(ID);
				setState(193);
				match(RPAREN);
				setState(194);
				match(SEMICOLON);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(195);
				match(RETURN);
				setState(196);
				expression();
				setState(197);
				match(SEMICOLON);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expression_statementContext extends ParserRuleContext {
		public TerminalNode SEMICOLON() { return getToken(id2205040_CSubsetParser.SEMICOLON, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public Expression_statementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterExpression_statement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitExpression_statement(this);
		}
	}

	public final Expression_statementContext expression_statement() throws RecognitionException {
		Expression_statementContext _localctx = new Expression_statementContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_expression_statement);
		try {
			setState(205);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SEMICOLON:
				enterOuterAlt(_localctx, 1);
				{
				setState(201);
				match(SEMICOLON);
				}
				break;
			case LPAREN:
			case ADDOP:
			case NOT:
			case ID:
			case CONST_INT:
			case CONST_FLOAT:
				enterOuterAlt(_localctx, 2);
				{
				setState(202);
				expression();
				setState(203);
				match(SEMICOLON);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VariableContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(id2205040_CSubsetParser.ID, 0); }
		public TerminalNode LTHIRD() { return getToken(id2205040_CSubsetParser.LTHIRD, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RTHIRD() { return getToken(id2205040_CSubsetParser.RTHIRD, 0); }
		public VariableContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variable; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterVariable(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitVariable(this);
		}
	}

	public final VariableContext variable() throws RecognitionException {
		VariableContext _localctx = new VariableContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_variable);
		try {
			setState(213);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(207);
				match(ID);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(208);
				match(ID);
				setState(209);
				match(LTHIRD);
				setState(210);
				expression();
				setState(211);
				match(RTHIRD);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionContext extends ParserRuleContext {
		public Logic_expressionContext logic_expression() {
			return getRuleContext(Logic_expressionContext.class,0);
		}
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public TerminalNode ASSIGNOP() { return getToken(id2205040_CSubsetParser.ASSIGNOP, 0); }
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitExpression(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_expression);
		try {
			setState(220);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(215);
				logic_expression();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(216);
				variable();
				setState(217);
				match(ASSIGNOP);
				setState(218);
				logic_expression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Logic_expressionContext extends ParserRuleContext {
		public List<Rel_expressionContext> rel_expression() {
			return getRuleContexts(Rel_expressionContext.class);
		}
		public Rel_expressionContext rel_expression(int i) {
			return getRuleContext(Rel_expressionContext.class,i);
		}
		public TerminalNode LOGICOP() { return getToken(id2205040_CSubsetParser.LOGICOP, 0); }
		public Logic_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_logic_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterLogic_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitLogic_expression(this);
		}
	}

	public final Logic_expressionContext logic_expression() throws RecognitionException {
		Logic_expressionContext _localctx = new Logic_expressionContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_logic_expression);
		try {
			setState(227);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(222);
				rel_expression();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(223);
				rel_expression();
				setState(224);
				match(LOGICOP);
				setState(225);
				rel_expression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Rel_expressionContext extends ParserRuleContext {
		public List<Simple_expressionContext> simple_expression() {
			return getRuleContexts(Simple_expressionContext.class);
		}
		public Simple_expressionContext simple_expression(int i) {
			return getRuleContext(Simple_expressionContext.class,i);
		}
		public TerminalNode RELOP() { return getToken(id2205040_CSubsetParser.RELOP, 0); }
		public Rel_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rel_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterRel_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitRel_expression(this);
		}
	}

	public final Rel_expressionContext rel_expression() throws RecognitionException {
		Rel_expressionContext _localctx = new Rel_expressionContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_rel_expression);
		try {
			setState(234);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,17,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(229);
				simple_expression(0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(230);
				simple_expression(0);
				setState(231);
				match(RELOP);
				setState(232);
				simple_expression(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Simple_expressionContext extends ParserRuleContext {
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public Simple_expressionContext simple_expression() {
			return getRuleContext(Simple_expressionContext.class,0);
		}
		public TerminalNode ADDOP() { return getToken(id2205040_CSubsetParser.ADDOP, 0); }
		public Simple_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_simple_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterSimple_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitSimple_expression(this);
		}
	}

	public final Simple_expressionContext simple_expression() throws RecognitionException {
		return simple_expression(0);
	}

	private Simple_expressionContext simple_expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		Simple_expressionContext _localctx = new Simple_expressionContext(_ctx, _parentState);
		Simple_expressionContext _prevctx = _localctx;
		int _startState = 34;
		enterRecursionRule(_localctx, 34, RULE_simple_expression, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(237);
			term(0);
			}
			_ctx.stop = _input.LT(-1);
			setState(244);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new Simple_expressionContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_simple_expression);
					setState(239);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(240);
					match(ADDOP);
					setState(241);
					term(0);
					}
					} 
				}
				setState(246);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TermContext extends ParserRuleContext {
		public Unary_expressionContext unary_expression() {
			return getRuleContext(Unary_expressionContext.class,0);
		}
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public TerminalNode MULOP() { return getToken(id2205040_CSubsetParser.MULOP, 0); }
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterTerm(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitTerm(this);
		}
	}

	public final TermContext term() throws RecognitionException {
		return term(0);
	}

	private TermContext term(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		TermContext _localctx = new TermContext(_ctx, _parentState);
		TermContext _prevctx = _localctx;
		int _startState = 36;
		enterRecursionRule(_localctx, 36, RULE_term, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(248);
			unary_expression();
			}
			_ctx.stop = _input.LT(-1);
			setState(255);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new TermContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_term);
					setState(250);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(251);
					match(MULOP);
					setState(252);
					unary_expression();
					}
					} 
				}
				setState(257);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Unary_expressionContext extends ParserRuleContext {
		public TerminalNode ADDOP() { return getToken(id2205040_CSubsetParser.ADDOP, 0); }
		public Unary_expressionContext unary_expression() {
			return getRuleContext(Unary_expressionContext.class,0);
		}
		public TerminalNode NOT() { return getToken(id2205040_CSubsetParser.NOT, 0); }
		public FactorContext factor() {
			return getRuleContext(FactorContext.class,0);
		}
		public Unary_expressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unary_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterUnary_expression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitUnary_expression(this);
		}
	}

	public final Unary_expressionContext unary_expression() throws RecognitionException {
		Unary_expressionContext _localctx = new Unary_expressionContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_unary_expression);
		try {
			setState(263);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case ADDOP:
				enterOuterAlt(_localctx, 1);
				{
				setState(258);
				match(ADDOP);
				setState(259);
				unary_expression();
				}
				break;
			case NOT:
				enterOuterAlt(_localctx, 2);
				{
				setState(260);
				match(NOT);
				setState(261);
				unary_expression();
				}
				break;
			case LPAREN:
			case ID:
			case CONST_INT:
			case CONST_FLOAT:
				enterOuterAlt(_localctx, 3);
				{
				setState(262);
				factor();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FactorContext extends ParserRuleContext {
		public VariableContext variable() {
			return getRuleContext(VariableContext.class,0);
		}
		public TerminalNode ID() { return getToken(id2205040_CSubsetParser.ID, 0); }
		public TerminalNode LPAREN() { return getToken(id2205040_CSubsetParser.LPAREN, 0); }
		public Argument_listContext argument_list() {
			return getRuleContext(Argument_listContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(id2205040_CSubsetParser.RPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode CONST_INT() { return getToken(id2205040_CSubsetParser.CONST_INT, 0); }
		public TerminalNode CONST_FLOAT() { return getToken(id2205040_CSubsetParser.CONST_FLOAT, 0); }
		public TerminalNode INCOP() { return getToken(id2205040_CSubsetParser.INCOP, 0); }
		public TerminalNode DECOP() { return getToken(id2205040_CSubsetParser.DECOP, 0); }
		public FactorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_factor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterFactor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitFactor(this);
		}
	}

	public final FactorContext factor() throws RecognitionException {
		FactorContext _localctx = new FactorContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_factor);
		try {
			setState(283);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(265);
				variable();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(266);
				match(ID);
				setState(267);
				match(LPAREN);
				setState(268);
				argument_list();
				setState(269);
				match(RPAREN);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(271);
				match(LPAREN);
				setState(272);
				expression();
				setState(273);
				match(RPAREN);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(275);
				match(CONST_INT);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(276);
				match(CONST_FLOAT);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(277);
				variable();
				setState(278);
				match(INCOP);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(280);
				variable();
				setState(281);
				match(DECOP);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Argument_listContext extends ParserRuleContext {
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public Argument_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argument_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterArgument_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitArgument_list(this);
		}
	}

	public final Argument_listContext argument_list() throws RecognitionException {
		Argument_listContext _localctx = new Argument_listContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_argument_list);
		try {
			setState(287);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LPAREN:
			case ADDOP:
			case NOT:
			case ID:
			case CONST_INT:
			case CONST_FLOAT:
				enterOuterAlt(_localctx, 1);
				{
				setState(285);
				arguments(0);
				}
				break;
			case RPAREN:
				enterOuterAlt(_localctx, 2);
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgumentsContext extends ParserRuleContext {
		public Logic_expressionContext logic_expression() {
			return getRuleContext(Logic_expressionContext.class,0);
		}
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(id2205040_CSubsetParser.COMMA, 0); }
		public ArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arguments; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).enterArguments(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof id2205040_CSubsetListener ) ((id2205040_CSubsetListener)listener).exitArguments(this);
		}
	}

	public final ArgumentsContext arguments() throws RecognitionException {
		return arguments(0);
	}

	private ArgumentsContext arguments(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ArgumentsContext _localctx = new ArgumentsContext(_ctx, _parentState);
		ArgumentsContext _prevctx = _localctx;
		int _startState = 44;
		enterRecursionRule(_localctx, 44, RULE_arguments, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(290);
			logic_expression();
			}
			_ctx.stop = _input.LT(-1);
			setState(297);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,23,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new ArgumentsContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_arguments);
					setState(292);
					if (!(precpred(_ctx, 2))) throw new FailedPredicateException(this, "precpred(_ctx, 2)");
					setState(293);
					match(COMMA);
					setState(294);
					logic_expression();
					}
					} 
				}
				setState(299);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,23,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 1:
			return program_sempred((ProgramContext)_localctx, predIndex);
		case 5:
			return parameter_list_sempred((Parameter_listContext)_localctx, predIndex);
		case 9:
			return declaration_list_sempred((Declaration_listContext)_localctx, predIndex);
		case 10:
			return statements_sempred((StatementsContext)_localctx, predIndex);
		case 17:
			return simple_expression_sempred((Simple_expressionContext)_localctx, predIndex);
		case 18:
			return term_sempred((TermContext)_localctx, predIndex);
		case 22:
			return arguments_sempred((ArgumentsContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean program_sempred(ProgramContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 2);
		}
		return true;
	}
	private boolean parameter_list_sempred(Parameter_listContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1:
			return precpred(_ctx, 4);
		case 2:
			return precpred(_ctx, 3);
		}
		return true;
	}
	private boolean declaration_list_sempred(Declaration_listContext _localctx, int predIndex) {
		switch (predIndex) {
		case 3:
			return precpred(_ctx, 4);
		case 4:
			return precpred(_ctx, 3);
		}
		return true;
	}
	private boolean statements_sempred(StatementsContext _localctx, int predIndex) {
		switch (predIndex) {
		case 5:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean simple_expression_sempred(Simple_expressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 6:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean term_sempred(TermContext _localctx, int predIndex) {
		switch (predIndex) {
		case 7:
			return precpred(_ctx, 1);
		}
		return true;
	}
	private boolean arguments_sempred(ArgumentsContext _localctx, int predIndex) {
		switch (predIndex) {
		case 8:
			return precpred(_ctx, 2);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001 \u012d\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0005\u00016\b\u0001\n\u0001\f\u0001"+
		"9\t\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0003\u0002>\b\u0002\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0003\u0003M\b\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0003\u0004\\\b\u0004\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0003\u0005c\b"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0005\u0005m\b\u0005\n\u0005\f\u0005p\t"+
		"\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001"+
		"\u0006\u0003\u0006x\b\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t"+
		"\u0003\t\u0086\b\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0005\t\u0091\b\t\n\t\f\t\u0094\t\t\u0001\n\u0001\n"+
		"\u0001\n\u0001\n\u0001\n\u0005\n\u009b\b\n\n\n\f\n\u009e\t\n\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u00c8\b\u000b\u0001\f"+
		"\u0001\f\u0001\f\u0001\f\u0003\f\u00ce\b\f\u0001\r\u0001\r\u0001\r\u0001"+
		"\r\u0001\r\u0001\r\u0003\r\u00d6\b\r\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0003\u000e\u00dd\b\u000e\u0001\u000f\u0001\u000f"+
		"\u0001\u000f\u0001\u000f\u0001\u000f\u0003\u000f\u00e4\b\u000f\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0003\u0010\u00eb\b\u0010"+
		"\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011"+
		"\u0005\u0011\u00f3\b\u0011\n\u0011\f\u0011\u00f6\t\u0011\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0005\u0012\u00fe"+
		"\b\u0012\n\u0012\f\u0012\u0101\t\u0012\u0001\u0013\u0001\u0013\u0001\u0013"+
		"\u0001\u0013\u0001\u0013\u0003\u0013\u0108\b\u0013\u0001\u0014\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0003\u0014\u011c\b\u0014"+
		"\u0001\u0015\u0001\u0015\u0003\u0015\u0120\b\u0015\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0005\u0016\u0128\b\u0016"+
		"\n\u0016\f\u0016\u012b\t\u0016\u0001\u0016\u0000\u0007\u0002\n\u0012\u0014"+
		"\"$,\u0017\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016"+
		"\u0018\u001a\u001c\u001e \"$&(*,\u0000\u0001\u0001\u0000\u000b\r\u013b"+
		"\u0000.\u0001\u0000\u0000\u0000\u00020\u0001\u0000\u0000\u0000\u0004="+
		"\u0001\u0000\u0000\u0000\u0006L\u0001\u0000\u0000\u0000\b[\u0001\u0000"+
		"\u0000\u0000\nb\u0001\u0000\u0000\u0000\fw\u0001\u0000\u0000\u0000\u000e"+
		"y\u0001\u0000\u0000\u0000\u0010}\u0001\u0000\u0000\u0000\u0012\u0085\u0001"+
		"\u0000\u0000\u0000\u0014\u0095\u0001\u0000\u0000\u0000\u0016\u00c7\u0001"+
		"\u0000\u0000\u0000\u0018\u00cd\u0001\u0000\u0000\u0000\u001a\u00d5\u0001"+
		"\u0000\u0000\u0000\u001c\u00dc\u0001\u0000\u0000\u0000\u001e\u00e3\u0001"+
		"\u0000\u0000\u0000 \u00ea\u0001\u0000\u0000\u0000\"\u00ec\u0001\u0000"+
		"\u0000\u0000$\u00f7\u0001\u0000\u0000\u0000&\u0107\u0001\u0000\u0000\u0000"+
		"(\u011b\u0001\u0000\u0000\u0000*\u011f\u0001\u0000\u0000\u0000,\u0121"+
		"\u0001\u0000\u0000\u0000./\u0003\u0002\u0001\u0000/\u0001\u0001\u0000"+
		"\u0000\u000001\u0006\u0001\uffff\uffff\u000012\u0003\u0004\u0002\u0000"+
		"27\u0001\u0000\u0000\u000034\n\u0002\u0000\u000046\u0003\u0004\u0002\u0000"+
		"53\u0001\u0000\u0000\u000069\u0001\u0000\u0000\u000075\u0001\u0000\u0000"+
		"\u000078\u0001\u0000\u0000\u00008\u0003\u0001\u0000\u0000\u000097\u0001"+
		"\u0000\u0000\u0000:>\u0003\u000e\u0007\u0000;>\u0003\u0006\u0003\u0000"+
		"<>\u0003\b\u0004\u0000=:\u0001\u0000\u0000\u0000=;\u0001\u0000\u0000\u0000"+
		"=<\u0001\u0000\u0000\u0000>\u0005\u0001\u0000\u0000\u0000?@\u0003\u0010"+
		"\b\u0000@A\u0005\u001e\u0000\u0000AB\u0005\u000e\u0000\u0000BC\u0003\n"+
		"\u0005\u0000CD\u0005\u000f\u0000\u0000DE\u0005\u0014\u0000\u0000EM\u0001"+
		"\u0000\u0000\u0000FG\u0003\u0010\b\u0000GH\u0005\u001e\u0000\u0000HI\u0005"+
		"\u000e\u0000\u0000IJ\u0005\u000f\u0000\u0000JK\u0005\u0014\u0000\u0000"+
		"KM\u0001\u0000\u0000\u0000L?\u0001\u0000\u0000\u0000LF\u0001\u0000\u0000"+
		"\u0000M\u0007\u0001\u0000\u0000\u0000NO\u0003\u0010\b\u0000OP\u0005\u001e"+
		"\u0000\u0000PQ\u0005\u000e\u0000\u0000QR\u0003\n\u0005\u0000RS\u0005\u000f"+
		"\u0000\u0000ST\u0003\f\u0006\u0000T\\\u0001\u0000\u0000\u0000UV\u0003"+
		"\u0010\b\u0000VW\u0005\u001e\u0000\u0000WX\u0005\u000e\u0000\u0000XY\u0005"+
		"\u000f\u0000\u0000YZ\u0003\f\u0006\u0000Z\\\u0001\u0000\u0000\u0000[N"+
		"\u0001\u0000\u0000\u0000[U\u0001\u0000\u0000\u0000\\\t\u0001\u0000\u0000"+
		"\u0000]^\u0006\u0005\uffff\uffff\u0000^_\u0003\u0010\b\u0000_`\u0005\u001e"+
		"\u0000\u0000`c\u0001\u0000\u0000\u0000ac\u0003\u0010\b\u0000b]\u0001\u0000"+
		"\u0000\u0000ba\u0001\u0000\u0000\u0000cn\u0001\u0000\u0000\u0000de\n\u0004"+
		"\u0000\u0000ef\u0005\u0015\u0000\u0000fg\u0003\u0010\b\u0000gh\u0005\u001e"+
		"\u0000\u0000hm\u0001\u0000\u0000\u0000ij\n\u0003\u0000\u0000jk\u0005\u0015"+
		"\u0000\u0000km\u0003\u0010\b\u0000ld\u0001\u0000\u0000\u0000li\u0001\u0000"+
		"\u0000\u0000mp\u0001\u0000\u0000\u0000nl\u0001\u0000\u0000\u0000no\u0001"+
		"\u0000\u0000\u0000o\u000b\u0001\u0000\u0000\u0000pn\u0001\u0000\u0000"+
		"\u0000qr\u0005\u0010\u0000\u0000rs\u0003\u0014\n\u0000st\u0005\u0011\u0000"+
		"\u0000tx\u0001\u0000\u0000\u0000uv\u0005\u0010\u0000\u0000vx\u0005\u0011"+
		"\u0000\u0000wq\u0001\u0000\u0000\u0000wu\u0001\u0000\u0000\u0000x\r\u0001"+
		"\u0000\u0000\u0000yz\u0003\u0010\b\u0000z{\u0003\u0012\t\u0000{|\u0005"+
		"\u0014\u0000\u0000|\u000f\u0001\u0000\u0000\u0000}~\u0007\u0000\u0000"+
		"\u0000~\u0011\u0001\u0000\u0000\u0000\u007f\u0080\u0006\t\uffff\uffff"+
		"\u0000\u0080\u0086\u0005\u001e\u0000\u0000\u0081\u0082\u0005\u001e\u0000"+
		"\u0000\u0082\u0083\u0005\u0012\u0000\u0000\u0083\u0084\u0005\u001f\u0000"+
		"\u0000\u0084\u0086\u0005\u0013\u0000\u0000\u0085\u007f\u0001\u0000\u0000"+
		"\u0000\u0085\u0081\u0001\u0000\u0000\u0000\u0086\u0092\u0001\u0000\u0000"+
		"\u0000\u0087\u0088\n\u0004\u0000\u0000\u0088\u0089\u0005\u0015\u0000\u0000"+
		"\u0089\u0091\u0005\u001e\u0000\u0000\u008a\u008b\n\u0003\u0000\u0000\u008b"+
		"\u008c\u0005\u0015\u0000\u0000\u008c\u008d\u0005\u001e\u0000\u0000\u008d"+
		"\u008e\u0005\u0012\u0000\u0000\u008e\u008f\u0005\u001f\u0000\u0000\u008f"+
		"\u0091\u0005\u0013\u0000\u0000\u0090\u0087\u0001\u0000\u0000\u0000\u0090"+
		"\u008a\u0001\u0000\u0000\u0000\u0091\u0094\u0001\u0000\u0000\u0000\u0092"+
		"\u0090\u0001\u0000\u0000\u0000\u0092\u0093\u0001\u0000\u0000\u0000\u0093"+
		"\u0013\u0001\u0000\u0000\u0000\u0094\u0092\u0001\u0000\u0000\u0000\u0095"+
		"\u0096\u0006\n\uffff\uffff\u0000\u0096\u0097\u0003\u0016\u000b\u0000\u0097"+
		"\u009c\u0001\u0000\u0000\u0000\u0098\u0099\n\u0001\u0000\u0000\u0099\u009b"+
		"\u0003\u0016\u000b\u0000\u009a\u0098\u0001\u0000\u0000\u0000\u009b\u009e"+
		"\u0001\u0000\u0000\u0000\u009c\u009a\u0001\u0000\u0000\u0000\u009c\u009d"+
		"\u0001\u0000\u0000\u0000\u009d\u0015\u0001\u0000\u0000\u0000\u009e\u009c"+
		"\u0001\u0000\u0000\u0000\u009f\u00c8\u0003\u000e\u0007\u0000\u00a0\u00c8"+
		"\u0003\u0018\f\u0000\u00a1\u00c8\u0003\f\u0006\u0000\u00a2\u00a3\u0005"+
		"\u0007\u0000\u0000\u00a3\u00a4\u0005\u000e\u0000\u0000\u00a4\u00a5\u0003"+
		"\u0018\f\u0000\u00a5\u00a6\u0003\u0018\f\u0000\u00a6\u00a7\u0003\u001c"+
		"\u000e\u0000\u00a7\u00a8\u0005\u000f\u0000\u0000\u00a8\u00a9\u0003\u0016"+
		"\u000b\u0000\u00a9\u00c8\u0001\u0000\u0000\u0000\u00aa\u00ab\u0005\u0005"+
		"\u0000\u0000\u00ab\u00ac\u0005\u000e\u0000\u0000\u00ac\u00ad\u0003\u001c"+
		"\u000e\u0000\u00ad\u00ae\u0005\u000f\u0000\u0000\u00ae\u00af\u0003\u0016"+
		"\u000b\u0000\u00af\u00c8\u0001\u0000\u0000\u0000\u00b0\u00b1\u0005\u0005"+
		"\u0000\u0000\u00b1\u00b2\u0005\u000e\u0000\u0000\u00b2\u00b3\u0003\u001c"+
		"\u000e\u0000\u00b3\u00b4\u0005\u000f\u0000\u0000\u00b4\u00b5\u0003\u0016"+
		"\u000b\u0000\u00b5\u00b6\u0005\u0006\u0000\u0000\u00b6\u00b7\u0003\u0016"+
		"\u000b\u0000\u00b7\u00c8\u0001\u0000\u0000\u0000\u00b8\u00b9\u0005\b\u0000"+
		"\u0000\u00b9\u00ba\u0005\u000e\u0000\u0000\u00ba\u00bb\u0003\u001c\u000e"+
		"\u0000\u00bb\u00bc\u0005\u000f\u0000\u0000\u00bc\u00bd\u0003\u0016\u000b"+
		"\u0000\u00bd\u00c8\u0001\u0000\u0000\u0000\u00be\u00bf\u0005\t\u0000\u0000"+
		"\u00bf\u00c0\u0005\u000e\u0000\u0000\u00c0\u00c1\u0005\u001e\u0000\u0000"+
		"\u00c1\u00c2\u0005\u000f\u0000\u0000\u00c2\u00c8\u0005\u0014\u0000\u0000"+
		"\u00c3\u00c4\u0005\n\u0000\u0000\u00c4\u00c5\u0003\u001c\u000e\u0000\u00c5"+
		"\u00c6\u0005\u0014\u0000\u0000\u00c6\u00c8\u0001\u0000\u0000\u0000\u00c7"+
		"\u009f\u0001\u0000\u0000\u0000\u00c7\u00a0\u0001\u0000\u0000\u0000\u00c7"+
		"\u00a1\u0001\u0000\u0000\u0000\u00c7\u00a2\u0001\u0000\u0000\u0000\u00c7"+
		"\u00aa\u0001\u0000\u0000\u0000\u00c7\u00b0\u0001\u0000\u0000\u0000\u00c7"+
		"\u00b8\u0001\u0000\u0000\u0000\u00c7\u00be\u0001\u0000\u0000\u0000\u00c7"+
		"\u00c3\u0001\u0000\u0000\u0000\u00c8\u0017\u0001\u0000\u0000\u0000\u00c9"+
		"\u00ce\u0005\u0014\u0000\u0000\u00ca\u00cb\u0003\u001c\u000e\u0000\u00cb"+
		"\u00cc\u0005\u0014\u0000\u0000\u00cc\u00ce\u0001\u0000\u0000\u0000\u00cd"+
		"\u00c9\u0001\u0000\u0000\u0000\u00cd\u00ca\u0001\u0000\u0000\u0000\u00ce"+
		"\u0019\u0001\u0000\u0000\u0000\u00cf\u00d6\u0005\u001e\u0000\u0000\u00d0"+
		"\u00d1\u0005\u001e\u0000\u0000\u00d1\u00d2\u0005\u0012\u0000\u0000\u00d2"+
		"\u00d3\u0003\u001c\u000e\u0000\u00d3\u00d4\u0005\u0013\u0000\u0000\u00d4"+
		"\u00d6\u0001\u0000\u0000\u0000\u00d5\u00cf\u0001\u0000\u0000\u0000\u00d5"+
		"\u00d0\u0001\u0000\u0000\u0000\u00d6\u001b\u0001\u0000\u0000\u0000\u00d7"+
		"\u00dd\u0003\u001e\u000f\u0000\u00d8\u00d9\u0003\u001a\r\u0000\u00d9\u00da"+
		"\u0005\u001d\u0000\u0000\u00da\u00db\u0003\u001e\u000f\u0000\u00db\u00dd"+
		"\u0001\u0000\u0000\u0000\u00dc\u00d7\u0001\u0000\u0000\u0000\u00dc\u00d8"+
		"\u0001\u0000\u0000\u0000\u00dd\u001d\u0001\u0000\u0000\u0000\u00de\u00e4"+
		"\u0003 \u0010\u0000\u00df\u00e0\u0003 \u0010\u0000\u00e0\u00e1\u0005\u001c"+
		"\u0000\u0000\u00e1\u00e2\u0003 \u0010\u0000\u00e2\u00e4\u0001\u0000\u0000"+
		"\u0000\u00e3\u00de\u0001\u0000\u0000\u0000\u00e3\u00df\u0001\u0000\u0000"+
		"\u0000\u00e4\u001f\u0001\u0000\u0000\u0000\u00e5\u00eb\u0003\"\u0011\u0000"+
		"\u00e6\u00e7\u0003\"\u0011\u0000\u00e7\u00e8\u0005\u001b\u0000\u0000\u00e8"+
		"\u00e9\u0003\"\u0011\u0000\u00e9\u00eb\u0001\u0000\u0000\u0000\u00ea\u00e5"+
		"\u0001\u0000\u0000\u0000\u00ea\u00e6\u0001\u0000\u0000\u0000\u00eb!\u0001"+
		"\u0000\u0000\u0000\u00ec\u00ed\u0006\u0011\uffff\uffff\u0000\u00ed\u00ee"+
		"\u0003$\u0012\u0000\u00ee\u00f4\u0001\u0000\u0000\u0000\u00ef\u00f0\n"+
		"\u0001\u0000\u0000\u00f0\u00f1\u0005\u0016\u0000\u0000\u00f1\u00f3\u0003"+
		"$\u0012\u0000\u00f2\u00ef\u0001\u0000\u0000\u0000\u00f3\u00f6\u0001\u0000"+
		"\u0000\u0000\u00f4\u00f2\u0001\u0000\u0000\u0000\u00f4\u00f5\u0001\u0000"+
		"\u0000\u0000\u00f5#\u0001\u0000\u0000\u0000\u00f6\u00f4\u0001\u0000\u0000"+
		"\u0000\u00f7\u00f8\u0006\u0012\uffff\uffff\u0000\u00f8\u00f9\u0003&\u0013"+
		"\u0000\u00f9\u00ff\u0001\u0000\u0000\u0000\u00fa\u00fb\n\u0001\u0000\u0000"+
		"\u00fb\u00fc\u0005\u0017\u0000\u0000\u00fc\u00fe\u0003&\u0013\u0000\u00fd"+
		"\u00fa\u0001\u0000\u0000\u0000\u00fe\u0101\u0001\u0000\u0000\u0000\u00ff"+
		"\u00fd\u0001\u0000\u0000\u0000\u00ff\u0100\u0001\u0000\u0000\u0000\u0100"+
		"%\u0001\u0000\u0000\u0000\u0101\u00ff\u0001\u0000\u0000\u0000\u0102\u0103"+
		"\u0005\u0016\u0000\u0000\u0103\u0108\u0003&\u0013\u0000\u0104\u0105\u0005"+
		"\u001a\u0000\u0000\u0105\u0108\u0003&\u0013\u0000\u0106\u0108\u0003(\u0014"+
		"\u0000\u0107\u0102\u0001\u0000\u0000\u0000\u0107\u0104\u0001\u0000\u0000"+
		"\u0000\u0107\u0106\u0001\u0000\u0000\u0000\u0108\'\u0001\u0000\u0000\u0000"+
		"\u0109\u011c\u0003\u001a\r\u0000\u010a\u010b\u0005\u001e\u0000\u0000\u010b"+
		"\u010c\u0005\u000e\u0000\u0000\u010c\u010d\u0003*\u0015\u0000\u010d\u010e"+
		"\u0005\u000f\u0000\u0000\u010e\u011c\u0001\u0000\u0000\u0000\u010f\u0110"+
		"\u0005\u000e\u0000\u0000\u0110\u0111\u0003\u001c\u000e\u0000\u0111\u0112"+
		"\u0005\u000f\u0000\u0000\u0112\u011c\u0001\u0000\u0000\u0000\u0113\u011c"+
		"\u0005\u001f\u0000\u0000\u0114\u011c\u0005 \u0000\u0000\u0115\u0116\u0003"+
		"\u001a\r\u0000\u0116\u0117\u0005\u0018\u0000\u0000\u0117\u011c\u0001\u0000"+
		"\u0000\u0000\u0118\u0119\u0003\u001a\r\u0000\u0119\u011a\u0005\u0019\u0000"+
		"\u0000\u011a\u011c\u0001\u0000\u0000\u0000\u011b\u0109\u0001\u0000\u0000"+
		"\u0000\u011b\u010a\u0001\u0000\u0000\u0000\u011b\u010f\u0001\u0000\u0000"+
		"\u0000\u011b\u0113\u0001\u0000\u0000\u0000\u011b\u0114\u0001\u0000\u0000"+
		"\u0000\u011b\u0115\u0001\u0000\u0000\u0000\u011b\u0118\u0001\u0000\u0000"+
		"\u0000\u011c)\u0001\u0000\u0000\u0000\u011d\u0120\u0003,\u0016\u0000\u011e"+
		"\u0120\u0001\u0000\u0000\u0000\u011f\u011d\u0001\u0000\u0000\u0000\u011f"+
		"\u011e\u0001\u0000\u0000\u0000\u0120+\u0001\u0000\u0000\u0000\u0121\u0122"+
		"\u0006\u0016\uffff\uffff\u0000\u0122\u0123\u0003\u001e\u000f\u0000\u0123"+
		"\u0129\u0001\u0000\u0000\u0000\u0124\u0125\n\u0002\u0000\u0000\u0125\u0126"+
		"\u0005\u0015\u0000\u0000\u0126\u0128\u0003\u001e\u000f\u0000\u0127\u0124"+
		"\u0001\u0000\u0000\u0000\u0128\u012b\u0001\u0000\u0000\u0000\u0129\u0127"+
		"\u0001\u0000\u0000\u0000\u0129\u012a\u0001\u0000\u0000\u0000\u012a-\u0001"+
		"\u0000\u0000\u0000\u012b\u0129\u0001\u0000\u0000\u0000\u00187=L[blnw\u0085"+
		"\u0090\u0092\u009c\u00c7\u00cd\u00d5\u00dc\u00e3\u00ea\u00f4\u00ff\u0107"+
		"\u011b\u011f\u0129";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}