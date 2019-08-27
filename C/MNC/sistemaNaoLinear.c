#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define abs(n) ((n) > 0 ? (n) : -(n))
#define erro(vExato, vAprox) ((abs(vExato) > 1) ? (abs(vExato - vAprox) / abs(vExato)) : (abs(vExato - vAprox)))
#define cp(maxH, maxX, erro) ((maxH / maxX < erro) ? true : false)
#define MAX 100
#define MAX_GRAU_FUNCAO 3
#define MAX_VARIAVEL 2
#define X 0
#define X2 1
#define MAX_ERRO 0.01

typedef enum
{
   false, //valor 0 por padrao
   true   //valor 1 por padrao
} bool;

//integracao numerica e resolucao de sistemas nao lineares

//n: qte de subintervalos
//a: limite inferior
//b: limite superior

typedef struct
{
   double coef[MAX_GRAU_FUNCAO + 1]; //coeficiente do termo de grau i, variando de 0 a MAX_GRAU_FUNCAO
} funcao;

typedef struct
{
   double coef[MAX_GRAU_FUNCAO + 1][MAX_VARIAVEL]; //coeficiente do termo de grau i, variando de 0 a MAX_GRAU_FUNCAO
} fNaoLinear;

void iniciaFuncao(funcao *f, int c0, int c1, int c2, int c3)
{
   (*f).coef[0] = c0;
   (*f).coef[1] = c1; //x
   (*f).coef[2] = c2; //x^2
   (*f).coef[3] = c3; //x^3
}

void iniciaFuncaoNaoLinear(fNaoLinear *f, int c0, int c1X, int c1Y, int c2X, int c2Y)
{
   (*f).coef[0][X] = c0;
   (*f).coef[1][X] = c1X;
   (*f).coef[2][X] = c2X;
   (*f).coef[1][X2] = c1Y;
   (*f).coef[2][X2] = c2Y;
}
//x^2+y^2-1=0
//x*y=0
double img(funcao f, double x)
{
   int i;
   double y = 0;
   for (i = 0; i <= MAX_GRAU_FUNCAO; i++)
      y += f.coef[i] * pow(x, i);
   return y;
}

double imgFNaoLinear(fNaoLinear f, double x, double x2, int tipo)
{
   int i;
   double y = 0;
   for (i = 0; i <= MAX_GRAU_FUNCAO; i++)
   {
      if (i == 0)
         y += f.coef[0][X];
      else if (tipo == 0)
         y += (f.coef[i][X] * pow(x, i)) * (f.coef[i][X2] * pow(x2, i));
      else if (tipo == 1)
         y += (f.coef[i][X] * pow(x, i)) + (f.coef[i][X2] * pow(x2, i));
   }
   return y;
}

double df(fNaoLinear f, double x, double x2, double e, int maxIte, int tipo)
{
   int i;
   double erroAtual = MAX_ERRO, erroAnt, h = 1;
   double dfAtual, dfAnt; //derivada no ponto x

   dfAtual = (imgFNaoLinear(f, x + h, x2, tipo) - imgFNaoLinear(f, x - h, x2, tipo)) / (2 * h); //1a iteracao
   for (i = 2; i <= maxIte; i++)
   {
      h /= 2;
      dfAnt = dfAtual;
      dfAtual = (imgFNaoLinear(f, x + h, x2, tipo) - imgFNaoLinear(f, x - h, x2, tipo)) / (2 * h);

      erroAnt = erroAtual;
      erroAtual = erro(dfAtual, dfAnt);

      if (erroAtual < e || erroAtual > erroAnt)
         return dfAtual;
   }
   return dfAtual;
}

void jacobiana(int dimVetX, int numEquacoes, fNaoLinear f1, fNaoLinear f2, double vetX[], double matriz[][MAX])
{
   int i, j, tipo = 1, trocaX1, trocaX2;
   fNaoLinear f = f1;

   for (i = 0; i < numEquacoes; i++)
   {
      trocaX1 = 0;
      trocaX2 = 1;
      for (j = 0; j < dimVetX; j++)
      {
         matriz[i][j] = df(f, vetX[trocaX1], vetX[trocaX2], 0.0001, 100, tipo);
         trocaX1 = 1;
         trocaX2 = 0;
      }
      tipo = 0;
      f = f2;
   }
}

