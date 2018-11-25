#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* palavra;
    int ocorrencias;
}Palavra;

/*
long espalhador(char* palavra){
    long caractere = 0;
    long soma = 0;
    long i = 0; //constante para lidar com palavras que tem as mesmas letras em outra ordem
    while (caractere != EOF)
    {
        caractere = palavra[i];        
        soma += (caractere + i)*2654435769;
        i++;
    }
    return(soma%10000000);
}
*/
void imprime(Palavra* resultado, int tamanho){
    for (int i = 0; i < tamanho; i++)
    {
        if (resultado[i].palavra != NULL)
        {
            printf("%s",resultado[i].palavra);
            printf("%d\n",resultado[i].ocorrencias);
        }
    }
}

unsigned espalhador (char* s, int tam) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++)
      h = (h * 2654435769 + s[i]) % tam;
   return h;
}


int interpreta (char c)
{
    if ((c > 32 && c < 65) || (c>90 && c<97) || c>122) 
    {
        return 1;
    }
    else if (c<33) return 2;
    else if (c<0) return 3;
    else
    {

        return 0;
    } 
}

Palavra* vetorDesordenado (FILE* texto, int tamanho) {
    
    Palavra* vetor = malloc(tamanho * sizeof(Palavra));
    char* palavra = malloc(29*sizeof(char)); //29 caracteres é o tamanho da maior palavra não-técnica em português
    char charAtual;
    int estado = 0; //0 = esperando letras, 1 = montando palavra
    int indiceLetra = 0;

    while(charAtual != EOF)
    {
        charAtual = fgetc(texto);
                if (charAtual< 91 && charAtual >64)
        {
            charAtual += 32; //converte para lower case
        }
        int interpretacao = interpreta(charAtual);
        if (interpretacao == 1 || interpretacao == 2) {
            //PONTUAÇÃO OU WHITESPACE
            if (estado == 1) {
                //Terminou a palavra que estava sendo lida
                estado = 0;
                indiceLetra = 0;
                long hash;
                hash = espalhador(palavra,tamanho);
                if (vetor[hash].ocorrencias < 1)
                {
                    vetor[hash].palavra = malloc(strlen(palavra)*sizeof(char));
                    strcpy(vetor[hash].palavra,palavra);
                    vetor[hash].ocorrencias = 1;
                }
                else 
                {
                vetor[hash].ocorrencias += 1;
                }
                free(palavra);
            }
        }
        else if (interpretacao == 3)
        {
            //CARACTERE ACENTUADO
        }
        else{
            //LETRA
            if (estado != 1)
            {
                estado = 1;
                palavra = malloc(29*sizeof(char));
            }
            palavra[indiceLetra] = charAtual;
            indiceLetra++;
        }


    }
    return(vetor);
}

int main(int argc, char **argv) {
    
    int tamanho = 127;
    FILE* texto = fopen("source.txt", "r");    
    //FILE* texto = fopen(argv[1], "r");
    if (texto==NULL)
    {
        printf("erro");
    }
    //char texto[] = "esse sera o texto teste do teste da coisa";
    Palavra* resultado = vetorDesordenado(texto,tamanho);
    imprime(resultado, tamanho);
    int esperar = 1;
}


/*

    
    char teste = ' ';
    if(pontuacao(teste)==2)
    {
        printf("Entrei");
        printf("Garantir");
    }
    int x = 10;
*/