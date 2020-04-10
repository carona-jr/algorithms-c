#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
typedef struct reg *no;
typedef struct {
    int dia, mes, ano, hora, min;
} data;
struct reg {
    char texto[80];
    data date;
    no prox;
};
void cadastro (no *agenda, int dia, int mes, int ano, int hora, int min, char texto[]){
    no p = (no)malloc(sizeof(struct reg));
    no q,r;
	q = *agenda;
	r = *agenda;
    strcpy(p->texto,texto);
    p->date.dia = dia;
    p->date.mes = mes;
    p->date.ano = ano;
    p->date.hora = hora;
    p->date.min = min;
    if(*agenda==NULL){
		p->prox=*agenda;
		*agenda=p;
	}
	else{
		while(q)
			{
				if(p->date.ano<=q->date.ano)
				 if(p->date.mes<=q->date.mes)
				  if(p->date.dia<=q->date.dia)
				   if(p->date.hora<=q->date.hora)
				    if(p->date.min<=q->date.min){
				    	if(q==*agenda){
								p->prox=q;
								*agenda=p;
								break;
						}
						else{
							p->prox=r->prox;
							r->prox=p;
							break;
						}
					}
			 r=q;
			 q=q->prox;
			}
		if(q==NULL && q!=*agenda)
			{
			 r->prox=p;
			 p->prox=NULL;
			}
		}
    }
int remover(no *agenda, int dia, int mes, int ano){
    if(*agenda == NULL)
        return 0;
    if((*agenda)->date.dia == dia && (*agenda)->date.mes == mes && (*agenda)->date.ano == ano){
        no q = *agenda;
        *agenda = (*agenda)->prox;
        free(q);
        return 1;
    }
    no p = *agenda, r;
    while(*agenda){
        if(p->date.dia == dia && p->date.mes == mes && p->date.ano == ano){
            r->prox = p->prox;
            free(p);
            return 1;
        }
        r = p;
        p = (*agenda)->prox;
    }
    return 0;
}
void mostra (no lista){
    while(lista){
        printf("%2d/%2d/%4d as %2d:%2d\n-%s\n", lista->date.dia, lista->date.mes, lista->date.ano, lista->date.hora, lista->date.min, lista->texto);
        lista = lista->prox;
    }
    printf("Aperte qualquer tecla para continuar\n");
    getch();
}
int busca_palavra (char palavra[], no lista){
    int controle = 0;
    char *div;
    while(lista){
        div = strtok(lista->texto, " .-,;/()[]{}");
        while(div != NULL){
            if(stricmp(div, palavra) == 0){
                printf("---------------------------\n");
                printf("%2d/%2d/%4d as %2d:%2d\n-%s\n", lista->date.dia, lista->date.mes, lista->date.ano, lista->date.hora, lista->date.min, lista->texto);
                printf("---------------------------\n");
                controle = 1;
            }
            div = strtok(NULL, " .-,;/()[]{}");
        }
        lista = lista->prox;
    }
    return controle;
}
void gravar_arquivo(no lista, FILE *arq){
    while(lista){
        fprintf(arq, "%d %d %d %d %d %s\n", lista->date.dia, lista->date.mes, lista->date.ano, lista->date.hora, lista->date.min, lista->texto);
        lista = lista->prox;
    }
}
int main () {
    FILE *arq;
    no agenda = NULL;
    int i, sair=0, dia, mes, ano, controle, hora, min;
    char opc, resp, palavra[30], texto[80];
    system("cls");
    printf("************************************\n");
    printf("AGENDA PARA INSERCAO DE COMPROMISSOS\n");
    printf("************************************\n");
    printf(" Feito com S2 por Carlos e Leandro\n");
    printf("************************************\n");
    printf("Aperte qualquer tecla para continuar\n");
    getch();
    do{
        system("cls");
        printf("1. Inserir compromisso\t\t2. Remover compromisso\n3. Consultar compromissos\t4. Buscar compromisso (palavra)\n");
        printf("5. Salvar em arquivo txt\t6. Ler arquivo txto\nESC para Sair!\n");
        opc = toupper(getch());
        switch(opc){
            case '1':   system("cls");
                        do{
                            printf("dia, mes e ano:\n");
                            scanf("%d %d %d", &dia, &mes, &ano);
                            printf("hora e minuto:\n");
                            scanf("%d %d", &hora, &min);
                            printf("texto:\n");
                            fflush(stdin);
                            fgets(texto, 80, stdin);
                            cadastro(&agenda, dia, mes, ano, hora, min, texto);
                            printf("Deseja cadastrar novo compromisso? [s/n]\n");
                            resp = toupper(getch());
                            system("cls");
                        }while(resp!='N');
                        system("cls");
                        break;
            case '2':   system("cls");
                        do{
                            printf("Digite o dia, mes e ano para remover:\n");
                            scanf("%d %d %d", &dia, &mes, &ano);
                            if(remover(&agenda, dia, mes, ano))
                                printf("%d/%d/%d foi removido com sucesso!\n", dia, mes, ano);
                            else
                                printf("%d/%d/%d nao foi removido\n", dia, mes, ano);
                            printf("Deseja remover outro dia da agenda? [s/n]\n");
                            resp = toupper(getch());
                            system("cls");
                        }while(resp!='N');
                        system("cls");
                        break;
            case '3':   system("cls");
                        mostra(agenda);
                        system("cls");
                        break;
            case '4':   system("cls");
                        do{
                            printf("Digite a palavra para buscar?\n");
                            fflush(stdin);
                            fgets(palavra, 30, stdin);
                            controle = busca_palavra(palavra, agenda);
                            if (controle == 0)
                                printf("A palavra \"%s\" nao existe na agenda\n", palavra);
                            printf("Deseja buscar outra palavra? [s/n]\n");
                            resp = toupper(getch());
                            system("cls");
                        } while(resp!='N');
                        system("cls");
                        break;
            case '5':   system("cls");
                        if ((arq = fopen("agenda.txt", "r+")) == NULL) 
                            if ((arq = fopen("agenda.txt", "w+")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        gravar_arquivo(agenda, arq);
                        fclose(arq);
                        system("cls");
                        break;
            case '6':   system("cls");
                        if ((arq = fopen("agenda.txt", "r+")) == NULL) 
                            if ((arq = fopen("agenda.txt", "w+")) == NULL) {
                                printf("\n Erro de abertura de arquivo\n");
                                exit(1);
                        }
                        while (fscanf(arq, "%d %d %d %d %d %s", &dia, &mes, &ano, &hora, &min, texto) != EOF){
                            printf("%2d/%2d/%4d as %2d:%2d\n-%s\n", dia, mes, ano, hora, min, texto);
                            cadastro(&agenda, dia, mes, ano, hora, min, texto);
                        }
                        printf("Aperte qualquer tecla para continuar\n");
                        getch();
                        fclose(arq);
                        system("cls");
                        break;
            case 27:    system("cls");
                        sair = 1;
                        system("cls");
                        break;
        }
    }while(sair!=1);
}