void geraSubMatriz(int n, double a[][MAX], int c, double sub[][MAX])
{
   int i, j, k;
   for (i = 1; i < n; i++)
      for (j = 0, k = 0; j < n; j++, k++)
      {
         if (j != c)
            sub[i - 1][k] = a[i][j];
         else
            k--;
      }
}

double determinante(int n, double a[][MAX])
{
   int j;
   double s = 0;
   if (n == 1)
      return a[0][0];
   else
   {
      double sub[MAX][MAX];
      for (j = 0; j < n; j++)
         if (a[0][j] != 0)
         { //para cada elemento da linha 0 (a[0][j])
            geraSubMatriz(n, a, j, sub);
            s += a[0][j] * pow(-1, j) * determinante(n - 1, sub);
         }
   }
   return s;
}

double sum(double a[][MAX], double b[], double x[], int i, int n, int qual)
{
   int j;
   double s = 0;
   if (qual == true)
   {
      for (j = 0; j < i; j++)
      {
         s += a[i][j] * x[j];
      }
   }
   else
   {
      for (j = i + 1; j < n; j++)
      {
         s += a[i][j] * x[j];
      }
   }
   return s;
}

void sistemaTriangularSuperior(int n, double a[][MAX], double b[], double x[])
{
   int i;
   double s = 0;
   x[n] = b[n] / a[n][n];
   for (i = n - 1; i >= 0; i--)
   {
      x[i] = (b[i] - sum(a, b, x, i, n, false)) / a[i][i];
   }
}

void sistemaTriangularInferior(int n, double a[][MAX], double b[], double x[])
{
   int i;
   double s = 0;
   x[0] = b[0] / a[0][0];
   for (i = 1; i < n; i++)
   {
      x[i] = (b[i] - sum(a, b, x, i, 0, true)) / a[i][i];
   }
}

bool decomposicaoLU(int n, double a[][MAX], double b[], double x[])
{
   int i = 0, ju = 0, il = 0, t = 1, j = 0, k = 0;
   double mU[MAX][MAX] = {0}, mL[MAX][MAX] = {0}, resultado[MAX], s = 0;
   // Verifica se e o det e diferente de 0
   for (i = 1; i <= n; i++)
   {
      if (determinante(i, a) == 0)
         return false;
   }
   // Monta a matriz U e L
   for (i = 0; i < n; i++)
   {
      for (; ju < n; ju++)
      {
         s = 0;
         for (k = 0; k < i; k++)
         {
            s += (mL[i][k] * mU[k][ju]);
         }
         mU[i][ju] = a[i][ju] - s;
      }
      j = i;
      for (; il < n; il++)
      {
         if (il == j)
         {
            mL[il][j] = 1;
         }
         else
         {
            s = 0;
            for (k = 0; k < il; k++)
            {
               s += mL[il][k] * mU[k][j];
            }
            mL[il][j] = (a[il][j] - s) / mU[j][j];
         }
      }
      ju = il = t++;
   }

   sistemaTriangularInferior(n, mL, b, resultado);
   sistemaTriangularSuperior(n, mU, resultado, x);
   return true;
}

bool sistemaNaoLinear(int dimVetX, int numEquacoes, fNaoLinear f1, fNaoLinear f2, double erro, int numMaxIte, double vetX[], int *numIte)
{
   int i, j;
   double matriz[MAX_VARIAVEL][MAX] = {0}, vetB[numEquacoes], vetH[numEquacoes], maxH = 0, maxX = 0;
   for (i = 0; i < numMaxIte; i++)
   {
      jacobiana(dimVetX, numEquacoes, f1, f2, vetX, matriz);
      vetB[0] = imgFNaoLinear(f1, vetX[0], vetX[1], 1);
      vetB[1] = imgFNaoLinear(f2, vetX[0], vetX[1], 0);
      if (!decomposicaoLU(numEquacoes, matriz, vetB, vetH))
         return false;
      for (j = 0; j < 2; j++)
      {
         if (fabs(vetH[j]) > maxH)
            maxH = fabs(vetH[j]);
      }
      vetX[0] -= vetH[0];
      vetX[1] -= vetH[1];
      for (j = 0; j < 2; j++)
      {
         if (fabs(vetX[j]) > maxH)
            maxX = fabs(vetX[j]);
         if (maxX < 1)
            maxX = 1;
      }
      *numIte = i;
      if (cp(maxH, maxX, erro))
         return true;
   }
   return false;
}

