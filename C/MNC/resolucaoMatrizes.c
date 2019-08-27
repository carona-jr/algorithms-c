#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 50
typedef enum
{
   false,
   true
} bool;
//a[][]: coeficientes
//b[]  : termos independentes
//x[]  : solução

// Encontra o proximo valor a ser colocado na matriz menor
double encontraProx(int controle[][MAX], double a[][MAX], int n)
{
   int i, j;
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         if (controle[i][j] == true)
         {
            controle[i][j] = -1;
            return a[i][j];
         }
      }
   }
}

// Retira a linha e a coluna da matriz
double retiraMatriz(double a[][MAX], double b[][MAX], int n, int k, int v)
{
   int i, j, t = 0;
   int controle[MAX][MAX];
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         if (j == v)
            controle[i][j] = false;
         else if (i != k)
            controle[i][j] = true;
         else
            controle[i][j] = false;
      }
   }
   for (i = 0; i < n - 1; i++)
   {
      for (j = 0; j < n - 1; j++)
      {
         b[i][j] = encontraProx(controle, a, n);
      }
   }
   //printf("Matriz:\n");
   //for (i = 0; i < n - 1; i++)
   //{
   //   for (t = 0; t < n - 1; t++)
   //      printf("%.2f\t", b[i][t]);
   //   printf("\n");
   //}
   //printf("\n");
}

double determinante(int n, double a[][MAX])
{
   double b[MAX][MAX], soma = 0;
   int i, j = 0;
   if (n == 1)
      return a[0][0];
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         retiraMatriz(a, b, n, i, j);
         if (j % 2 == 0)
            soma += a[i][j] * determinante(n - 1, b);
         else
         {
            soma -= a[i][j] * determinante(n - 1, b);
         }
      }
      break;
   }
   return soma;
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

bool sistemaTriangularSuperior(int n, double a[][MAX], double b[], double x[])
{
   int i;
   double s = 0;
   x[n] = b[n] / a[n][n];
   for (i = n - 1; i >= 0; i--)
   {
      x[i] = (b[i] - sum(a, b, x, i, n, false)) / a[i][i];
      //printf("\nx %.3f b %.3f sum %.3f a %.3f\n", x[i], b[i], sum(a, b, x, i, n, false), a[i][i]);
   }
   //printf("\n1  %.3f 2  %.3f 3  %.3f 4  %.3f\n", x[0], x[1], x[2], x[3]);
}

bool sistemaTriangularInferior(int n, double a[][MAX], double b[], double x[])
{
   int i;
   double s = 0;
   x[0] = b[0] / a[0][0];
   for (i = 1; i < n; i++)
   {
      x[i] = (b[i] - sum(a, b, x, i, 0, true)) / a[i][i];
      //printf("\nx %.3f b %.3f sum %.3f a %.3f\n", x[i], b[i], sum(a, b, x, i, n, false), a[i][i]);
   }
   //printf("\n1  %.3f 2  %.3f 3  %.3f 4  %.3f\n", x[0], x[1], x[2], x[3]);
}

