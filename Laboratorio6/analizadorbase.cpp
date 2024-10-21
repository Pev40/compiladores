#include <stdio.h>

int preanalisis;

// Rutinas auxiliares
void error()
{
    printf("Error de sintaxis");
}

void parea(int t)
{
    if (preanalisis == t)
        preanalisis = getchar();
    else
        error();
}


// Reglas
void Term()
{
    if (preanalisis >= '0' && preanalisis <= '9')
    {
        printf("%c", preanalisis);
        parea(preanalisis);
    }
    else
    {
        error();
    }
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