double trapezio_1ap(double y0, double y1, double h)
{
   return (h * 1 / 2) * (y0 + y1);
}
double umTercoSimpson_1ap(double y0, double y1, double y2, double h)
{
   return (h * 1 / 3) * (y0 + 4 * y1 + y2);
}
double tresOitavosSimpson_1ap(double y0, double y1, double y2, double y3, double h)
{
   return (h * 3 / 8) * (y0 + 3 * y1 + 3 * y2 + y3);
}

//calcula o vetor y = {f(x), f(x+h), f(x+2h), ... , f(x+n*h)} de tamanho n+1
void calculaY(int n, double h, double x, funcao f, double y[MAX])
{
   int i;
   for (i = 0; i <= n; i++)
      y[i] = img(f, x + i * h);
}

double trapezio(int n, double a, double b, funcao f)
{
   int i;
   double res = 0, y[MAX];
   double h = (b - a) / n;

   calculaY(n, h, a, f, y);

   //n aplicacoes
   for (i = 0; i + 1 <= n; i++)
      res += trapezio_1ap(y[i], y[i + 1], h);

   return res;
}

double umTercoSimpson(int n, double a, double b, funcao f)
{
   int i;
   double res = 0, y[MAX];
   double h = (b - a) / n;

   calculaY(n, h, a, f, y);

   // n/2 aplicacoes, logo n precisa ser multiplo de 2
   for (i = 0; i + 2 <= n; i += 2)
      res += umTercoSimpson_1ap(y[i], y[i + 1], y[i + 2], h);

   if (n % 2 != 0)
      res += trapezio_1ap(y[n - 1], y[n], h); // faltou 1 intervalo

   return res;
}

double tresOitavosSimpson(int n, double a, double b, funcao f)
{
   int i;
   double res = 0, y[MAX];
   double h = (b - a) / n;

   calculaY(n, h, a, f, y);

   // n/3 aplicacoes, logo n precisa ser multiplo de 3
   for (i = 0; i + 3 <= n; i += 3)
      res += tresOitavosSimpson_1ap(y[i], y[i + 1], y[i + 2], y[i + 3], h);

   if (n % 3 != 0)
   {
      if (n % 2 == 0)
         res += umTercoSimpson_1ap(y[n - 2], y[n - 1], y[n], h); // faltou 2 intervalos
      else
         res += trapezio_1ap(y[n - 1], y[n], h); // faltou 1 intervalo
   }

   return res;
}

int menu()
{
   int op;
   printf("\n        Calculo de integracao      \n");
   printf("          e sistema nao linear       \n");
   printf("...................................\n\n");
   printf("| Integracao\n");
   printf("  01 > Trapezio\n");
   printf("  02 > 1/3 de Simpson\n");
   printf("  03 > 3/8 de Simpson\n\n");
   printf("| Sistema Nao Linear\n");
   printf("  04 > Newton\n\n");
   do
   {
      printf("Resp.: ");
      scanf("%d", &op);
   } while (op < 1 || op > 4);
   return op;
}

void leVetor(int n, double v[MAX], char nomeVetor[])
{
   int i;
   for (i = 0; i <= n; i++)
   {
      printf("%s[GRAU %d]: ", nomeVetor, i + 1);
      scanf("%lf", &v[i]);
   }
}

void mostraVetor(int n, double vetor[], char nomeVetor[], char nome[], int num)
{
   int i;
   printf("\n%s, com %d iteracoes\n", nome, num + 1);
   for (i = 0; i < n; i++)
   {
      printf("%s[%d] = %.4lf\n", nomeVetor, i, vetor[i]);
   }
}

