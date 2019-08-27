#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define MAX 50
#define LIN_X 0
#define LIN_Y 1
typedef enum
{
    false,
    true
} bool;

bool verificaIntervalo(double tabela[][MAX], int n)
{
    double h, soma = tabela[0][0];
    int i;
    h = tabela[0][1] - tabela[0][0];
    for (i = 1; i < n; i++)
        if (tabela[0][i] - tabela[0][i - 1] > h + 0.00001 || tabela[0][i] - tabela[0][i - 1] < h - 0.00001)
            return false;
    return true;
}

double newton(double ponto, int n, double tabela[][MAX])
{
    int i, j;
    double aux[MAX], final[MAX], soma = 0, valorFinal;

    for (i = 0; i < n; i++)
        aux[i] = tabela[1][i];
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i; j++)
        {
            aux[j] = (aux[j + 1] - aux[j]) / (tabela[0][j + i + 1] - tabela[0][j]);
            if (j == 0)
                final[i] = aux[j];
        }
    valorFinal = tabela[1][0];
    for (i = 0; i < n - 1; i++)
    {
        if (i == 0)
            soma += (ponto - tabela[0][i]);
        else
            soma *= (ponto - tabela[0][i]);
        valorFinal += soma * final[i];
    }
    return valorFinal;
}
double newtonGregory(double ponto, int n, double tabela[][MAX])
{
    int i, j, fat = 1;
    double aux[MAX], final[MAX], soma = 0, valorFinal, h;

    h = tabela[0][1] - tabela[0][0];

    for (i = 0; i < n; i++)
        aux[i] = tabela[1][i];
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i; j++)
        {
            aux[j] = (aux[j + 1] - aux[j]);
            if (j == 0)
                final[i] = aux[j];
        }
    valorFinal = tabela[1][0];
    for (i = 0; i < n - 1; i++)
    {
        if (i == 0)
            soma += (ponto - tabela[0][i]);
        else
            soma *= (ponto - tabela[0][i]);
        valorFinal += soma * final[i] / (fat * pow(h, i + 1));
        fat *= i + 2;
    }
    return valorFinal;
}
double coefDeterminacao(int n, double tabela[][MAX], double vetorY[])
{
    double somay = 0, denominador = 0, quadrado = 0, numerador = 0;
    int i;

    for (i = 0; i < n; i++)
    {
        somay += tabela[1][i]; // soma os valores de y;
    }

    for (i = 0; i < n; i++)
    {
        numerador += pow((tabela[1][i] - vetorY[i]), 2.0);
    }

    for (i = 0; i < n; i++)
    {
        quadrado += pow(tabela[1][i], 2.0); // calculo do somatório do QUADRADO DE Y;
    }

    denominador = (n * quadrado) - (pow(somay, 2.0)); // calculo do denominador

    //Resultado
    return 1.0 - (n * numerador / denominador);
}

//ajusta os pontos a uma reta do tipo y = a0 + a1.x
void ajusteReta(int n, double tabela[][MAX], double *a0, double *a1, double yAjustado[], double *coefDet)
{
    double xy = 0, x = 0, y = 0, x2 = 0; //somatórios

    for (int j = 0; j < n; j++)
    {
        xy += tabela[LIN_X][j] * tabela[LIN_Y][j];
        x += tabela[LIN_X][j];
        y += tabela[LIN_Y][j];
        x2 += pow(tabela[LIN_X][j], 2);
    }
    *a1 = (n * xy - x * y) / (n * x2 - pow(x, 2));
    *a0 = (y - (*a1) * x) / n;

    for (int i = 0; i < n; i++)
        yAjustado[i] = (*a0) + (*a1) * tabela[LIN_X][i];

    *coefDet = coefDeterminacao(n, tabela, yAjustado);
}

