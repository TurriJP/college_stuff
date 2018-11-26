//Algoritmo de Djikstra - versão básica

int caminhoMinimo (int **lab, int m, int n, posicaorato, posicaoqueijo)
{
    Fila F = CriaFila (m+n);
    posicaoatual = rato, prox;
    int dir, temsol = 1;
    lab[atual.linha][atual.col] = 1;
    insere(F, atual);
}

while (!FilaVazia(F) && (atual.linha != queijo.linha || atual.col != queijo.col))
{
    atual = PrimeiroDaFila(F);
    remove(F);
    for (dir = 0; dir < 4; dir++)
    {
        if(PodeIr(lab,m,n,atual,dir))
        {
            prox = anda(atual, dir);
            insere(F,prox);
            lab[prox.linha][prox.col] = lab[atual.linha][atual.col] +1;
        }
    }
    if (atual.linha == queijo.linha && atual.col == queijo.col)
    {
        imprimeMatriz(lab, m, n);
    }
    else 
    {
        printf("Não tem caminho");
        temsol = 0;
    }
    destroiFila(F);
    return(temsol);
}

//Recursao

/*
Dizemos que uma função é recursiva se em sua definição a própria função é utilizada.
EX: N fatorial é N vezes N-1 fatorial
EX2: 2 ^ n = 1, se n=0; 2.2 ^ n-1, n > 0
EX3: Fibonacci 

Em Computação dizemos que uma função é recursiva se dentro do corpo da função temos uma chamada para ela própria. 
Nem todas as linguagens de programação implementam recursão.
Precisa haver um caso base para assegurar que a função termine.
*/

int fatorial (int n)
{
    if(n==0) return 1;
    return(n * fatorial(n-1));
}

int expo2(int n)
{
    if(n==0) return 1;
    return(2 * expo2(n-1));
}
//Essas duas são "recursão de cauda": facilmente substituíveis por um while
//Fibonacci é mais complexo:

int fibo(int n)
{
    if (n <= 2) return 1;
    return(fibo(n-1)+fibo(n-2));
}

int maximo (int v[], int n)
{
    int max;
    if (n==1) return(v[0]);
    max = maximo(v, n-1);
    if(max > v[n-1]) return(max);
    return(v[n-1]);
}