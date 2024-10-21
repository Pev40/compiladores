%{
#include "parser.tab.h"
%}

DIGIT       [0-9]
ID          [a-zA-Z_][a-zA-Z0-9_]*

%%

"if"        { return IF; }
"then"      { return THEN; }
"else"      { return ELSE; }
"endif"     { return ENDIF; }
"conclude"  { return CONCLUDE; }
"true"      { return TRUE; }
"false"     { return FALSE; }

{ID}        { yylval.sval = strdup(yytext); return ID; }
{DIGIT}+    { yylval.ival = atoi(yytext); return NUMBER; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }

"("         { return LPAREN; }
")"         { return RPAREN; }
"="         { return ASSIGN; }

[ \t\n]+    { /* Ignorar espacios en blanco */ }

.           { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
