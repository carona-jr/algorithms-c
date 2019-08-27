#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
void escreveUnidade (char valor[], char escrito[], int i, int cont){
    switch (valor[i]){
        case '1': if((cont)>=2) 
                    strcat (escrito, " e ");
                  strcat (escrito, "um");
                  break;
        case '2': if((cont)>=2) 
                    strcat (escrito, " e ");
                  strcat (escrito, "dois");
                  break;
        case '3': if((cont)>=2) 
                    strcat (escrito, " e ");
                  strcat (escrito, "tres");
                  break;
        case '4': if((cont)>=2) 
                    strcat (escrito, " e ");
                  strcat (escrito, "quatro");
                  break;
        case '5': if((cont)>=2) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "cinco");
                  break;
        case '6': if((cont)>=2) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "seis");
                  break;
        case '7': if((cont)>=2) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "sete");
                  break;
        case '8': if((cont)>=2) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "oito");
                  break;
        case '9': if((cont)>=2) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "nove");
                  break;
    }
}
void escreveDezena (char valor[], char escrito[], int i, int cont, int *aux, int *aux3){
    switch (valor[i]){
        case '1': if((cont)>=3) 
                    strcat (escrito, " e ");  
                  if(valor[i-1]=='0')
                      strcat (escrito, "dez");
                  else if(valor[i-1]=='1')
                      strcat (escrito, "onze");
                  else if(valor[i-1]=='2') 
                      strcat (escrito, "doze");
                  else if(valor[i-1]=='3') 
                      strcat (escrito, "treze");
                  else if(valor[i-1]=='4') 
                      strcat (escrito, "quatorze");
                  else if(valor[i-1]=='5') 
                      strcat (escrito, "quinze");
                  else if(valor[i-1]=='6') 
                      strcat (escrito, "dezesseis");
                  else if(valor[i-1]=='7') 
                      strcat (escrito, "dezessete");
                  else if(valor[i-1]=='8') 
                      strcat (escrito, "dezoito");
                  else if(valor[i-1]=='9') 
                      strcat (escrito, "dezenove");
                  *aux=*aux3=1;
                  break;
        case '2': if((cont)>=3) 
                    strcat (escrito, " e ");  
                  strcat (escrito, "vinte");
                  break;
        case '3': if((cont)>=3) 
                    strcat (escrito, " e ");  
                  strcat (escrito, "trinta");
                  break;
        case '4': if((cont)>=3) 
                    strcat (escrito, " e ");  
                  strcat (escrito, "quarenta");
                  break;
        case '5': if((cont)>=3) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "cinquenta");
                  break;
        case '6': if((cont)>=3) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "sessenta");
                  break;
        case '7': if((cont)>=3) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "setenta");
                  break;
        case '8': if((cont)>=3) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "oitenta");
                  break;
        case '9': if((cont)>=3) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "noventa");
                  break;
    }
}
void escreveCentena (char valor[], char escrito[], int i, int cont){
    switch (valor[i]){
        case '1': if((cont)>=4) 
                    strcat (escrito, " e ");
                  if (valor[i-1]=='0' && valor[i-2]=='0'){
                      strcat (escrito, "cem");
                      break;
                  }  
                  strcat (escrito, "cento");
                  break;
        case '2': if((cont)>=4) 
                    strcat (escrito, " e ");  
                  strcat (escrito, "duzentos");
                  break;
        case '3': if((cont)>=4) 
                    strcat (escrito, " e ");  
                  strcat (escrito, "trezentos");
                  break;
        case '4': if((cont)>=4) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "quatrocentos");
                  break;
        case '5': if((cont)>=4) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "quinhentos");
                  break;
        case '6': if((cont)>=4) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "seiscentos");
                  break;
        case '7': if((cont)>=4) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "setecentos");
                  break;
        case '8': if((cont)>=4) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "oitocentos");
                  break;
        case '9': if((cont)>=4) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "novecentos");
                  break;
    }
}
void escreveMilhar (char valor[], char escrito[], int i, int cont){
    switch (valor[i]){
        case '1': if((cont)>=5) 
                    strcat (escrito, " e ");
                  else if (stricmp(valor, "0001")==0){
                      strcat (escrito, "um mil");
                      break;
                  }
                  strcat (escrito, "um mil");
                  break;
        case '2': if((cont)>=5) 
                    strcat (escrito, " e ");  
                  strcat (escrito, "dois mil");
                  break;
        case '3': if((cont)>=5) 
                    strcat (escrito, " e ");  
                  strcat (escrito, "tres mil");
                  break;
        case '4': if((cont)>=5) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "quatro mil");
                  break;
        case '5': if((cont)>=5) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "cinco mil");
                  break;
        case '6': if((cont)>=5) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "seis mil");
                  break;
        case '7': if((cont)>=5) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "sete mil");
                  break;
        case '8': if((cont)>=5) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "oito mil");
                  break;
        case '9': if((cont)>=5) 
                    strcat (escrito, " e "); 
                  strcat (escrito, "nove mil");
                  break;
    }
}
void escreveMilhares (char valor[], char escrito[], int i, int cont, int *aux2){
    switch (valor[i]){
        case '1': if((cont)>=6) 
                    strcat (escrito, " e ");
                  if (valor[i-1]=='0')
                      strcat (escrito, "dez mil");
                  else if (valor[i-1]=='1')
                      strcat (escrito, "onze mil");
                  else if (valor[i-1]=='2')
                      strcat (escrito, "doze mil");
                  else if (valor[i-1]=='3')
                      strcat (escrito, "treze mil");
                  else if (valor[i-1]=='4')
                      strcat (escrito, "quatorze mil");
                  else if (valor[i-1]=='5')
                      strcat (escrito, "quinze mil");
                  else if (valor[i-1]=='6')
                      strcat (escrito, "dezesseis mil");
                  else if (valor[i-1]=='7')
                      strcat (escrito, "dezessete mil");
                  else if (valor[i-1]=='8')
                      strcat (escrito, "dezoito mil");
                  else if (valor[i-1]=='9')
                      strcat (escrito, "dezenove mil");
                  *aux2=1;
                  break;
        case '2': if((cont)>=6) 
                    strcat (escrito, " e ");  
                  if (stricmp(valor, "00002")==0){
                      strcat (escrito, "vinte mil");
                      break;
                  }  
                  if (valor[i-1]=='0'){
                      strcat (escrito, "vinte mil");
                      break;
                  }
                  strcat (escrito, "vinte");
                  break;
        case '3': if((cont)>=6) 
                    strcat (escrito, " e "); 
                  if (stricmp(valor, "00003")==0){
                      strcat (escrito, "trinta mil");
                      break;
                  }     
                  if (valor[i-1]=='0'){
                      strcat (escrito, "trinta mil");
                      break;
                  }
                  strcat (escrito, "trinta");
                  break;
        case '4': if((cont)>=6) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "00004")==0){
                      strcat (escrito, "quarenta mil");
                      break;
                  }    
                  if (valor[i-1]=='0'){
                      strcat (escrito, "quarenta mil");
                      break;
                  }
                  strcat (escrito, "quarenta");
                  break;
        case '5': if((cont)>=6) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "00005")==0){
                      strcat (escrito, "cinquenta mil");
                      break;
                  }   
                  if (valor[i-1]=='0'){
                      strcat (escrito, "cinquenta mil");
                      break;
                  }
                  strcat (escrito, "cinquenta");
                  break;
        case '6': if((cont)>=6) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "00006")==0){
                      strcat (escrito, "sessenta mil");
                      break;
                  }   
                  if (valor[i-1]=='0'){
                      strcat (escrito, "sessenta mil");
                      break;
                  }
                  strcat (escrito, "sessenta");
                  break;
        case '7': if((cont)>=6) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "00007")==0){
                      strcat (escrito, "setenta mil");
                      break;
                  }   
                  if (valor[i-1]=='0'){
                      strcat (escrito, "setenta mil");
                      break;
                  }
                  strcat (escrito, "setenta");
                  break;
        case '8': if((cont)>=6) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "00008")==0){
                      strcat (escrito, "oitenta mil");
                      break;
                  }
                  if (valor[i-1]=='0'){
                      strcat (escrito, "oitenta mil");
                      break;
                  }   
                  strcat (escrito, "oitenta");
                  break;
        case '9': if((cont)>=6) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "00009")==0){
                      strcat (escrito, "noventa mil");
                      break;
                  }
                  if (valor[i-1]=='0'){
                      strcat (escrito, "noventa mil");
                      break;
                  }   
                  strcat (escrito, "noventa");
                  break;
    }
}
void escreveMilhares_Milhao (char valor[], char escrito[], int i, int cont){
    switch (valor[i]){
        case '1': if((cont)>=7) 
                    strcat (escrito, " e ");
                  if (valor[i-1]=='0' && valor[i-2]=='0'){
                      strcat (escrito, "cem");
                      break;
                  }
                  strcat (escrito, "cento");
                  break;
        case '2': if((cont)>=7) 
                    strcat (escrito, " e ");  
                  if (stricmp(valor, "000002")==0){
                      strcat (escrito, "duzentos mil");
                      break;
                  }  
                  strcat (escrito, "duzentos");
                  break;
        case '3': if((cont)>=7) 
                    strcat (escrito, " e "); 
                  if (stricmp(valor, "000003")==0){
                      strcat (escrito, "trezentos mil");
                      break;
                  }     
                  strcat (escrito, "trezentos");
                  break;
        case '4': if((cont)>=7) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "000004")==0){
                      strcat (escrito, "quatrocentos mil");
                      break;
                  }    
                  strcat (escrito, "quatrocentos");
                  break;
        case '5': if((cont)>=7) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "000005")==0){
                      strcat (escrito, "quinhentos mil");
                      break;
                  }   
                  strcat (escrito, "quinhentos");
                  break;
        case '6': if((cont)>=7) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "000006")==0){
                      strcat (escrito, "seiscentos mil");
                      break;
                  }   
                  strcat (escrito, "seiscentos");
                  break;
        case '7': if((cont)>=7) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "000007")==0){
                      strcat (escrito, "setecentos mil");
                      break;
                  }   
                  strcat (escrito, "setecentos");
                  break;
        case '8': if((cont)>=7) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "000008")==0){
                      strcat (escrito, "oitocentos mil");
                      break;
                  }   
                  strcat (escrito, "oitocentos");
                  break;
        case '9': if((cont)>=8) 
                    strcat (escrito, " e ");
                  if (stricmp(valor, "000009")==0){
                      strcat (escrito, "novecentos mil");
                      break;
                  }   
                  strcat (escrito, "novecentos");
                  break;
    }
}
void escreveMilhao (char valor[], char escrito[], int i, int cont){
        switch (valor[i]){
        case '1': if((cont)>=8) 
                    strcat (escrito, " e ");
                  if (valor[i-1]=='0' && valor[i-2]=='0'){
                      strcat (escrito, "um milhao de");
                      break;
                  }
                  strcat (escrito, "um milhao de");
                  break;
        }
}
void escreveEspeciais (char valor[], char escrito[], int i, int cont){
}
int cheque (){
    char resp;
    do{
        int cont, i, num, aux=0, aux2=0, cont2, aux3=0, num2;
        char valor[MAX], escrito[MAX]="\0", centavos[MAX];
        do{
        printf ("Digite o valor em reais:");
        fflush(stdin);
        gets(valor);
        printf ("Digite o valor em centavos:");
        gets(centavos);
        num = atoi(valor);
        num2 = atoi(centavos);
        } while ((num<0 || num>1000000) && (num2<0 || num2>99));
        cont = strlen(valor);
        strrev(valor);
        for (i=cont-1; i>=0; i--){
            if (i==0 && aux==0)
                escreveUnidade(valor, escrito, i, cont);
            else if (i==1)
                escreveDezena(valor, escrito, i, cont, &aux, &aux3);
            else if (i==2)
                escreveCentena(valor, escrito, i, cont);
            else if (i==3 && aux2==0)
                escreveMilhar(valor, escrito, i, cont);
            else if (i==4)
                escreveMilhares(valor, escrito, i, cont, &aux2);
            else if (i==5)
                escreveMilhares_Milhao(valor, escrito, i, cont);
            else if (i==6)
                escreveMilhao(valor, escrito, i, cont);
        }
        if (stricmp(valor, "1")==0)
            strcat (escrito, " real e ");
        else
            strcat (escrito, " reais e ");
        cont2 = strlen(centavos);
        strrev(centavos);
        for (i=cont2-1; i>=0; i--){
            if (i==0 && aux3==0)
                escreveUnidade(centavos, escrito, i, cont2);
            else if (i==1)
                escreveDezena(centavos, escrito, i, cont2, &aux, &aux3);
        }
        if (stricmp(centavos, "1")==0)
            strcat (escrito, " centavo");
        else
            strcat (escrito, " centavos");
        if ((stricmp(valor, "0")==0 || stricmp(valor, "\0")==0) && (stricmp(centavos, "0")==0 || stricmp(centavos, "0")==0))
            strcpy(escrito, "SEM VALOR");
        printf ("%s\n",escrito);
        printf("\n\nPara para voltar aperte ESC\nOu aperte qualquer tecla para continuar\n\n");
        resp = toupper(getch());
    } while (resp!=27);
}