#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCT PRINCIPAL
typedef struct{
    char* palavra;
    int ocorrencias;
}Palavra;

//STRUCTS LISTA LIGADA
typedef struct elo {
  struct elo* next;
  void *val;
} Elo;

typedef struct {
    Elo* cabec;
} Lista;

Lista criaL () {
    Lista tmp;
    tmp.cabec = malloc (sizeof (Elo));
    tmp.cabec->val = NULL;
    tmp.cabec->next = NULL;
    return tmp;
}

int fimDaLista (Lista l) {
    if (l.cabec->next == NULL)
        return 1;
    return 0;
}

void* ultimoElemento (Lista l) {
    return l.cabec->val;
}

Lista insereL (Lista l, void* val) {
    Lista aux = l;
    Elo *tmp = malloc (sizeof (Elo));
    tmp->val = val; tmp->next = NULL;

    while (aux.cabec->next != NULL)
        aux.cabec = aux.cabec->next;

    aux.cabec->next = tmp;

    return aux;
}

void* retiraL (Lista ant, Lista atual) {
    void *aux = atual.cabec->val;

    ant.cabec->next = atual.cabec->next;
    free (atual.cabec);

    return aux;
}


int ordenaNum (const void * a, const void * b)
{

    Palavra *palavraA = (Palavra *)a;
    Palavra *palavraB = (Palavra *)b;

    return(palavraB->ocorrencias - palavraA->ocorrencias);
}

int ordenaAlfa (const void * a, const void * b)
{

    Palavra *palavraA = (Palavra *)a;
    Palavra *palavraB = (Palavra *)b;
    if (palavraA->palavra == NULL) return 1;
    if (palavraB->palavra == NULL) return -1;

    return strcmp(palavraA->palavra, palavraB->palavra);
}

void imprime(Palavra* resultado, int tamanho){
    for (int i = 0; i < tamanho; i++)
    {
        if (resultado[i].palavra != NULL)
        {
            printf("%s ",resultado[i].palavra);
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
    Palavra* resultado = vetorDesordenado(texto,tamanho);
    qsort(resultado, tamanho, sizeof(Palavra), ordenaAlfa);
    imprime(resultado, tamanho);
    int esperar = 1;
}