//gera matriz sub de ordem n-1, sem a linha 0 e a coluna c da matriz a
void geraSubMatriz(int n, double a[][MAX], int c, double sub[][MAX])
{
    for (int i = 1; i < n; i++)
        for (int j = 0, k = 0; j < n; j++, k++)
        {
            if (j != c)
                sub[i - 1][k] = a[i][j];
            else
                k--;
        }
}

//retorna o determinante da matriz, por laplace
double determinante(int n, double a[][MAX])
{
    double s = 0;
    if (n == 1)
        return a[0][0];
    else
    {
        double sub[MAX][MAX];
        for (int j = 0; j < n; j++)
            if (a[0][j] != 0)
            { //para cada elemento da linha 0 (a[0][j])
                geraSubMatriz(n, a, j, sub);
                s += a[0][j] * pow(-1, j) * determinante(n - 1, sub);
            }
    }
    return s;
}

bool sistemaTriangularSuperior(int n, double a[][MAX], double b[], double x[])
{
    if (determinante(n, a) == 0)
        return false;

    for (int i = n - 1; i >= 0; i--)
    {
        double s = 0;
        for (int j = i; j < n; j++)
            s += a[i][j] * x[j];

        x[i] = (b[i] - s) / a[i][i];
    }
    return true;
}

//retorna true se todas as submatrizes principais têm determinante diferente de 0
bool temSubMatrizesNaoSingulares(int n, double a[][MAX])
{
    for (int i = 1; i <= n; i++)
        if (determinante(i, a) == 0)
            return false;
    return true;
}

bool sistemaTriangularInferior(int n, double a[][MAX], double b[], double x[])
{
    if (determinante(n, a) == 0)
        return false;

    for (int i = 0; i < n; i++)
    {
        double s = 0;
        for (int j = 0; j < i; j++)
            s += a[i][j] * x[j];

        x[i] = (b[i] - s) / a[i][i];
    }
    return true;
}

//métodos diretos
bool decomposicaoLU(int n, double a[][MAX], double b[], double x[])
{
    double u[MAX][MAX], l[MAX][MAX], y[MAX], s;

    if (!temSubMatrizesNaoSingulares(n, a))
        return false; //método não converge

    for (int p = 0; p < n; p++)
    {
        //calcula a linha p de U
        for (int j = p; j < n; j++)
        {
            s = 0;
            for (int k = 0; k < p; k++)
                s += l[p][k] * u[k][j];

            u[p][j] = a[p][j] - s;
        }
        //calcula a coluna p de L
        for (int i = p; i < n; i++)
        {
            s = 0;
            for (int k = 0; k < p; k++)
                s += l[i][k] * u[k][p];

            l[i][p] = (a[i][p] - s) / u[p][p];
        }
    }
    // impMatriz(n, l);
    // impMatriz(n, u);
    sistemaTriangularInferior(n, l, b, y); //L.y = b
    sistemaTriangularSuperior(n, u, y, x); //U.x = y
    return true;
}

