#include <stdio.h>
#include <conio.h>
int verifiq (int x, int y,int campo[3][3],int v)
{
    int f=0;
    // Verificacao linhas
    if (campo[0][0]=='X' && campo[0][1]=='X' && campo[0][2]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[0][0]=='O' && campo[0][1]=='O' && campo[0][2]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    else if (campo[1][0]=='X' && campo[1][1]=='X' && campo[1][2]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[1][0]=='O' && campo[1][1]=='O' && campo[1][2]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    else if (campo[2][0]=='X' && campo[2][1]=='X' && campo[2][2]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[2][0]=='O' && campo[2][1]=='O' && campo[2][2]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    // Verificacao colunas
    else if (campo[0][0]=='X' && campo[1][0]=='X' && campo[2][0]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[0][0]=='O' && campo[1][0]=='O' && campo[2][0]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    else if (campo[0][1]=='X' && campo[1][1]=='X' && campo[2][1]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[0][1]=='O' && campo[1][1]=='O' && campo[2][1]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    else if (campo[2][0]=='X' && campo[2][1]=='X' && campo[2][2]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[2][0]=='O' && campo[2][1]=='O' && campo[2][2]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    // Verificacao diagonal
    else if (campo[0][0]=='X' && campo[1][1]=='X' && campo[2][2]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[0][0]=='O' && campo[1][1]=='O' && campo[2][2]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    else if (campo[2][0]=='X' && campo[1][1]=='X' && campo[0][2]=='X')
    {
        printf ("Parabens! Jogador 1 ganhou!\n");
        return f=1;
    }
    else if (campo[2][0]=='O' && campo[1][1]=='O' && campo[0][2]=='O')
    {
        printf ("Parabens! Jogador 2 ganhou!\n");
        return f=1;
    }
    else if (v==9)
    {
        printf ("Velha!\n");
        return f=1;
    }
}
void desenho (int x, int y,int campo[3][3])
{
    int aux1,aux2;
    printf ("\n-------------------\n");
    for (aux1=0;aux1<3;aux1++)
    {
        for (aux2=0;aux2<3;aux2++)
        {
            printf ("|%c|\t",campo[aux1][aux2]);
        }
        printf ("\n-------------------\n");
    }
}
void coord ()
{
    printf ("Use as coordenadas para marcar a casa desejada: \n\t\t[LINHA/COLUNA]\n\n");
    printf ("\n\t\t   1   2   3 \n");
    printf ("\n\t\t1    |   |   \n");
    printf ("\t\t  -----------\n");
    printf ("\t\t2    |   |   \n");
    printf ("\t\t  -----------\n");
    printf ("\t\t3    |   |   \n\n\n");
}
void intro ()
{
        printf ("\t*******************\n");
        printf ("\t*  Jogo da Velha  *\n");
        printf ("\t*******************\n");
        printf ("\tJogador vs Jogador!\nAperte qualquer tecla para continuar!\n\n");
        getch();
}
int main ()
{
    char resposta;
    do
    {
        int campo[3][3]={45,45,45,45,45,45,45,45,45},x,y,t,aux1,aux2,f=0,v=1;
        intro ();
        t=2;
        coord ();
        do
        {
          do{
            do
            {
                printf ("\nJogador %d digite o numero da casa: \n",t%2+1);
                scanf ("%d %d",&x,&y);
                x--;y--;
                } while (x>2 || x<0 || y<0 || y>2);
        }while(campo[x][y]!=45);
                if (t%2==0) // Jogador 1
                    campo[x][y]='X';
                else // Jogador 2
                    campo[x][y]='O';
        t++;
        f=verifiq(x,y,campo,v);
        desenho (x,y,campo);
        v++;
        } while (f!=1);
        do
        {
            printf ("Deseja jogar denovo? [s/n]\n");
            scanf (" %c",&resposta);
        } while (resposta!='S' && resposta!='s' && resposta!='N' && resposta!='n');
    } while (resposta!='N' && resposta!='n');
}

