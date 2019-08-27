#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cheque.c"
void contaNotas (int *C100,int *I50,int *J20,int *K10,int *CI5,int *D2,int *L1,int *money){
    int aux;
    *C100=*money/100;
    aux=*money%100;
    *I50=aux/50;
    aux=aux%50;
    *J20=aux/20;
    aux=aux%20;
    *K10=aux/10;
    aux=aux%10;
    *CI5=aux/5;
    aux=aux%5;
    *D2=aux/2;
    aux=aux%2;
    *L1=aux/1;
}
int main ()
{
    char resp;
    char senha[10];
    printf ("Digite a senha (1234):");
    gets(senha);
    if (stricmp(senha, "1234")==0){
    do
    {
        int C100, I50, J20, K10, CI5, D2, L1, money, sair=1;
        char opc;
        do {
        system ("cls");
        printf ("Entre com o numero corresponde da operacao que deseja realizar.\n1. Saque de valores;\n2. Preencher cheque;\nPara sair aperte ESC\n");
        opc = toupper(getch ());
        switch(opc){
            case '1': system ("cls");
                    do {
                    printf ("Digite a quantidade de notas: \n");
                    scanf ("%d",&money);
                    } while (money<=0);
                    contaNotas (&C100, &I50, &J20, &K10, &CI5, &D2, &L1, &money);
                    printf ("%d notas de 100 reais.\n%d notas de 50 reais.\n%d notas de 20 reais.\n%d notas de 10 reais.\n%d notas de 5 reais.\n%d notas de 2 reais.\n%d moedas de 1 reais.\n",C100,I50,J20,K10,CI5,D2,L1);
                    printf ("APERTE ESC PARA SAIR!");
                    getch();
                    system ("cls");
                    break;
            case '2': system ("cls");
                      cheque ();
                      system("cls");
                      break;
            case 27: system ("cls");
                     sair=0;
                     break;
            default: system ("cls");
                     printf ("Desculpe-nos, mas nao existe essa opcao, por favor retorne ao menu principal.\nAperte qualquer tecla para retornar.\n");
                     getch ();
                     system ("cls");
                     break;
        }
        } while (sair!=0);
        do
        {
            printf ("Deseja realmente sair? [s/n]\n");
            scanf (" %c",&resp);
        } while (resp!='S' && resp!='s' && resp!='N' && resp!='n');
    } while (resp!='N' && resp!='n');
    }
    else
        printf ("SENHA INVALIDA\n");
        system("pause");
}
