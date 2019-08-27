#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define MAX 50
void intro ()
{
        printf ("\t*********************\n");
        printf ("\t*  Jogo da Memoria  *\n");
        printf ("\t*********************\n");
        printf ("Aperte qualquer tecla para continuar!\n\n");
        getch();
}
int main ()
{
    char resposta;
    do
    {
        int vet[MAX],vet2[MAX],quant,i,k,t,y,q;
        intro ();
        do
        {
        printf ("Digite a sequencia maxima entre 1 e %d:\n",MAX);
        scanf ("%d",&quant);
        } while (quant<=0 || quant>MAX);
        srand (time(NULL));
        for (i=0;i<quant;i++)
        {
            vet[i]=rand()%5+1;
        }
        printf ("\n");
        t=0; k=1; y=1; i=0;
        do
        {
            for (i=0;i<t+1;i++)
            {
                printf ("Termo %d = %d\n",i+1,vet[i]);
                continue;
            }
            printf ("Aperte qualquer tecla para fazer a sequencia\n");
        getch();
        q=1;
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            for (i=0;i<t+1;i++)
            {
                printf ("Digite o termo %d:\n",q);
                scanf ("%d",&vet2[t]);
                q++;
                if (vet2[t]!=vet[i])
                {
                    printf ("PERDEU!\nSeu acerto maximo foi de %d do total de %d\n",t,quant);
                    i=1000;
                }
                if(quant==(q-1))
                    printf("Parabens! Voce completou a sequencia\n");
                continue;
            }
            t++; k++; y++;
        } while (y<=quant && i<=quant);
        do
        {
            printf ("Deseja jogar denovo? [s/n]\n");
            scanf (" %c",&resposta);
        } while (resposta!='S' && resposta!='s' && resposta!='N' && resposta!='n');
    } while (resposta!='N' && resposta!='n');
}