bool ajustePolinomial(int grauDesejado, int numPontosTabelados, double tabela[][MAX], double vetorA[], double vetorY[], double *coefDet)
{
    int i, j;
    double vetorSomaX[MAX], vetorSomaY[MAX], soma, elevado, matrizComSomatorios[MAX][MAX];
    vetorSomaX[0] = numPontosTabelados;

    // Calcula o somatorio do X até o dobro do grau colocado
    for (i = 1; i <= (grauDesejado + grauDesejado); i++)
    {
        soma = 0;
        elevado = i;
        for (j = 0; j < numPontosTabelados; j++)
        {
            soma += pow(tabela[0][j], elevado);
        }
        vetorSomaX[i] = soma;
    }

    // Calcula o somatorio de X*Y até o grau desejado
    soma = 0;
    for (j = 0; j < numPontosTabelados; j++)
    {
        soma += tabela[1][j];
    }
    vetorSomaY[0] = soma;
    for (i = 1; i <= grauDesejado; i++)
    {
        soma = 0;
        elevado = i;
        for (j = 0; j < numPontosTabelados; j++)
        {
            soma += pow(tabela[0][j], elevado) * tabela[1][j];
        }
        vetorSomaY[i] = soma;
    }

    // Montagem da matriz com os valores calculados
    for (i = 0; i <= grauDesejado; i++)
    {
        for (j = 0; j <= grauDesejado; j++)
        {
            matrizComSomatorios[i][j] = vetorSomaX[i + j];
        }
    }

    // resultado da matriz com os valores de A
    if (!decomposicaoLU(grauDesejado + 1, matrizComSomatorios, vetorSomaY, vetorA))
        return false;

    printf("\nMatriz com Valores do Somatorio:\n");
    for (i = 0; i <= grauDesejado; i++)
    {
        for (j = 0; j <= grauDesejado; j++)
            printf("%.10f\t", matrizComSomatorios[i][j]);
        printf("\n");
    }

    // Calcula os pontos de Y ajustados
    soma = 0;
    for (i = 0; i < numPontosTabelados; i++)
    {
        soma = vetorA[0];
        for (j = 1; j <= grauDesejado; j++)
        {
            elevado = j;
            soma += vetorA[j] * pow(tabela[0][i], elevado);
        }
        vetorY[i] = soma;
    }

    *coefDet = coefDeterminacao(numPontosTabelados, tabela, vetorY);
    return true;
}
//ajusta os pontos a uma curva do tipo y = a.(b^x)
void ajusteExponencial(int n, double tabela[][MAX], double *a, double *b, double yAjustado[], double *coefDet)
{
    double a0, a1;
    for (int j = 0; j < n; j++)
        tabela[LIN_Y][j] = log(tabela[LIN_Y][j]);

    ajusteReta(n, tabela, &a0, &a1, yAjustado, &(*coefDet));
    // printf("a0: %lf\na1: %lf\n", a0, a1);
    *a = pow(M_E, a0);
    *b = pow(M_E, a1);
}

int menu()
{
    int op;
    printf("\n     Calculo de interpolacao    \n");
    printf("          e ajuste de curva       \n");
    printf("................................\n\n");
    printf("| Interpolacao\n");
    printf("  01 > Newton\n");
    printf("  02 > Newton-Gregory\n\n");
    printf("| Ajuste de curva\n");
    printf("  03 > Reta\n");
    printf("  04 > Polinomial\n");
    printf("  05 > Exponencial\n\n");
    do
    {
        printf("Resp.: ");
        scanf("%d", &op);
    } while (op < 1 || op > 5);
    return op;
}

void leVetor(int n, int var, double v[][MAX])
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("v[%d]: ", i);
        scanf("%lf", &v[var][i]);
    }
}

void mostraVetor(int n, double vetor[], char nomeVetor[])
{
    int i;
    printf("\n%s\n", nomeVetor);
    for (i = 0; i < n; i++)
    {
        printf("%s[%d] = %.4lf\n", nomeVetor, i, vetor[i]);
    }
}

