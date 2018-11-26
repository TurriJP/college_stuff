#include <stdlib.h>
#include <stdio.h>

typedef struct reg {
   int conteudo;
   struct reg *prox;
} celula;

void imprime (celula *le) {
   if (le != NULL) {
      printf ("%d\n", le->conteudo);
      imprime (le->prox);
   }
}

// Esta função recebe um inteiro x e uma
// lista encadeada le de inteiros e devolve
// o endereço de uma celula que contém x.
// Se tal celula não existe, devolve NULL.

celula *busca (int x, celula *le)
{
   celula *p;
   p = le;
   while (p != NULL && p->conteudo != x) 
      p = p->prox; 
   return p;
}

//Versão recursiva da busca
celula *busca_r (int x, celula *le)
{
   if (le == NULL)  return NULL;
   if (le->conteudo == x)  return le;
   return busca_r (x, le->prox);
}

celula *criaLista()
{
   celula *le;
   le = malloc (sizeof (celula));
   le->prox = NULL;
   return le;
}

// Esta função insere uma nova celula
// em uma lista encadeada. A nova celula
// tem conteudo x e é inserida entre a
// celula p e a celula seguinte.
// (Supõe-se que p != NULL.)

void 
insere (int x, celula *p)
{
   celula *nova;
   nova = malloc (sizeof (celula));
   nova->conteudo = x;
   nova->prox = p->prox;
   p->prox = nova;
}

// Esta função recebe o endereço p de uma 
// celula de uma lista encadeada e remove 
// da lista a celula p->prox. A função supõe
// que p != NULL e p->prox != NULL.

void 
remove (celula *p)
{
   celula *lixo;
   lixo = p->prox;
   p->prox = lixo->prox;
   free (lixo);
}

// Esta função recebe uma lista encadeada le
// com cabeça e remove da lista a primeira
// celula que contiver y, se tal celula existir.

void busca_e_remove (int y, celula *le)
{
   celula *p, *q;
   p = le;
   q = le->prox;
   while (q != NULL && q->conteudo != y) {
      p = q;
      q = q->prox;
   }
   if (q != NULL) {
      p->prox = q->prox;
      free (q);
   }
}

// Esta função recebe uma lista encadeada le
// com cabeça e insere na lista uma nova celula
// imediatamente antes da primeira que contém y.
// Se nenhuma celula contém y, insere a nova
// celula no fim da lista. O conteudo da nova
// celula é x.

void busca_e_insere (int x, int y, celula *le)
{
   celula *p, *q, *nova;
   nova = malloc (sizeof (celula));
   nova->conteudo = x;
   p = le;
   q = le->prox;
   while (q != NULL && q->conteudo != y) {
      p = q;
      q = q->prox;
   }
   nova->prox = q;
   p->prox = nova;
}