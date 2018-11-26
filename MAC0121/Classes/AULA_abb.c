/*
árvore de busca binária
AB em que, para cada nó, a informação de todo nó na subárvore esquerda é menor que a info do nó,
e todo nó da subárvore direita é maior

estrutura boa quando vou receber dados desordenados
*/

apontador busca (apontador raiz, TipoDaArbore x)
{
    //devolve um apontador para o nó que contem x ou NULL se x não está na árvore
    if(raiz==NULL || raiz->info==x)
        return raiz;
    if(raiz->info > x)
        return(busca(raiz->esq,x));
    return(busca(raiz->dir,x)); //O(altura)
}

apontador busca(apontador raiz, TipoDaArbore x)
{
    apontador p = raiz;
    while(p!=NULL && p->info!=x)
        if(p->info>x)
            p=p->esq;
        else
            p=p->dir;
    return(p); //O(altura)
}

apontador minimo(apontador raiz)
{
    apontador p=raiz;
    while(p!=NULL && p->esq!=NULL)
        p=p->esq;
    return(p);
}

apontador insere(apontador raiz, TipoDaArvore x)
//complexidade: O(altura)
{
    //devolve um apontador para a raiz da árvore com x incluído
    if(raiz==NULL)
    {
        raiz=malloc(sizeof(celula));
        raiz->info=x;
        raiz->dir = raiz->esq = NULL;
        //return(raiz); DESNECESSARIO
    }
    if(raiz->info>x)
        raiz->esq = insere(raiz->esq,x);
    else if(raiz->info<x)
        raiz->dir=insere(raiz->dir,x);
    return(raiz);
}

apontador insere(apontador raiz, TipoDaArvore x)
//versão iterativa
{
    apontador p,q,novo;
    p=raiz;
    q=NULL;
    while(p!=NULL && p->info!=x)
    {
        q=p;
        if(p->info>x)
            p=p->esq;
        else
            p=p->dir;
    }
    if(p==NULL)
    {
        novo=malloc(sizeof(celula));
        novo->info=x;
        novo->esq = novo->dir = NULL;
        novo->pai = q;
        if(q==NULL)
            raiz=novo;
        else if(q->info < x)
            q->dir = novo;
        else
            q->esq = novo;
    }
    return(raiz);
}

apontador remove(apontador raiz, TipoDaArvore x)
//recursivo; O(altura)
{
    apontador aux;
    if(raiz!=NULL)
    {
        if(raiz->info > x)
            raiz->esq=remove(raiz->esq,x)
        else if(raiz->info<x)
            raiz->dir=remove(raiz->dir,x);
        else
        {
            if(raiz->dir==NULL)
            {
                aux = raiz;
                raiz = raiz->esq;
                if(raiz!=NULL)
                    raiz->pai = aux->pai;
                free(aux);
            }
            else if(raiz->esq==NULL)
            {
                aux=raiz;
                raiz=raiz->dir;
                raiz->pai = aux->pai;
                free(aux)
            }
            else //tem os dois filhos
            {
                aux = maximo(raiz->esq);
                raiz->info = aux->info;
                raiz->esq = remove(raiz->esq,aux->info);
            }
        }
    }
    return(raiz);
}

//ler N números e construir uma ABB com esses números
int main()
{
    apontador raiz;
    int i,n,x;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",x);
        raiz=insere(raiz,x);
    }
    in-ordem(raiz);
}