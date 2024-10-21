#include <stdio.h>
#include <stdlib.h>

int preanalisis;

// Rutinas auxiliares
void error()
{
    printf("Error de sintaxis");
    exit(1);
}

void parea(int t)
{
    if (preanalisis == t)
        preanalisis = getchar();
    else
        error();
}

// Reglas
void Factor()
{
    if (preanalisis >= '0' && preanalisis <= '9')
    {
        while (preanalisis >= '0' && preanalisis <= '9')
        {
            printf("%c", preanalisis);
            preanalisis = getchar();
        }
    }
    else
    {
        error();
    }
}

void Term()
{
    Factor();
}

void Resto()
{
    if (preanalisis == '+')
    {
        parea('+');
        Term();
        printf("+");
        Resto();
    }
    else if (preanalisis == '-')
    {
        parea('-');
        Term();
        printf("-");
        Resto();
    }
    else
    {
        // Vacio
    }
}

void Exp()
{
    Term();
    Resto();
}

int main()
{
    preanalisis = getchar();
    Exp();
    return 0;
}