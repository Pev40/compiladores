%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token IF THEN ELSE ENDIF CONCLUDE TRUE FALSE ID NUMBER
%token PLUS MINUS MUL DIV LPAREN RPAREN ASSIGN

%%

program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
    if_statement
    | assign_statement
    | conclude_statement
    ;

if_statement:
    IF expression THEN statements ELSE statements ENDIF
    | IF expression THEN statements ENDIF
    ;

assign_statement:
    ID ASSIGN expression
    ;

conclude_statement:
    CONCLUDE TRUE
    | CONCLUDE FALSE
    ;

expression:
    term
    | expression PLUS term
    | expression MINUS term
    ;

term:
    factor
    | term MUL factor
    | term DIV factor
    ;

factor:
    NUMBER
    | ID
    | LPAREN expression RPAREN
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