bool decomposicaoLU(int n, double a[][MAX], double b[], double x[])
{
   int i = 0, ju = 0, il = 0, t = 1, j = 0, k = 0;
   double mU[MAX][MAX] = {0}, mL[MAX][MAX] = {0}, resultado[MAX], s = 0;
   // Verifica se é o det é diferente de 0
   for (i = 1; i <= n; i++)
   {
      if (determinante(i, a) == 0)
         return false;
      //printf("\nD %.2f\n", determinante(i, a));
   }
   // Monta a matriz U e L
   for (i = 0; i < n; i++)
   {
      for (ju; ju < n; ju++)
      {
         s = 0;
         for (k = 0; k < i; k++)
         {
            s += (mL[i][k] * mU[k][ju]);
            // printf("\nUUU i[%d]j[%d]k[%d] ml[%d][%d]%.3f * mu[%d][%d]%.3f = %.3f\n", i, ju, k, i, k, mL[i][k], k, ju, mU[k][ju], s);
         }
         mU[i][ju] = a[i][ju] - s;
         //printf("\nUUU||mU[%d][%d] = a[%d][%d]%.3f - %.3f||\n", i, ju, i, ju, a[i][ju], s);
      }
      j = i;
      for (il; il < n; il++)
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
               //printf("\nLLL i[%d]j[%d]k[%d] ml[%d][%d]%.3f * mu[%d][%d]%.3f = %.3f\n", il, j, k, il, k, mL[il][k], k, j, mU[k][j], s);
            }
            mL[il][j] = (a[il][j] - s) / mU[j][j];
            //printf("\nLLL||mL[%d][%d] = a[%d][%d]%.3f - %.3f / mU[%d][%d]%.3f||\n", il, j, il, j, a[il][j], s, j, j, mU[j][j]);
         }
      }
      ju = il = t++;
   }

   //printf("Matriz U:\n");
   //for (i = 0; i < n; i++)
   //{
   //   for (t = 0; t < n; t++)
   //      printf("%.8f\t", mU[i][t]);
   //   printf("\n");
   //}
   //printf("\n");

   //printf("Matriz L:\n");
   //for (i = 0; i < n; i++)
   //{
   //   for (t = 0; t < n; t++)
   //      printf("%.8f\t", mL[i][t]);
   //   printf("\n");
   //}
   //printf("\n");

   sistemaTriangularInferior(n, mL, b, resultado);
   sistemaTriangularSuperior(n, mU, resultado, x);
   return true;
}

bool gaussCompacto(int n, double a[][MAX], double b[], double x[])
{
   int i = 0, ju = 0, il = 0, t = 1, j = 0, k = 0;
   double mU[MAX][MAX] = {0}, mL[MAX][MAX] = {0}, resultado[MAX], s;
   // Verifica se o det(A) é diferente de 0
   for (i = 1; i <= n; i++)
   {
      if (determinante(i, a) == 0)
         return false;
      //printf("\nD %.2f\n", determinante(i, a));
   }
   // Coloca o valord de b na matriz a
   for (i = 0; i < n; i++)
   {
      a[i][n] = b[i];
   }
   // Monta a matriz U e L
   for (i = 0; i < n; i++)
   {
      for (ju; ju <= n; ju++)
      {
         s = 0;
         for (k = 0; k < i; k++)
         {
            s += (mL[i][k] * mU[k][ju]);
            //printf("\ni[%d]j[%d]k[%d] ml[%d][%d]%.3f * mu[%d][%d]%.3f = %.3f\n", i, ju, k, i, k, mL[i][k], k, ju, mU[k][ju], s);
         }
         mU[i][ju] = a[i][ju] - s;
         //printf("\nmU[%d][%d] = a[%d][%d]%.3f - %.3f\n", i, ju, i, ju, a[i][ju], s);
      }
      for (il; il < n; il++)
      {
         if (il == i)
         {
            mL[il][i] = 1;
         }
         else
         {
            s = 0;
            for (k = 0; k < il; k++)
               s += mL[il][k] * mU[k][i];
            mL[il][i] = (a[il][i] - s) / mU[i][i];
         }
      }
      ju = il = t++;
   }

   // Coloca os valores alterados de b no vetor b
   for (i = 0; i < n; i++)
   {
      resultado[i] = mU[i][n];
   }
   //printf("\nBB 1  %.3f 2  %.3f 3  %.3f\n", b[0], b[1], b[2]);
   sistemaTriangularSuperior(n, mU, resultado, x);
   return true;
}

bool verificaSimetria(int n, double a[][MAX])
{
   int i, j;
   for (i = 0; i < n; i++)
   {
      for (j = i; j < n; j++)
      {
         if (a[i][j] != a[j][i])
            return false;
      }
   }
   return true;
}

