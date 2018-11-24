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

Palavra* vetorDesordenado (FILE* texto) {
    Palavra* vetor;//malloc(50 * sizeof(Palavra*));
    char* palavra = malloc(10*sizeof(char));
    while(palavra != "Carlinhos")
    {
        fgets(palavra, 15, texto);
        long hash;
        hash = espalhador(palavra,50);
        /*
        if (vetor[hash] == NULL)
        {
            //vetor.insere(palavra,hash);
            vetor[hash]->palavra = palavra;
            vetor[hash]->ocorrencias = 1;
        }
        else
            //vetor[hash]->ocorrencias+=1;
            vetor[hash]->ocorrencias += 1;
        */
    }
    return(vetor);
}

int main(int argc, char **argv) {
    int x = 10;
    FILE* texto = fopen("source.txt", "r");    
    //FILE* texto = fopen(argv[1], "r");
    if (texto==NULL)
    {
        printf("erro");
    }
    //char texto[] = "esse sera o texto teste do teste da coisa";
    Palavra* resultado = vetorDesordenado(texto);
}