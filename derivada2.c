#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct{
    double x[6], expo;
} funcao;
double resultaFuncao (funcao termo, double valor){
    termo.x[0] = 1;
    termo.x[1] = -3;
    termo.x[2] = 0;
    termo.x[3] = 0;
    termo.x[4] = 0;
    termo.expo = 4;
    int i = 0, j = termo.expo; 
    double s = 0;
    for(i = 0; i <= termo.expo; i++){
        s += pow(valor, j) * termo.x[i];
        j--;
    }
    return s;
}

double max(double fx, double um){
    if (fx > um){
        return fx;
    }
    else{
        return um;
    }
    
}

double derivada_segunda (funcao termo, double valor, double precisao, int it_max, int *it_efetuada){
    int i; 
    double fx, ant, h = 1, erro_ant, d = 2;
    for(i = 0; i < it_max; i++){
        if(i == 0){
            fx = (resultaFuncao(termo, valor + 2 * h) - 2 * resultaFuncao(termo, valor) + resultaFuncao(termo, valor - 2 * h)) / pow(2 * h, 2);
        }
        else if(i == 1){
            fx = (resultaFuncao(termo, valor + 2 * h) - 2 * resultaFuncao(termo, valor) + resultaFuncao(termo, valor - 2 * h)) / pow(2 * h, 2);
            if(fabs(fx - ant) / max(fx, 1) < precisao){
                *it_efetuada = i+1;
                return fx;
            }
            erro_ant = fabs(fx - ant) / max(fx, 1);
        }
        else if(i >= 2){
            fx = (resultaFuncao(termo, valor + 2 * h) - 2 * resultaFuncao(termo, valor) + resultaFuncao(termo, valor - 2 * h)) / pow(2 * h, 2);
            /*printf("%lf - %lf / 2 * %lf = %lf\n", resultaFuncao(termo, valor + 2 * h), resultaFuncao(termo, valor - 2 * h), h, fx);
            printf("%lf * %lf = %lf\n", d, h, d * h);
            printf("%lf - %lf / %lf = %lf\nERRO ANT %lf\n", fx, ant, fx, fabs(fx - ant) / max(fx, 1), erro_ant);*/
            if(fabs(fx - ant) / max(fx, 1) < precisao){
                *it_efetuada = i+1;
                return fx;
            }
            else if(fabs(fx - ant) / max(fx, 1) > erro_ant){
                *it_efetuada = i++;
                return fx;
            }
            erro_ant = fabs(fx - ant) / max(fx, 1);
        }
        ant = fx;
        h /= d;
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
    double valor, precisao;
    int it_max = 100, it_efetuada = 0;
    char str[20];
    funcao fx;
    printf("Metodo da Diferenciacao\nDigite o valor de x:\n");
    scanf("%lf", &valor);
    printf("Digite o valor da precisao (ex: 10E-10):\n");
    scanf("%s", str);
    if(str[0] == '1' && str[1] == '0' && (str[2] == 'e' || str[2] == 'E') && str[3] == '-' && str[4] > 48 && str[4] < 57)
        precisao = converteString(str);
    else{
        printf("Nao foi possivel identifcar o valor da precisao (formato errado)\n");
        exit(0);
    }
    if(valor = derivada_segunda(fx, valor, precisao, it_max, &it_efetuada))
        printf("Resultado = %lf\nIteracoes = %d\n", valor, it_efetuada);
    else
        printf("Impossivel determinar a raiz\n");
}