double sumCholesk(int n, int i, int j, double mL[][MAX], int qual)
{
   int k;
   double s = 0;

   if (qual == true)
   {
      for (k = 0; k < i; k++)
      {
         s += pow(mL[i][k], 2);
         //printf("\nS %.3f i %d MMLL %.3f\n", s, i, mL[i][k]);
      }
   }
   else
   {
      for (k = 0; k < i; k++)
      {
         s += (mL[i][k] * mL[j][k]);
         //printf("\nS %.3f i %d MMLL %.3f\n", s, i, mL[i][k]);
      }
   }
   return s;
}

bool cholesky(int n, double a[][MAX], double b[], double x[])
{
   int i, j, t = 1;
   double mLInversa[MAX][MAX] = {0}, mL[MAX][MAX] = {0}, resultado[MAX];
   // Verifica simetria
   if (verificaSimetria(n, a) == false)
      return false;
   // Verifica se é o det é diferente de 0
   for (i = 1; i <= n; i++)
   {
      if (determinante(i, a) < 0)
         return false;
      //printf("\nD %.2f\n", determinante(i, a));
   }
   // Monta a matriz L
   for (i = 0; i < n; i++)
   {
      for (j = i; j < n; j++)
      {
         if (i == j)
         {
            mL[i][i] = sqrt((a[i][i] - sumCholesk(n, i, j, mL, true)));
            //printf("\nL %.3f sq %.3f a %.3f sum %.3f II %d JJ %d\n", mL[i][i], sqrt((a[i][i] - sumCholesk(n, i, j, mL, true))), a[i][i], sumCholesk(n, i, j, mL, true), i, j);
         }
         else
         {
            mL[j][i] = (a[j][i] - sumCholesk(n, j, i, mL, false)) / mL[i][i];
            // printf("\nL2 %.3f a %.3f sum %.3f II %d JJ %d\n", mL[i][i], a[j][i], sumCholesk(n, j, i, mL, false), i, j);
         }
      }
   }

   //Inverte matriz
   for (i = 0; i < n; i++)
   {
      for (j = i; j < n; j++)
      {
         mLInversa[i][j] = mL[j][i];
         //printf("\nIn %.4f No %.4f\n", mLInversa[i][j], mL[j][i]);
      }
   }

   sistemaTriangularInferior(n, mL, b, resultado);
   sistemaTriangularSuperior(n, mLInversa, resultado, x);
   return true;
}

bool gaussJordan(int n, double a[][MAX], double b[], double x[])
{
   int i, j, k;
   double m = 0, mR[MAX][MAX] = {0};
   // Verifica se é o det é diferente de 0
   for (i = 1; i <= n; i++)
   {
      if (determinante(i, a) == 0)
         return false;
      //printf("\nD %.2f\n", determinante(i, a));
   }
   // Coloca o valor de b na matriz a
   for (i = 0; i < n; i++)
   {
      mR[i][n] = b[i];
   }

   for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){
         mR[i][j] = a[i][j];
      }
   }

   for (i = 0; i < n; i++)
   {
      if (mR[i][i] == 0.0)
      {
         printf("Divisão por zero");
         system("pause");
         return false;
      }
      for (j = 0; j < n; j++)
      {
         if (i != j)
         {
            m = mR[j][i] / mR[i][i];
            for (k = 0; k <= n; k++)
            {
               mR[j][k] = mR[j][k] - m * mR[i][k];
            }
         }
      }
   }

   for (i = 0; i < n; i++)
   {
      x[i] = mR[i][n] / mR[i][i];
   }
   return true;
}

bool criterioLinha(int n, double a[][MAX])
{
   int i, j;
   double resultado[MAX];
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         if (j != i)
         {
            resultado[i] += fabs(a[i][j] / a[i][i]);
         }
      }
      if (resultado[i] >= 1)
         return false;
      //printf("\n%.5f / %.5f = %.5f\n", a[i][j], a[i][i], resultado[i]);
   }
   return true;
}

