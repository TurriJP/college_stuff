#include <stdlib.h>
#include <stdio.h>

typedef struct reg {
    int  conteudo; // conteúdo
    cell *esq;
    cell *dir;
} cell; // nó

typedef struct reg {
    int conteudo;
    int chave; // para Árvore de Busca Binária
    struct reg *pai;
    struct reg *esq, *dir;
} noh;

typedef noh *arvore; //ponteiro para o nó que é raiz da árvore

// Recebe a raiz r de uma árvore binária e
// imprime os conteúdos dos seus nós
// em ordem esquerda-raiz-direita. (INFIXA)

void erd (arvore r) {
   if (r != NULL) {
      erd (r->esq);
      printf ("%d\n", r->conteudo);
      erd (r->dir); 
   }
}

// Recebe uma árvore binária não vazia r
// e devolve o primeiro nó da árvore
// na ordem e-r-d.

noh *primeiro (arvore r) {  
    while (r->esq != NULL) 
       r = r->esq;
    return r;
}

// Recebe o endereço de um nó x. Devolve o endereço 
// do nó seguinte na ordem e-r-d.
// A função supõe que x != NULL.

noh *seguinte (noh *x) {  
    if (x->dir != NULL) {
       noh *y = x->dir; 
       while (y->esq != NULL) y = y->esq;
       return y;                               // A
    }
    while (x->pai != NULL && x->pai->dir == x) // B 
       x = x->pai;                             // B
    return x->pai;
}

// Devolve a altura da árvore binária
// cuja raiz é r.

int altura (arvore r) {
   if (r == NULL) 
      return -1; // altura da árvore vazia
   else {
      int he = altura (r->esq);
      int hd = altura (r->dir);
      if (he < hd) return hd + 1;
      else return he + 1;
   }
}

//RELAÇÃO ENTRE ALTURA E NÚMERO DE NÓS (log na base 2):
// n−1  >=  h  >=  floor(log(n))
//Se a altura é n-1, cada nó tem no máximo 1 filho; árvore "espichada"


/*
ÁRVORE DE BUSCA BINÁRIA
*/

// Recebe uma árvore de busca r e
// um número k. Devolve um nó
// cuja chave é k; se tal nó não existe,
// devolve NULL.

noh *busca (arvore r, int k) {
    if (r == NULL || r->chave == k)
       return r;
    if (r->chave > k)
       return busca (r->esq, k);
    else
       return busca (r->dir, k);
}
//No pior caso, a busca consome tempo proporcional à altura
//Se a árvore for balanceada (em cada nó, os filhos tem alturas parecidas)
//o tempo será proporcional a log(n), onde n é o número de nós

noh *criaNoh(int k, struct reg* pai) {
    noh *novo;
    novo = malloc (sizeof (noh));
    novo->chave = k;
    novo->esq = novo->dir = NULL;
    novo->pai = pai;
    return novo;
}

// A função a seguir recebe uma árvore de busca r
// e uma folha avulsa novo e insere a folha
// na árvore de modo que a árvore continue
// sendo de busca. A função devolve a raiz 
// da árvore resultante.

arvore insere (arvore r, noh *novo) {  
    if (r == NULL) return novo;
    if (r->chave > novo->chave) 
       r->esq = insere (r->esq, novo);
    else 
       r->dir = insere (r->dir, novo);
    return r;
}

// Recebe uma árvore não vazia r.
// Remove a raiz da árvore e rearranja
// a árvore de modo que ela continue sendo
// de busca. Devolve o endereço da
// nova raiz.
//Para remover o filho esquerdo de um nó x faça
//x->esq = removeraiz (x->esq);

arvore removeraiz (arvore r) {  
    noh *p, *q;
    if (r->esq == NULL) {
       q = r->dir;
       free (r);
       return q;
    }
    p = r; q = r->esq;
    while (q->dir != NULL) {
       p = q; q = q->dir;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->dir = q->esq;
       q->esq = r->esq;
    }
    q->dir = r->dir;
    free (r);
    return q;
}



