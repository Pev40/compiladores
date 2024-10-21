#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define IDENTIFICADOR 256
#define NUMERO 257
#define SUMA 258
#define RESTA 259
#define MULTIPLICACION 260
#define DIVISION 261
#define MAYOR 262
#define MAYOR_IGUAL 263
#define MENOR 264
#define MENOR_IGUAL 265
#define ASIGNACION 266
#define IGUALDAD 267
#define DIFERENTE 268
#define PARENTESIS_IZQ 269
#define PARENTESIS_DER 270
#define CORCHETE_IZQ 271
#define CORCHETE_DER 272
#define COMA 273
#define PUNTO_Y_COMA 274
#define LLAVE_IZQ 275
#define LLAVE_DER 276
#define MIENTRAS 277
#define SI 278

int analizadorLexico();
void mostrarToken(int token);

FILE *f;
char lexema[80];

int main(int argc, char *argv[])
{
    int token;
    f = stdin; // entrada estándar del teclado
    if (argc == 2) // si se especificó un archivo de lectura
    {
        f = fopen(argv[1], "r"); // lectura modo texto
        if (f == NULL)
            f = stdin;
    }
    if (f == stdin) // la lectura será desde la entrada estándar
        printf("Ingrese texto ........ termine con Ctrl z \n");

    while (1)
    {
        token = analizadorLexico();
        if (token == EOF)
            break;
        mostrarToken(token);
    }

    if (f != stdin) // si la entrada fue de un archivo
        fclose(f);  // entonces cerrar el archivo.

    return 0;
}

int analizadorLexico()
{
    int c;
    int i;
    do
        c = fgetc(f);
    while (isspace(c)); // ignora blancos

    if (c == EOF)
        return EOF;

    if (isalpha(c)) // regla del IDENTIFICADOR
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isalnum(c) || c == '_');

        lexema[i] = '\0';
        ungetc(c, f);   // se devuelve c al flujo de entrada
        if (strcmp(lexema, "mientras") == 0)
            return MIENTRAS;
        else if (strcmp(lexema, "si") == 0)
            return SI;
        else
            return IDENTIFICADOR; // se trata de un IDENTIFICADOR
    }

    if (isdigit(c)) // regla del NUMERO
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isdigit(c));

        lexema[i] = '\0';
        ungetc(c, f);
        return NUMERO;
    }

    // reglas de los operadores y símbolos
    switch (c)
    {
    case '+':
        return SUMA;
    case '-':
        return RESTA;
    case '*':
        return MULTIPLICACION;
    case '/':
        return DIVISION;
    case '>':
        c = fgetc(f);
        if (c == '=')
            return MAYOR_IGUAL;
        ungetc(c, f);
        return MAYOR;
    case '<':
        c = fgetc(f);
        if (c == '=')
            return MENOR_IGUAL;
        ungetc(c, f);
        return MENOR;
    case '=':
        c = fgetc(f);
        if (c == '=')
            return IGUALDAD;
        ungetc(c, f);
        return ASIGNACION;
    case '!':
        c = fgetc(f);
        if (c == '=')
            return DIFERENTE;
        ungetc(c, f);
        break;
    case '(':
        return PARENTESIS_IZQ;
    case ')':
        return PARENTESIS_DER;
    case '[':
        return CORCHETE_IZQ;
    case ']':
        return CORCHETE_DER;
    case ',':
        return COMA;
    case ';':
        return PUNTO_Y_COMA;
    case '{':
        return LLAVE_IZQ;
    case '}':
        return LLAVE_DER;
    }

    return -1;
}

void mostrarToken(int token)
{
    switch (token)
    {
    case IDENTIFICADOR:
        printf("Token = IDENTIFICADOR [%s]\n", lexema);
        break;
    case NUMERO:
        printf("Token = NUMERO [%s]\n", lexema);
        break;
    case SUMA:
        printf("Token = SUMA [+]\n");
        break;
    case RESTA:
        printf("Token = RESTA [-]\n");
        break;
    case MULTIPLICACION:
        printf("Token = MULTIPLICACION [*]\n");
        break;
    case DIVISION:
        printf("Token = DIVISION [/]\n");
        break;
    case MAYOR:
        printf("Token = MAYOR [>]\n");
        break;
    case MAYOR_IGUAL:
        printf("Token = MAYOR_IGUAL [>=]\n");
        break;
    case MENOR:
        printf("Token = MENOR [<]\n");
        break;
    case MENOR_IGUAL:
        printf("Token = MENOR_IGUAL [<=]\n");
        break;
    case ASIGNACION:
        printf("Token = ASIGNACION [=]\n");
        break;
    case IGUALDAD:
        printf("Token = IGUALDAD [==]\n");
        break;
    case DIFERENTE:
        printf("Token = DIFERENTE [!=]\n");
        break;
    case PARENTESIS_IZQ:
        printf("Token = PARENTESIS_IZQ [(]\n");
        break;
    case PARENTESIS_DER:
        printf("Token = PARENTESIS_DER [)]\n");
        break;
    case CORCHETE_IZQ:
        printf("Token = CORCHETE_IZQ [[]\n");
        break;
    case CORCHETE_DER:
        printf("Token = CORCHETE_DER []]\n");
        break;
    case COMA:
        printf("Token = COMA [,]\n");
        break;
    case PUNTO_Y_COMA:
        printf("Token = PUNTO_Y_COMA [;]\n");
        break;
    case LLAVE_IZQ:
        printf("Token = LLAVE_IZQ [{]\n");
        break;
    case LLAVE_DER:
        printf("Token = LLAVE_DER [}]\n");
        break;
    case MIENTRAS:
        printf("Token = MIENTRAS [mientras]\n");
        break;
    case SI:
        printf("Token = SI [si]\n");
        break;
    }
}
