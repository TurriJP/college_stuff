/*
Árvores Binárias
Percursos
Profundidade: vai fazendo as escolhas até chegar numa folha, depois backtrackeia até percorrer tudo
Largura: Nível por Nível
Pré ordem: visito a raiz; visito a subárvore esquerda da raiz em pré-ordem; visito a subárvore direita da raiz em pré-ordem (na verdade é só a busca em profundidade)
Numa árvore que representa uma expressão aritmética, dá a notação pré-fixa da expressão
*/

void pré-ordem(apontador raiz)
{
    if(raiz!=NULL)
    {
        printf("%c",raiz->info);
        pré-ordem(raiz->esq);
        pré-ordem(raiz->dir);
    }
}

/*
In-ordem:
-visita os nós da subárvore esquerda in-ordem
-visita a raiz
-visita os nós da sub-árvore direita em in-ordem
*/

void in-ordem(apontador raiz)
{
    if(raiz!=NULL)
    {
        in-ordem(raiz->esq);
        printf("%c",raiz->info);
        in-ordem(raiz->dir);
    }
}

/*
Pós-ordem
-Visita a subárvore esquerda
-Visita a subárvore direita
-Visita a raiz
Numa árvore que representa uma expressão aritmética, dá a notação pós-ordem da operação 
*/

void pós-ordem(apontador raiz)
{
    if(raiz!=NULL)
    {
        pós-ordem(raiz->esq);
        pós-ordem(raiz->dir);
        printf("%c",raiz->info);
    }
}

/*
Se te derem uma lista da pré-ordem e uma da in-ordem, é possível remontar a lista
A pré vai te dando as raízes, e olhando a pós você sabe se cada elemento está à esquerda ou à direita do elemento anterior
Tb dá pra fazer isso com in+pós; mas se vc tem só a pré e a pós, não tem como diferenciar casos de quiralidade
*/

int ancestral(apontador p, apontador q)
{
    if(p==NULL||q==NULL) return 0;
    if(p==q) return 1;
    return(ancestral(p->esq,q)||ancestral(p->dir,q));
}

int ancestral2(apontador p, apontador q)
{
    //caso exista um ponteiro pro pai
    apontador aux = q;
    if(p==NULL) return 0;
    while(aux!=NULL && aux!=p)
        aux=aux->pai;
    return(aux==p);
}

apontador ancestralComumMaisProximo(apontador p, apontador q)
{
    //minha implementação
    while !(ancestral(p,q))
    {
        p = p->pai;
    }
    return ṕ;
}
//O(n)

int nivel(apontador p)
{
    //p!=NULL
    int cont = 0;
    while (p->pai !=NULL)
    {
        cont++;
        p=p->pai;
    }
    return cont;
}

apontador aCMP(apontador p, apontador q)
{
    int np=nivel(p),nq=nivel(q);
    while(np>nq)
    {
        p=p->pai;
        np--;
    }
    while(nq>np)
    {
        q=q->pai;
        nq--;
    }
    while(p!=q)
    {
        p=p->pai;
        q=q->pai;
    }
    return p;
}
//tempo de execução proporcional à altura da árvore 

apontador ancestralDoBrother(apontador p, apontador q)
{
    while(ancestral(p,q)==0)
        p=p->pai;
    return p;
}

void imprimeFolhas(apontador raiz)
{
    if(raiz!=NULL)
    {
        if(raiz->esq==NULL && raiz->dir==NULL)
            printf("%c",raiz->info);
            //Se for uma folha, imprime
        else
        {
            imprimeFolhas(raiz->esq);
            imprimeFolhas(raiz->dir);
        }
    }
}