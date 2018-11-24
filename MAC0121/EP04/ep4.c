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
unsigned espalhador (char* s, int tam) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++)
      h = (h * 256 + s[i]) % tam;
   return h;
}


int interpreta (char c)
{
    if ((c > 32 && c < 65) || (c>90 && c<97) || c>122) 
    {
        return 1;
    }
    else if (c<33) return 2;
    else return 0;
}

Palavra* vetorDesordenado (FILE* texto) {
    
    int tamanho = 50;
    Palavra* vetor = malloc(50 * sizeof(Palavra));
    char* palavra = malloc(29*sizeof(char)); //29 caracteres é o tamanho da maior palavra não-técnica em português
    char charAtual;
    int estado = 0; //0 = esperando letras, 1 = montando palavra
    int indiceLetra = 0;

    while(charAtual != EOF)
    {
        charAtual = fgetc(texto);
        int interpretacao = interpreta(charAtual);
        if (interpretacao != 0) {
            //PONTUAÇÃO OU WHITESPACE
            if (estado == 1) {
                //Terminou a palavra que estava sendo lida
                estado = 0;
                indiceLetra = 0;
                long hash;
                hash = espalhador(palavra,tamanho);
                if (vetor[hash].ocorrencias == 0)
                {
                    //vetor.insere(palavra,hash);
                    vetor[hash].palavra = palavra;
                    vetor[hash].ocorrencias = 1;
                }
                else
                    //vetor[hash]->ocorrencias+=1;
                    vetor[hash].ocorrencias += 1;
            }
        }
        else{
            //LETRA
            if (estado != 1) estado = 1;
            palavra[indiceLetra] = charAtual;
            indiceLetra++;
        }


    }
    return(vetor);
}

int main(int argc, char **argv) {

    FILE* texto = fopen("source.txt", "r");    
    //FILE* texto = fopen(argv[1], "r");
    if (texto==NULL)
    {
        printf("erro");
    }
    //char texto[] = "esse sera o texto teste do teste da coisa";
    Palavra* resultado = vetorDesordenado(texto);
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