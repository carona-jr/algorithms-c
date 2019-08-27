//Conversão de bases
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 50
void decTObin (char decimal[], char binario[]){
    int i=0, dec;
    dec = atoi(decimal);
    strcpy (binario,"");
    while (dec!=0){   
        if (dec%2 == 0)
            strcat (binario,"0");
        else
	        strcat (binario,"1");
        dec/= 2;      
        i++;
   }  
   strrev (binario);
}
void decTOoct (char decimal[], char octal[]){
    int i=0, oct;
    oct = atoi(decimal);
    strcpy (octal,"");
    while (oct!=0){   
        if (oct%8 == 0)
            strcat (octal,"0");
        else if (oct%8 == 7)
            strcat (octal,"7");
        else if (oct%8 == 6)
            strcat (octal,"6");
        else if (oct%8 == 5)
            strcat (octal,"5");
        else if (oct%8 == 4)
            strcat (octal,"4");
        else if (oct%8 == 3)
            strcat (octal,"3");
        else if (oct%8 == 2)
            strcat (octal,"2");
        else
	        strcat (octal,"1");
        oct/= 8;      
        i++;
   }  
   strrev (octal);
}
void decTOhexa (char decimal[], char hexa[]){
    int i=0, hex;
    hex = atoi(decimal);
    strcpy (hexa,"");
    while (hex!=0){   
        if (hex%16 == 0)
            strcat (hexa,"0");
        else if (hex%16 == 15)
            strcat (hexa,"F");
        else if (hex%16 == 14)
            strcat (hexa,"E");
        else if (hex%16 == 13)
            strcat (hexa,"D");
        else if (hex%16 == 12)
            strcat (hexa,"C");
        else if (hex%16 == 11)
            strcat (hexa,"B");
        else if (hex%16 == 10)
            strcat (hexa,"A");
        else if (hex%16 == 9)
            strcat (hexa,"9");
        else if (hex%16 == 8)
            strcat (hexa,"8");
        else if (hex%16 == 7)
            strcat (hexa,"7");
        else if (hex%16 == 6)
            strcat (hexa,"6");
        else if (hex%16 == 5)
            strcat (hexa,"5");
        else if (hex%16 == 4)
            strcat (hexa,"4");
        else if (hex%16 == 3)
            strcat (hexa,"3");
        else if (hex%16 == 2)
            strcat (hexa,"2");
        else
	        strcat (hexa,"1");
        hex/= 16;      
        i++;
   }  
   strrev (hexa);
}
void binTOdec (char decimal[],char binario[]) {
  int i, aux=0, pot=1;
  for (i=strlen(binario)-1; i>=0; i--) {
    if (binario[i] == '1')
      aux+=pot;  
    pot*=2;  
  }
  itoa(aux, decimal, 10);
}  
void hexaTOdec (char decimal[],char hexa[]) {
  int i, aux=0, pot=1;
  for (i = strlen(hexa)-1; i>=0; i--) {
    switch (toupper(hexa[i])) {
      case '0': break;
      case '1': aux+=1*pot; break;
      case '2': aux+=2*pot; break;
      case '3': aux+=3*pot; break;            
      case '4': aux+=4*pot; break;      
      case '5': aux+=5*pot; break;      
      case '6': aux+=6*pot; break;
      case '7': aux+=7*pot; break;
      case '8': aux+=8*pot; break;
      case '9': aux+=9*pot; break;            
      case 'A': aux+=10*pot; break;      
      case 'B': aux+=11*pot; break;      
      case 'C': aux+=12*pot; break;
      case 'D': aux+=13*pot; break;      
      case 'E': aux+=14*pot; break;      
      case 'F': aux+=15*pot; 
    }  
    pot*=16;  
  }
  itoa(aux, decimal, 10);    
}  
void octalTOdec (char decimal[],char octal[]) {
  int i, aux=0, pot=1;
  for (i = strlen(octal)-1; i>=0; i--) {
    switch (toupper(octal[i])) {
      case '0': break;
      case '1': aux+=1*pot; break;
      case '2': aux+=2*pot; break;
      case '3': aux+=3*pot; break;            
      case '4': aux+=4*pot; break;      
      case '5': aux+=5*pot; break;      
      case '6': aux+=6*pot; break;
      case '7': aux+=7*pot; break;
    }  
    pot*=8;  
  }
  itoa(aux, decimal, 10);    
} 
int verificaBIN (char binario[]) {
  int i;
  for (i = 0; i < strlen(binario); i++)
    if (binario[i] != '0' && binario[i] != '1')
      return 0;    
  return 1;
}    
int verificaHEXA (char hexa[]) {
  int i;
  for (i = 0; i < strlen(hexa); i++)
    if (!(hexa[i]>='0' && hexa[i]<='9') && 
        !(toupper(hexa[i])>='A' && toupper(hexa[i])<='F'))
      return 0;    
  return 1;
}   
int verificaOCTAL (char octal[]) {
  int i;
  for (i = 0; i < strlen(octal); i++)
    if (!(octal[i]>='0' && octal[i]<='7'))
      return 0;    
  return 1;
}   
int main(){
    int sair=0;
    do{
        int opc_dec;
        char opc, decimal[MAX], binario[MAX], hexa[MAX], octal[MAX];
        system("cls");
        printf ("Escolha a opcao da base a ser convertida:\n");
        printf ("1. Decimal\n2. Binario\n3. Octal\n4. Hexadecimal\n\nPara sair, aperte ESC\n");
        opc = toupper(getch());
        system("cls");
        switch(opc){
            case '1':   do{
                            printf ("Decimal para:\n1. Binario\n2. Octal\n3. Hexadecimal\n");
                                opc_dec = toupper(getch());
                            if (opc_dec=='1'){
                                system("cls");
                                printf("Digite o valor em decimal:");
                                fflush(stdin);
                                gets(decimal);
                                decTObin(decimal, binario);
                                printf("Valor em binario: %s\n\nAperte qualquer tecla para voltar\n",binario);
                                getch();
                                break;
                            }
                            else if (opc_dec=='2'){
                                system("cls");
                                printf("Digite o valor em decimal:");
                                fflush(stdin);
                                gets(decimal);
                                decTOoct(decimal, octal);
                                printf("Valor em octal: %s\n\nAperte qualquer tecla para voltar\n", octal);
                                getch();
                                break;
                            }
                            else if (opc_dec=='3'){
                                system("cls");
                                printf("Digite o valor em decimal:");
                                fflush(stdin);
                                gets(decimal);
                                decTOhexa(decimal, hexa);
                                printf("Valor em hexa: %s\n\nAperte qualquer tecla para voltar\n", hexa);
                                getch();
                                break;
                            }
                            system("cls");
                        } while(opc_dec<=0 || opc_dec>=4);
                        break;
            case '2':   do{
                            printf ("Binario para:\n1. Decimal\n2. Octal\n3. Hexadecimal\n");
                                opc_dec = toupper(getch());
                            if (opc_dec=='1'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em binario: ");
                                    fflush(stdin);
                                    gets (binario);
                                } while (!verificaHEXA(binario));
                                binTOdec(decimal, binario);
                                printf("Valor em decimal: %s\n\nAperte qualquer tecla para voltar\n",decimal);
                                getch();
                                break;
                            }
                            else if (opc_dec=='2'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em binario: ");
                                    fflush(stdin);
                                    gets (binario);
                                } while (!verificaHEXA(binario));
                                binTOdec(decimal, binario);
                                decTOoct(decimal, octal);
                                printf("Valor em octal: %s\n\nAperte qualquer tecla para voltar\n", octal);
                                getch();
                                break;
                            }
                            else if (opc_dec=='3'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em binario: ");
                                    fflush(stdin);
                                    gets (binario);
                                } while (!verificaHEXA(binario));
                                binTOdec(decimal, binario);
                                decTOhexa(decimal, hexa);
                                printf("Valor em hexa: %s\n\nAperte qualquer tecla para voltar\n", hexa);
                                getch();
                                break;
                            }
                            system("cls");
                        } while(opc_dec<=0 || opc_dec>=4);
                        break;
            case '3':   do{
                            printf ("Octal para:\n1. Decimal\n2. Binario\n3. Hexadecimal\n");
                                opc_dec = toupper(getch());
                            if (opc_dec=='1'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em octal: ");
                                    fflush(stdin);
                                    gets (octal);
                                } while (!verificaOCTAL(octal));
                                octalTOdec(decimal, octal);
                                printf("Valor em decimal: %s\n\nAperte qualquer tecla para voltar\n",decimal);
                                getch();
                                break;
                            }
                            else if (opc_dec=='2'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em octal: ");
                                    fflush(stdin);
                                    gets (octal);
                                } while (!verificaOCTAL(octal));
                                octalTOdec(decimal, octal);
                                decTObin(decimal, binario);
                                printf("Valor em binario: %s\n\nAperte qualquer tecla para voltar\n",binario);
                                getch();
                                break;
                            }
                            else if (opc_dec=='3'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em octal: ");
                                    fflush(stdin);
                                    gets (octal);
                                } while (!verificaOCTAL(octal));
                                octalTOdec(decimal, octal);
                                decTOhexa(decimal, hexa);
                                printf("Valor em hexa: %s\n\nAperte qualquer tecla para voltar\n", hexa);
                                getch();
                                break;
                            }
                            system("cls");
                        } while(opc_dec<=0 || opc_dec>=4);
                        break;
            case '4':   do{
                            printf ("Hexadecimal para:\n1. Decimal\n2. Octal\n3. Binario\n");
                                opc_dec = toupper(getch());
                            if (opc_dec=='1'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em hexa: ");
                                    fflush(stdin);
                                    gets (hexa);
                                } while (!verificaHEXA(hexa));
                                hexaTOdec(decimal, hexa);
                                printf("Valor em decimal: %s\n\nAperte qualquer tecla para voltar\n", decimal);
                                getch();
                                break;
                            }
                            else if (opc_dec=='2'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em hexa: ");
                                    fflush(stdin);
                                    gets (hexa);
                                } while (!verificaHEXA(hexa));
                                hexaTOdec(decimal, hexa);
                                decTOoct(decimal, octal);
                                printf("Valor em octal: %s\n\nAperte qualquer tecla para voltar\n", octal);
                                getch();
                                break;
                            }
                            else if (opc_dec=='3'){
                                system("cls");
                                do {
                                    printf ("Digite o valor em hexa: ");
                                    fflush(stdin);
                                    gets (hexa);
                                } while (!verificaHEXA(hexa));
                                hexaTOdec(decimal, hexa);
                                decTObin(decimal, binario);
                                printf("Valor em binario: %s\n\nAperte qualquer tecla para voltar\n", binario);
                                getch();
                                break;
                            }
                            system("cls");
                        } while(opc_dec<=0 || opc_dec>=4);
                        break;
            case 27:    system("cls");
                        sair=1;
                        break;
            default:    printf("Opcao invalida, aperte qualquer tecla para voltar\n");
                        getch();
                        break;  
        }
    } while (sair==0);
}
