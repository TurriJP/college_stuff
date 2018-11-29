//Implementação usando lista ligada

typedef struct reg {
   char        conteudo; 
   struct reg *prox;
} celula;

void criapilha (void) {
   pi = malloc (sizeof (celula)); // cabeça
   pi->prox = NULL; 
}

void empilha (char y) { 
   celula *nova;
   nova = malloc (sizeof (celula));
   nova->conteudo = y;
   nova->prox  = pi->prox;
   pi->prox = nova; 
}

char desempilha (void) {
   celula *p;
   p = pi->prox;
   char x = p->conteudo;
   pi->prox = p->prox;
   free (p);
   return x; 
}
