//Implementação usando lista ligada

typedef struct reg {
   int         conteudo; 
   struct reg *prox;
} celula;

void criaFila() {
  celula *fi;
  fi = malloc (sizeof (celula));
  fi->prox = fi;
  return fi;
}

// Tira um elemento da fila fi e devolve
// o conteudo do elemento removido.
// Supõe que a fila não está vazia.

int tiradafila (celula *fi) {
   celula *p;
   p = fi->prox;  // o primeiro da fila
   int x = p->conteudo;
   fi->prox = p->prox;
   free (p);
   return x;  
}

// Coloca um novo elemento com conteudo y
// na fila fi. Devolve o endereço da
// cabeça da fila resultante.

celula *colocanafila (int y, celula *fi) { 
   celula *nova;
   nova = malloc (sizeof (celula));
   nova->prox = fi->prox;
   fi->prox = nova;
   fi->conteudo = y;
   return nova;
}
