int nRainhasrec (int ** tab, int n, int atual)
{
    if (atual==n) return 1;
    for (col=0; col < n; col++)
    {
        if (PosicaoLivre(tab, n, atual, col)==1)
        {
            tab[atual][col] = 1;
            if (nRainhasrec(tab,n,atual+1)) return 1;
            tab[atual][col]=0
        }
        return 0;
    }
}

int main()
{
    int **tab, n;
    scanf("%d",&n);
    tab = alocaMatriz(n,n);
    if (nRainhasrec(tab,n,0)==1)
    {
        imprimeMatriz(tab,n,n);
    }
    else printf("Não tem solução \n");
}

/*Faça uma função recursiva que recebe um vetor y, com n>=0 inteiros e um inteiro x
e devolve um índice i do vetor com v[i]=x ou -1 se x não está no vetor */
int estaOuNao(int *y, int n, int x)
{
    i = n;
    for(i > 0; i--)
    {

    }
    return(-1)

}

int buscarec(int v[], int n, int x)
{
    if (n==0) return (-1);
    if (v[n-1]==x) return (n-1);
    return(buscarec(v, n-1, x));
    //Pior caso: n recursões
    //Mlehor caso: O(1) quando x está logo no primeiro índice checado
}

int busca(int v[], int n, int x)
{
    int i = n-1;
    while (i>=0 && v[i]!=x) i--;
    return i;
    //Pior caso: n comparações O(n) quando X não está lá
    //Melhor caso: O(1) x==v[n-1]
}