int main()
{
   double vetX[MAX_VARIAVEL], erro, coefX[MAX], coefY[MAX], a, b, termoInd;
   int numIte, i, op, maxIte, n;
   char opSair;
   funcao f1, f2, f3;
   fNaoLinear f4, f5, f6;
   iniciaFuncao(&f1, 0, 0, 1, 0);
   iniciaFuncao(&f2, 1, 0, 0, 1);
   iniciaFuncaoNaoLinear(&f4, -1, 0, 0, 1, 1);
   iniciaFuncaoNaoLinear(&f5, 0, 1, 1, 0, 0);
   do
   {
      op = menu();
      printf("\n");
      switch (op)
      {
      case 1:
         printf("\nTRAPEZIO\n");
         printf("Digite o termo independente da funcao: \n");
         scanf("%lf", &termoInd);
         printf("Digite os coeficientes da funcao para o maior (MAX GRAU 3): \n");
         leVetor(MAX_GRAU_FUNCAO, coefX, "x");
         iniciaFuncao(&f1, termoInd, coefX[0], coefX[1], coefX[2]);
         printf("Digite o numero de subintervalos: \n");
         scanf("%d", &n);
         printf("Digite o limite inferior: \n");
         scanf("%lf", &a);
         printf("Digite o limite superior: \n");
         scanf("%lf", &b);
         printf("A integral da funcao eh: %.10lf\n", trapezio(n, a, b, f1));
         break;
      case 2:
         printf("\n1/3 de SIMPSON\n");
         printf("Digite o termo independente da funcao: \n");
         scanf("%lf", &termoInd);
         printf("Digite os coeficientes da funcao para o maior (MAX GRAU 3): \n");
         leVetor(MAX_GRAU_FUNCAO, coefX, "x");
         iniciaFuncao(&f2, termoInd, coefX[0], coefX[1], coefX[2]);
         printf("Digite o numero de subintervalos: \n");
         scanf("%d", &n);
         printf("Digite o limite inferior: \n");
         scanf("%lf", &a);
         printf("Digite o limite superior: \n");
         scanf("%lf", &b);
         printf("A integral da funcao eh: %.10lf\n", umTercoSimpson(n, a, b, f2));
         break;
      case 3:
         printf("\n3/8 de SIMPSON\n");
         printf("Digite o termo independente da funcao: \n");
         scanf("%lf", &termoInd);
         printf("Digite os coeficientes da funcao para o maior (MAX GRAU 3): \n");
         leVetor(MAX_GRAU_FUNCAO, coefX, "x");
         iniciaFuncao(&f3, termoInd, coefX[0], coefX[1], coefX[2]);
         printf("Digite o numero de subintervalos: \n");
         scanf("%d", &n);
         printf("Digite o limite inferior: \n");
         scanf("%lf", &a);
         printf("Digite o limite superior: \n");
         scanf("%lf", &b);
         printf("A integral da funcao eh: %.10lf\n", tresOitavosSimpson(n, a, b, f3));
         break;
      case 4:
         printf("..................................\n\n");
         printf("Resolucao somente com duas funcoes\n");
         printf("Funcao tipo 0 - (X1 * X2) + termos\n");
         printf("Funcao tipo 1 - X1 + X2 + termos\n");
         printf("\n..................................\n\n");
         printf("|| Linha 1 -> funcao tipo 1 ||\n");
         printf("Digite o termo independente da funcao 1: \n");
         scanf("%lf", &termoInd);
         printf("Digite os termos X1 da funcao 1 em ordem crescente de expoente: \n");
         leVetor(MAX_VARIAVEL - 1, coefX, "F -> 1");
         printf("Digite os termos X2 da funcao 1 em ordem crescente de expoente: \n");
         leVetor(MAX_VARIAVEL - 1, coefY, "F -> 1");
         iniciaFuncaoNaoLinear(&f4, termoInd, coefX[0], coefY[0], coefX[1], coefY[1]);
         printf("|| Linha 2 -> funcao tipo 0 ||\n");
         printf("Digite o termo independente da funcao 2: \n");
         scanf("%lf", &termoInd);
         printf("Digite os termos X1 da funcao 2 em ordem crescente de expoente: \n");
         leVetor(MAX_VARIAVEL - 1, coefX, "F -> 2");
         printf("Digite os termos X2 da funcao 2 em ordem crescente de expoente: \n");
         leVetor(MAX_VARIAVEL - 1, coefY, "F -> 2");
         iniciaFuncaoNaoLinear(&f5, termoInd, coefX[0], coefY[0], coefX[1], coefY[1]);
         printf("Digite os valores iniciais de X: \n");
         leVetor(MAX_VARIAVEL - 1, vetX, "vetX");
         printf("Digite o maximo de iteracoes: \n");
         scanf("%d", &maxIte);
         printf("Digite o erro: \n");
         scanf("%lf", &erro);
         if (!sistemaNaoLinear(MAX_VARIAVEL, MAX_VARIAVEL, f4, f5, erro, maxIte, vetX, &numIte))
            mostraVetor(MAX_VARIAVEL, vetX, "x", "Resultado Sistema", numIte);
         else
            printf("ERRO");
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