#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define MAX 100
typedef struct{
    int e, cod, quant;
    float custo;
    char nome[MAX], data[MAX];
} s;
void cadastro (s a, int num, FILE *arqA){
    int i;
    fseek (arqA, 0, SEEK_END);
    for (i=0; i<num; i++){
        system("cls");
        a.e = 1;
        printf ("Nome do produto %d:\n", i+1);
        fflush(stdin);
        gets(a.nome);
        printf ("Codigo produto %d:\n", i+1);
        scanf ("%d", &a.cod);
        printf ("Quantidade do produto %d:\n", i+1);
        scanf ("%d", &a.quant);
        printf ("Preco do produto %d:\n", i+1);
        scanf ("%f", &a.custo);
        printf ("Data de cadastro do produto %d:\n", i+1);
        fflush(stdin);
        gets(a.data);
        fwrite (&a, sizeof(a), 1, arqA);
    }
    fflush(arqA);
}
void mostra (s a, int num, FILE *arqA){
    rewind (arqA);
    while (fread (&a, sizeof(a), 1, arqA)){
        if (a.e == 1)
            printf ("Nome: %s\nCodigo: %d\nQuantidade: %d\nPreco: %.2f reais\nData de cadastro: %s\n\n",a.nome,a.cod,a.quant,a.custo,a.data);
    }
    printf ("\n\nAperte qualquer tecla para continuar\n\n");
    getch();
}
void remover (s a, int num, FILE *arqA){
    int i=0;
    char nom[MAX];
    rewind (arqA);
    printf ("***********************************************\n");
    printf ("Apagar o produto nao removera ele completamente\n");
    printf ("***********************************************\n");
    printf ("Digite o nome do produto que deseja remover:\n");
    fflush(stdin);
    gets(nom);
    while (fread (&a, sizeof(a), 1, arqA)){
        if (stricmp(a.nome, nom)==0){
            fseek (arqA, ftell(arqA) - sizeof(a), SEEK_SET);
            a.e = 0;
            fwrite (&a, sizeof(a), 1, arqA);
            printf ("Apagado\n");
            break;
            }
    }
    printf ("Para apagar permanentemente utilize a exclusao (opcao 7)\n");
    printf ("\n\nAperte qualquer tecla para continuar\n\n");
    getch();
    fflush (arqA);
}
void busca_nome (s a, int num, FILE *arqA){
    char nom[MAX];
    rewind (arqA);
    printf ("Digite o nome do produto que deseja remover:\n");
    fflush(stdin);
    gets(nom);
    while (fread (&a, sizeof(a), 1, arqA)){
        if (a.e == 1)
            if (stricmp(a.nome, nom)==0)
                printf ("Nome: %s\nCodigo: %d\nQuantidade: %d\nPreco: %.2f reais\nData de cadastro: %s\n\n",a.nome,a.cod,a.quant,a.custo,a.data);
    }
    printf ("\n\nAperte qualquer tecla para continuar\n\n");
    getch();
}
void busca_cod (s a, int num, FILE *arqA){
    int codi;
    rewind (arqA);
    printf ("Digite o codigo do produto que deseja remover:\n");
    scanf ("%d", &codi);
    while (fread (&a, sizeof(a), 1, arqA)){
        if (a.e == 1)
            if (a.cod == codi)
                printf ("Nome: %s\nCodigo: %d\nQuantidade: %d\nPreco: %.2f reais\nData de cadastro: %s\n\n",a.nome,a.cod,a.quant,a.custo,a.data);
    }
    printf ("\n\nAperte qualquer tecla para continuar\n\n");
    getch();
}
void altera (s a, int num, FILE *arqA){
    char nom[MAX];
    rewind (arqA);
    printf ("Digite o nome do produto que deseja alterar:\n");
    fflush(stdin);
    gets(nom);
    while (fread (&a, sizeof(a), 1, arqA)){
        if (a.e == 1)
            if (stricmp(a.nome, nom)==0){
                fseek (arqA, ftell(arqA) - sizeof(a), SEEK_SET);
                system("cls");
                a.e = 1;
                printf ("Nome do produto:\n");
                fflush(stdin);
                gets(a.nome);
                printf ("Codigo produto:\n");
                scanf ("%d", &a.cod);
                printf ("Quantidade do produto:\n");
                scanf ("%d", &a.quant);
                printf ("Preco do produto:\n");
                scanf ("%f", &a.custo);
                printf ("Data de cadastro do produto:\n");
                fflush(stdin);
                gets(a.data);
                fwrite (&a, sizeof(a), 1, arqA);
                fflush(arqA);
            }       
    }
    printf ("\n\nAperte qualquer tecla para continuar\n\n");
    getch();
}
void exclui (s a, int num, FILE *arqA){
    char resp;
    FILE *arqT;
    if ((arqT = fopen("arqT.dat", "r+b")) == NULL) 
            if ((arqT = fopen("arqT.dat", "w+b")) == NULL) {
                printf("\n Erro de abertura de arquivo");
                exit(1);
        }
    rewind (arqA);
    printf ("**********************************************\n");
    printf ("Apagar o conteudo removera ele permanentemente\n");
    printf ("**********************************************\n");
    printf ("Deseja realmente apagar os produtos removidos [s/n]:\n");
    resp = toupper(getch());
    if (resp == 'S'){
        while (fread (&a, sizeof(a), 1, arqA)){
            if (a.e == 1)
                fwrite (&a, sizeof(a), 1, arqT);
        }
        printf ("\n");
        if (fclose (arqA) == 0)     
            printf ("Arquivo A foi fechado com sucesso.\n"); 
        else     
            printf ("Nao foi possivel fechar o arquivo.\n");
        if (fclose (arqT) == 0)     
            printf ("Arquivo T foi fechado com sucesso.\n"); 
        else     
            printf ("Nao foi possivel fechar o arquivo.\n");
        if (remove("arqA.dat") == 0)     
            printf ("Arquivo A foi excluido com sucesso.\n"); 
        else     
            printf ("Nao foi possivel excluir o arquivo.\n");
        printf("Arquivo T foi renomeado com sucesso.\n");
        printf ("\n\nAperte qualquer tecla para continuar\n\n");
        getch();
    }
}
int main(){
    s a;
    FILE *arqA, *arqtex;
    int sair = 1, num, i;
    char opc, texto[MAX], opcS, nome[MAX];;
    do{
        system("cls");
        printf ("****************************************************************\n");
        printf ("Software para cadastrar, consultar e remover produtos do estoque\n");
        printf ("****************************************************************\n");
        printf ("Digite a opcao desejada:\n1. Cadastro de novo produto\n2. Mostrar produtos cadastrados\n3. Remover produto\n4. Busca por nome\n5. Busca por codigo\n");
        printf ("6. Alteracao de produto\n7. Exclusao permanente\n8. Opcoes de sistema\nAJUDA APERTE F1 - SAIR APERTE ESC\n");
        opc = toupper(getch());
        switch (opc){
            case '1':   system("cls");
                        if ((arqA = fopen("arqA.dat", "r+b")) == NULL) 
                            if ((arqA = fopen("arqA.dat", "w+b")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        do{
                            printf ("Quantos produtos deseja cadastrar?\n");
                            scanf ("%d", &num);
                        } while (num<=0 || num>=MAX);
                        cadastro (a, num, arqA);
                        fclose (arqA);
                        system("cls");
                        break;
            case '2':   system("cls");
                        if ((arqA = fopen("arqA.dat", "r+b")) == NULL) 
                            if ((arqA = fopen("arqA.dat", "w+b")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        mostra (a, num, arqA);
                        fclose (arqA);
                        system("cls");
                        break;  
            case '3':   system("cls");
                        if ((arqA = fopen("arqA.dat", "r+b")) == NULL) 
                            if ((arqA = fopen("arqA.dat", "w+b")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        remover (a, num, arqA);
                        fclose (arqA);
                        system("cls");
                        break;     
            case '4':   system("cls");
                        if ((arqA = fopen("arqA.dat", "r+b")) == NULL) 
                            if ((arqA = fopen("arqA.dat", "w+b")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        busca_nome (a, num, arqA);
                        fclose (arqA);
                        system("cls");
                        break;         
            case '5':   system("cls");
                        if ((arqA = fopen("arqA.dat", "r+b")) == NULL) 
                            if ((arqA = fopen("arqA.dat", "w+b")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        busca_cod (a, num, arqA);
                        fclose (arqA);
                        system("cls");
                        break;     
            case '6':   system("cls");
                        if ((arqA = fopen("arqA.dat", "r+b")) == NULL) 
                            if ((arqA = fopen("arqA.dat", "w+b")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        altera (a, num, arqA);
                        fclose (arqA);
                        system("cls");
                        break;  
            case '7':   system("cls");
                        if ((arqA = fopen("arqA.dat", "r+b")) == NULL) 
                            if ((arqA = fopen("arqA.dat", "w+b")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        exclui (a, num, arqA);
                        rename ("arqT.dat", "arqA.dat");
                        fclose (arqA);
                        system("cls");
                        break;  
            case '8':   do{
			            system("cls");
            			printf ("Digite a opcao desejada:\n1. Criar uma pasta \n2. Mudar programa para a pasta solicitada\n");
            			printf("3. Mostrar o diretorio corrente\n4. Mudar a cor da tela para verde\n5. Mudar a cor da tela para rosa\n6. Mostrar a versao do sistema operacional\n");
            			printf("7. Mostrar o nome e o numero de serie do volume, se existir\n8. Mostrar hora\n9. Mostrar data\nESC. Retornar ao menu principal\n");
            			opcS = toupper(getch());
        				switch (opcS){
        					case '1':   system("cls");
        								printf ("Digite o nome da pasta a ser criada: ");
 										gets (nome);
 										mkdir (nome);
        								system("cls");
        								break;
							case '2':   system("cls");
										chdir (nome);
										system("pause");
        								system("cls");
        								break;	        							
							case '3':   system("cls");
										printf ("Programa executado em:\n");
  										system ("cd");
										system ("dir");
  										system ("pause");
        								system("cls");
        								break;
        					case '4':   system("cls");
        								system ("color 21");
  										system ("pause");
  										break;
							case '5':   system("cls");
        								system ("color 58");
  										system ("pause");
        								system("cls");
        								break;
        					case '6':   system("cls");
        								printf ("\nRodando em sistema:");
        								system ("ver");
        								system ("pause");
        								system("cls");
        								break;
        					case '7':   system("cls");
        					 			printf ("\nNo volume:\n");
  										system ("vol");
  										printf ("\n");
  										system ("pause");
        								system("cls");
        								break;
        					case '8':   system("cls");
        								system ("time/t");
  										printf ("\n");
  										system ("pause");
        								system("cls");
        								break;
							case '9':   system("cls");
        								printf ("As ");
  										system ("date/t");
  										system ("pause");
  	      								system("cls");
        								break;
        					case 27:   
        								break;
        				}
        					}while(opcS!=27);
						system("cls");
						break;
            			
            
            case 27:    sair = 0;
                        system ("cls");
                        break;
            case 0 && 59:   system ("cls");
                            if ((arqtex = fopen("ajuda.txt", "r+")) == NULL) 
                                if ((arqtex = fopen("ajuda.txt", "w+")) == NULL) {
                                    printf("\n Erro de abertura de arquivo\n");
                                    exit(1);
                                }
                            while(fgets (texto, MAX, arqtex) != NULL){
                                for (i=0; i<strlen(texto); i++){
                                    if (toupper(texto[i]) == 'C')
                                        texto[i] = 'a';
                                    else if (toupper(texto[i]) == 'D')
                                        texto[i] = 'b';
                                    else if (toupper(texto[i]) == 'E')
                                        texto[i] = 'c';
                                    else if (toupper(texto[i]) == 'F')
                                        texto[i] = 'd';
                                    else if (toupper(texto[i]) == 'G')
                                        texto[i] = 'e';
                                    else if (toupper(texto[i]) == 'H')
                                        texto[i] = 'f';
                                    else if (toupper(texto[i]) == 'I')
                                        texto[i] = 'g';
                                    else if (toupper(texto[i]) == 'J')
                                        texto[i] = 'h';
                                    else if (toupper(texto[i]) == 'K')
                                        texto[i] = 'i';
                                    else if (toupper(texto[i]) == 'L')
                                        texto[i] = 'j';
                                    else if (toupper(texto[i]) == 'M')
                                        texto[i] = 'k';
                                    else if (toupper(texto[i]) == 'N')
                                        texto[i] = 'l';
                                    else if (toupper(texto[i]) == 'O')
                                        texto[i] = 'm';
                                    else if (toupper(texto[i]) == 'P')
                                        texto[i] = 'n';
                                    else if (toupper(texto[i]) == 'Q')
                                        texto[i] = 'o';
                                    else if (toupper(texto[i]) == 'R')
                                        texto[i] = 'p';
                                    else if (toupper(texto[i]) == 'T')
                                        texto[i] = 'q';
                                    else if (toupper(texto[i]) == 'U')
                                        texto[i] = 'r';
                                    else if (toupper(texto[i]) == 'V')
                                        texto[i] = 't';
                                    else if (toupper(texto[i]) == 'W')
                                        texto[i] = 'u';
                                    else if (toupper(texto[i]) == 'Y')
                                        texto[i] = 'v';
                                }
                                printf ("%s", texto);
                            }
                            printf ("\n");
                            system ("pause");
                            fclose (arqtex);
                            system ("cls");
                            break;
        }
    } while (sair != 0);
}