bool criterioColuna(int n, double a[][MAX])
{
   int i, j;
   double resultado[MAX];
   for (j = 0; j < n; j++)
   {
      for (i = 0; i < n; i++)
      {
         if (i != j)
         {
            resultado[j] += fabs(a[i][j] / a[j][j]);
         }
      }
      //printf("\n%.5f / %.5f = %.5f\n", a[i][j], a[j][j], resultado[j]);
      if (resultado[j] >= 1)
         return false;
   }
   return true;
}

// Somatorio da resolução das equações
double sumDaLinha(int n, int i, double a[][MAX], double aprox[])
{
   int j;
   double s = 0;
   for (j = 0; j < n; j++)
   {
      if (j != i)
      {
         s += a[i][j] * aprox[j];
      }
   }
   return s;
}

// Criterio de parada dos metodos interativos
bool cp(int n, double resultado[], double aproxInicial[], double e)
{
   int i;
   double maiorDiferenca = fabs(resultado[0] - aproxInicial[0]), maiorValor = fabs(resultado[0]);
   for (i = 1; i < n; i++)
   {
      if (maiorDiferenca < fabs(resultado[i] - aproxInicial[i]))
         maiorDiferenca = fabs(resultado[i] - aproxInicial[i]);
      if (maiorValor < fabs(resultado[i]))
         maiorValor = fabs(resultado[i]);
   }
   return (maiorDiferenca / maiorValor) < e ? true : false;
}

bool jacobi(int n, double a[][MAX], double b[], double e, double aproxInicial[], int maxIte, double x[], int *ite)
{
   int i, j;
   double valorX[MAX] = {0};
   // Verifica se a diagonal principal é diferente de zero
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         if (i == j)
            if (a[i][j] == 0)
               return false;
      }
   }
   // Verifica determinante != 0
   if (determinante(n, a) == 0)
      return false;
   for (i = 0; i < n; i++)
   {
      valorX[i] = aproxInicial[i];
   }

   // Verifica critério das linhas ou colunas
   if (criterioLinha(n, a) || criterioColuna(n, a))
   {
      for ((*ite) = 0; (*ite)< maxIte; (*ite)++)
      {
         for (i = 0; i < n; i++)
         {
            x[i] = (b[i] - sumDaLinha(n, i, a, valorX)) / a[i][i];
            //printf("\nK = %d || x%d || %.5f - %.5f / %.5f = %.5f\n", (*ite), i, b[i], sumDaLinha(n, i, a, aproxInicial), a[i][i], x[i]);
         }
         if (cp(n, x, valorX, e))
            return true;
         for (j = 0; j < n; j++)
         {
            valorX[j] = x[j];
            //printf("\naprox %.5f\n", aproxInicial[k]);
         }
      }
      //printf("\nVALOR %.5f %.5f %.5f\n", x[0], x[1], x[2]);
   }

   return false;
}

// Somatorio sassenfield
double sumA(int i, double a[][MAX], double b[])
{
   int j;
   double s = 0;
   for (j = 0; j < i; j++)
   {
      s += fabs((a[i][j] / a[i][i]) * b[j]);
   }
   return s;
}

// Somatorio sassenfield
double sumB(int n, int i, double a[][MAX])
{
   int j = i + 1;
   double s = 0;
   for (j; j < n; j++)
   {
      s += fabs(a[i][j] / a[i][i]);
   }
   return s;
}

bool criterioSassenfield(int n, double a[][MAX])
{
   int i, j;
   double b[MAX];
   for (i = 0; i < n; i++)
   {
      b[i] = sumA(i, a, b) + sumB(n, i, a);
      if (b[i] >= 1)
         return false;
      //printf("\nb[%d] = %.5f + %.5f\n", i, sumA(i, a, b), sumB(n, i, a));
   }
   return true;
}