int main()
{
    int n = 0, op;
    char opSair;
    double tabela[2][MAX];
    // ponto é a variável onde deseja se conhecer o P(x) interpolado
    double vetorA[MAX], vetorY[MAX], ponto = 0, coefDet = 0, grauDesejado = 0, a = 0, b = 0;

    do
    {
        op = menu();
        printf("\n");
        switch (op)
        {
        case 1:
            printf("Interpolacao por Newton\n");
            printf("Digite o valor de pontos tabelas: \n");
            scanf("%d", &n);
            printf("Digite o valor a ser calculado: \n");
            scanf("%lf", &ponto);
            printf("Digite os valores de X de 0 ate %d: \n", n);
            leVetor(n, 0, tabela);
            printf("Digite os valores de Y de 0 ate %d: \n", n);
            leVetor(n, 1, tabela);
            if (verificaIntervalo(tabela, n))
            {
                printf("\n------ RESULTADO ------");
                printf("\nf(%.4lf) = %.4lf\n", ponto, newton(ponto, n, tabela));
            }
            else
            {
                printf("\nErro, nao foi possivel resolver o metodo com esses valores\n");
            }
            break;
        case 2:
            printf("Interpolacao por Newton-Gregory\n");
            printf("Digite o valor de pontos tabelas: \n");
            scanf("%d", &n);
            printf("Digite o valor a ser calculado: \n");
            scanf("%lf", &ponto);
            printf("Digite os valores de X de 0 ate %d: \n", n);
            leVetor(n, 0, tabela);
            printf("Digite os valores de Y de 0 ate %d: \n", n);
            leVetor(n, 1, tabela);
            if (verificaIntervalo(tabela, n))
            {
                printf("\n------ RESULTADO ------");
                printf("\nf(%.4lf) = %.4lf\n", ponto, newtonGregory(ponto, n, tabela));
            }
            else
            {
                printf("\nErro, nao foi possivel resolver o metodo com esses valores\n");
            }
            break;
        case 3:
            printf("Ajuste de curva por Reta\n");
            printf("Digite o valor de pontos tabelas: \n");
            scanf("%d", &n);
            printf("Digite os valores de X de 0 ate %d: \n", n);
            leVetor(n, 0, tabela);
            printf("Digite os valores de Y de 0 ate %d: \n", n);
            leVetor(n, 1, tabela);
            printf("\n------ RESULTADO ------");
            ajusteReta(n, tabela, &a, &b, vetorY, &coefDet);
            printf("\nTermo independente = %.4lf\n", a);
            printf("\nCoeficiente de grau 1 = %.4lf\n", b);
            mostraVetor(n, vetorY, "vAjustado");
            printf("\nCoeficiente de determinacao = %.4lf\n", coefDet);
            break;
        case 4:
            printf("Ajuste de curva Polinomial\n");
            printf("Digite o valor de pontos tabelas: \n");
            scanf("%d", &n);
            printf("Digite o grau desejado: \n");
            scanf("%lf", &grauDesejado);
            printf("Digite os valores de X de 0 ate %d: \n", n);
            leVetor(n, 0, tabela);
            printf("Digite os valores de Y de 0 ate %d: \n", n);
            leVetor(n, 1, tabela);
            if (ajustePolinomial(grauDesejado, n, tabela, vetorA, vetorY, &coefDet))
            {
                printf("\n------ RESULTADO ------");
                mostraVetor(grauDesejado + 1, vetorA, "vSolMatriz");
                mostraVetor(n, vetorY, "vAjustado");
                printf("\nCoeficiente de determinacao = %.4lf\n", coefDet);
            }
            else
            {
                printf("\nErro, nao foi possivel resolver o metodo com esses valores\n");
            }
            break;
        case 5:
            printf("Ajuste de curva Exponencial\n");
            printf("Digite o valor de pontos tabelas: \n");
            scanf("%d", &n);
            printf("Digite os valores de X de 0 ate %d: \n", n);
            leVetor(n, 0, tabela);
            printf("Digite os valores de Y de 0 ate %d: \n", n);
            leVetor(n, 1, tabela);
            printf("\n------ RESULTADO ------");
            ajusteExponencial(n, tabela, &a, &b, vetorY, &coefDet);
            printf("\nTermo A = %.4lf\n", a);
            printf("\nTermo B = %.4lf\n", b);
            mostraVetor(n, tabela[1], "vLogN");
            mostraVetor(n, vetorY, "vAjustado");
            printf("\nCoeficiente de determinacao = %.4lf\n", coefDet);
            break;
        }
        do
        {
            printf("\nDeseja sair? [s/n]\n");
            fflush(stdin);
            scanf("%c", &opSair);
            opSair = toupper(opSair);
        } while (opSair != 'S' && opSair != 'N');
    } while (opSair != 'S');
    return 0;
}