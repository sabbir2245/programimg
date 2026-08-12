lexer grammar Lexer;

// filename lexer.g4

INT: [0-9]+ ;
PLUS: '+' ;
TIMES: '*' ;
LPAREN: '(';
RPAREN: ')';

WS: [ \r\n]+ -> skip ;