bool gaussSeidel(int n, double a[][MAX], double b[], double e, double aproxInicial[], int maxIte, double x[], int *ite)
{
   int i, j, k;
   // Verifica se a diagonal principal é diferente de zero
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < n; j++)
      {
         if (i == j)
            if (a[i][j] == 0)
               return false;
      }
   }
   // Verifica determinante != 0
   if (determinante(n, a) == 0)
      return false;
   double xAnt[MAX] = {0};
   // Verifica critério das linhas ou sassenfield
   if (criterioLinha(n, a) || criterioSassenfield(n, a))
   {
      for ((*ite) = 0; (*ite)< maxIte; (*ite)++)
      {
         for (i = 0; i < n; i++)
         {
            xAnt[i] = aproxInicial[i];
            x[i] = (b[i] - sumDaLinha(n, i, a, aproxInicial)) / a[i][i];
            aproxInicial[i] = x[i];
            //printf("\nK = %d || x%d || %.5f - %.5f / %.5f = %.5f\n", (*ite), i, b[i], sumDaLinha(n, i, a, aproxInicial), a[i][i], x[i]);
         }
         if (cp(n, x, xAnt, e))
            return true;
      }
      //printf("\nVALOR %.5f %.5f %.5f\n", x[0], x[1], x[2]);
      return true;
   }

   return false;
}

bool matrizInversa(int n, double a[][MAX], double rx[][MAX])
{
   int i, j, t;
   // Monta matriz com valor 1 na diagonal
   for (i = 0; i < n; i++)
   {
      double b[MAX], x[MAX];
      for (j = 0; j < n; j++)
      {
         if (j == i)
         {
            b[j] = 1;
         }
         else
         {
            b[j] = 0;
         }
      }
      //printf("\nNN 1 %.3f 2 %.3f 3 %.3f\n", b[0], b[1], b[2]);
      if (gaussCompacto(n, a, b, x))
      {
         //printf("\nx1 %.3f x2 %.3f x3 %.3f\n", x[0], x[1], x[2]);
         for (t = 0; t < n; t++)
         {
            rx[t][i] = x[t];
         }
      }
      //printf("\n1 %.3f 2 %.3f 3 %.3f\n", b[0], b[1], b[2]);
   }
}

int main()
{
   int n = 3, ite = 0, i, t;
   double a[MAX][MAX] = {
       {3, 0, 3},
       {2, -2, 1},
       {1, 2, 0}};
   double x[MAX] = {0}, b[MAX] = {0, 0, 0}, xInicial[MAX] = {0, 0, 0}, rx[MAX][MAX] = {0};
   //printf("\n\nDET %f\n\n", determinante(n, a));
   //if (decomposicaoLU(n, a, b, x))
   //   printf("\nVALOR %.3f %.3f %.3f\n", x[0], x[1], x[2]);
   //if (gaussCompacto(n, a, b, x))
   //   printf("\nVALOR %.3f %.3f %.3f\n", x[0], x[1], x[2]);
   //if (cholesky(n, a, b, x))
   //   printf("\nVALOR %.3f %.3f %.3f %.3f\n", x[0], x[1], x[2], x[3]);
   //if(gaussJordan(n, a, b, x))
   //   printf("\nVALOR %.3f %.3f %.3f\n", x[0], x[1], x[2]);
   //if (jacobi(n, a, b, 0.1, xInicial, 100, x, &ite))
   //   printf("\nVALOR %.5f %.5f %.5f\n", x[0], x[1], x[2]);
   //if (gaussSeidel(n, a, b, 0.1, xInicial, 100, x, &ite))
   //   printf("\nVALOR %.5f %.5f %.5f\n", x[0], x[1], x[2]);
   /*if (matrizInversa(n, a, rx))
   {
      printf("Matriz Inversa:\n");
      for (i = 0; i < n; i++)
      {
         for (t = 0; t < n; t++)
            printf("%.8f\t", rx[i][t]);
         printf("\n");
      }
      printf("\n");
   }*/

   system("pause");
   return 0;
}