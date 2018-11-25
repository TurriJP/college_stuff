#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Globais que armazenam o tipo de estrutura e de ordenação
int estruturas[5] = {0,0,0,0,0};
char *ordem;

int listaVazia = 1;

//STRUCT PRINCIPAL
typedef struct{
    char* palavra;
    int ocorrencias;
    long indice;
    void* colisoes;
}Palavra;

//STRUCTS LISTA LIGADA
typedef struct elo {
  struct elo* next;
  Palavra* val;
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

void *ultimoElemento (Lista l) {
    return l.cabec->val;
}

Lista insereL (Lista l, void* val) {
    Lista aux = l;
    Elo *tmp = malloc (sizeof (Elo));
    tmp->val = val; 
    tmp->next = NULL;

    while (aux.cabec->next != NULL)
        aux.cabec = aux.cabec->next;

    aux.cabec->next = tmp;

    if (listaVazia) listaVazia = 0;

    return aux;
}


Palavra *buscaPalavra (Lista l, long hash) {
  Lista aux = l;

  //se tah olhando pra cabeca, tem q olhar pro prox
  if (aux.cabec->val == NULL && aux.cabec->next->val != NULL)
    aux.cabec = aux.cabec->next;


  while (aux.cabec != NULL) {
    long palavraB = aux.cabec->val->indice;
    if (palavraB == hash)
      return aux.cabec->val;
    aux.cabec = aux.cabec->next;
  }

  return NULL;
}

void avaliaEstrutura(char *estrutura)
{
    if (estrutura[0] == 86 && estrutura[1] == 68) estruturas[0] = 1;
    if (estrutura[0] == 86 && estrutura[1] == 79) estruturas[1] = 1;
    if (estrutura[0] == 76 && estrutura[1] == 68) estruturas[2] = 1;
    if (estrutura[0] == 76 && estrutura[1] == 79) estruturas[3] = 1;
    if (estrutura[0] == 65 && estrutura[1] == 66) estruturas[4] = 1;
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

//ORDENAÇÃO PARA LISTA LIGADA

void bubbleSort(Elo **head) 
{
    int done = 0;         // 1 quando nenhuma troca foi feita numa passagem

    // Não organizar uma lista vazia ou com um único elemento
    if (*head == NULL || (*head)->next == NULL) return;

    while (!done) {
        Elo **pv = head;            // fonte do ponteiro para o nó atual na lista
        Elo *nd = *head;            // ponteiro de iteração local
        Elo *nx = (*head)->next;    // ponteiro com o próximo ponteiro

        done = 1;

        while (nx) {
            int cmp; 
            if (ordem[0] == 65) cmp = strcmp(nd->val->palavra, nx->val->palavra); //Alfabética
            if (ordem[0] == 79) cmp = (nx->val->ocorrencias - nd->val->ocorrencias); 
            if (cmp > 0) {
                nd->next = nx->next;
                nx->next = nd;
                *pv = nx;

                done = 0;
            }
            pv = &nd->next;
            nd = nx;
            nx = nx->next;
        }
    }
}

//FUNÇÕES PARA IMPRIMIR O RESULTADO

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

void imprimeLista(Lista* resultado)
{
  if (resultado->cabec->val == NULL && resultado->cabec->next->val != NULL)
    resultado->cabec = resultado->cabec->next;


  while (resultado->cabec != NULL) {
    printf("%s ",resultado->cabec->val->palavra);
    printf("%d\n",resultado->cabec->val->ocorrencias);
    resultado->cabec = resultado->cabec->next;
  }

  return;
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

void hashVetor(Palavra* vetor, char* palavra, long hash)
{
    if (vetor[hash].ocorrencias < 1)
    {
        vetor[hash].palavra = malloc(strlen(palavra)*sizeof(char));
        strcpy(vetor[hash].palavra,palavra);
        vetor[hash].ocorrencias = 1;
        vetor[hash].indice = hash;
    }
    else 
    {
    //Implementar um check aqui pra ver se não há colisões nesse índice
    vetor[hash].ocorrencias += 1;
    }
    free(palavra);
}

void hashLista(Lista lista, char* palavra, long hash)
{
    if (listaVazia)
    {
        Palavra* novoElemento = malloc(sizeof(Palavra));
        novoElemento->palavra = palavra;
        novoElemento->ocorrencias = 1;
        novoElemento->indice = hash;
        lista = insereL(lista,novoElemento);
        return;

    }
    Palavra *resultado = buscaPalavra(lista,hash);
    if (resultado == NULL)
    {
        //Palavra ainda não está na lista
        Palavra* novoElemento = malloc(sizeof(Palavra));
        novoElemento->palavra = palavra;
        novoElemento->ocorrencias = 1;
        novoElemento->indice = hash;
        //Fazer aqui um check no caso de ordenação
        lista = insereL(lista,novoElemento);
    }
    else
    {
        //Implementar um check aqui pra ver se há colisões nesse hash
        resultado->ocorrencias += 1;
    }
    return;
}

void* processaTexto (FILE* texto, int tamanho) {
    
    //Preciso criar todas as estruturas e dar free nas irrelevantes
    //O compilador não deixou criar variáveis dentro de um if
    Palavra* vetor = malloc(tamanho * sizeof(Palavra));
    if (!estruturas[0]&&!estruturas[1]) free(vetor);

    Lista listapalavras = criaL();
    
    
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
                if (estruturas[0]||estruturas[1]) hashVetor(vetor, palavra, hash);
                if (estruturas[2]||estruturas[3]) hashLista(listapalavras, palavra, hash);


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
    FILE* texto = fopen(argv[1], "r");
    char *estrutura = argv[2];
    ordem = argv[3];
    avaliaEstrutura(estrutura);

    if (estruturas[0]||estruturas[1])
    {
        Palavra* resultado = processaTexto(texto,tamanho);
        if (estruturas[1])
        {
            if (ordem[0] == 65) qsort(resultado, tamanho, sizeof(Palavra), ordenaAlfa);
            if (ordem[0] == 79) qsort(resultado, tamanho, sizeof(Palavra), ordenaNum);
        }
        imprime(resultado, tamanho);
    }

    if (estruturas[2]||estruturas[3])
    {
        Lista* resultado = processaTexto(texto,tamanho);
        if (estruturas[3])
        {
            bubbleSort(resultado);
        }
        imprimeLista(resultado);
    }

    return 0;
}

