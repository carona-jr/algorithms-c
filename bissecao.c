#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct{
    double x[5], expo;
} funcao;
double resultaFuncao (funcao termo, double valor){
    termo.x[0] = 1;
    termo.x[1] = -4;
    termo.x[2] = 1;
    termo.x[3] = 6;
    termo.expo = 3;
    int i = 0, j = termo.expo; 
    double s = 0;
    for(i = 0; i <= termo.expo; i++){
        s += pow(valor, j) * termo.x[i];
        j--;
    }
    return s;
}

int bissecao (funcao termo, double a, double b, double erro, int it_max, double *raiz, int *it_efetuada){
    int i; 
    double x, d = 2;
    if(resultaFuncao(termo, a) * resultaFuncao(termo, b) < 0){
        for(i = 0; i < it_max; i++){
            x = (a + b) / d;
            if(fabs(resultaFuncao(termo, x)) < erro){
                *it_efetuada = i + 1;
                *raiz = x;
                return 1;
            }
            else if(resultaFuncao(termo, a) * resultaFuncao(termo, x) < 0)
                b = x;
            else if(resultaFuncao(termo, a) * resultaFuncao(termo, x) > 0)
                a = x;
            if(fabs(b - a) < erro){
                *it_efetuada = i + 1;
                *raiz = x;
                return 1;
            }
        }
    }
    return 0;
}

double converteString(char str[]){
    char num[20];
    int i, repete = 0, j = 0, numero;
    for(i = 3; i < strlen(str); i++){
        num[j] = str[i];
        j++;
    }
    numero = atoi(num);
    return pow(10, numero);
}

int main(){
    double valor, a, b, precisao, raiz;
    int it_max = 100, it_efetuada = 0;
    char str[20];
    funcao fx;
    printf("Metodo da Bissecao\nDigite o valor do limite inferior:\n");
    scanf("%lf", &a);
    printf("Digite o valor do limite superior:\n");
    scanf("%lf", &b);
    printf("Digite o valor da precisao (ex: 10E-10):\n");
    scanf("%s", str);
    if(str[0] == '1' && str[1] == '0' && (str[2] == 'e' || str[2] == 'E') && str[3] == '-' && str[4] > 48 && str[4] < 57)
        precisao = converteString(str);
    else{
        printf("Nao foi possivel identifcar o valor da precisao (formato errado)\n");
        exit(0);
    }
    if(bissecao(fx, a, b, precisao, it_max, &raiz, &it_efetuada))
        printf("Resultado = %lf\nIteracoes = %d\n", raiz, it_efetuada);
    else
        printf("Impossivel determinar a raiz\n");
}