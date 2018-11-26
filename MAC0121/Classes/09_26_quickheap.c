void quicksortAleatorizado(float v[], int ini, int fim)
{
    int pivo;
    if (fim - ini > 1)
    {
        pivo = separaAleatorizado(v,ini, fim);
        quicksortAleatorizado(v, ini, pivo);
        quicksortAleatorizado(v, pivo+1, fim);
    }
}

//Complexidade eperada O(n log n)
//Prob. de ocorrer o pior caso é praticamente nula: 2^n/n!

//Heapsort (Williams, Floyd, 1960)
//Um max min heap binário é estrutura hierárquica (árvore) com as seguintes propriedades:
//É completo até o penúltimo nível
//Os elementos do último nível estão o mais à esquerda possível
//Cada elemento é maior que seus filhos
//Pode representar usando um vetor: 
//os filhos do elemento da posição i estão em 2i +1 e 2i + 2
//o pai do elemento na posição i está em (i-1)/2

//Suponha que existe uma função que pega um vetor e transforma num heap
void heapsort(float v[], int n)
{
    heapfica(v, n);
    for (i=n-1; i>0; i--)
    {
        troca(v, 0, i);
        heapfica(v, i);
    }
}

void rebaixa(float v[], int n, int i) //n tem que ser o único errado, os outros já estão na posição correta

/*
{
    //minha tentativa (incompleto)
    int temp;
    if (v[2i+1] > v[2i+2])
    {
        temp = v[2i+1];
        v[2i+1] = n;
    }
    else
    {
        temp = v[2i+2];
        v[2i+2] = n;
    }
    v[i] = temp;
}
*/

{
    //tempo de execução: log n. Ao rodar n vezes, terá complexidade total n log n 
    int pai, filho;
    pai = 1; filho = 2*i+1;
    while(filho<n)
    {
        if (filho+1<n && v[fiho+1]>v[filho]) filho++;
        if (v[filho]<v[pai]) break;
        else
        {
            troca(v,pai,filho);
            pai = filho;
            filho = 2*pai+1;
        }
    }
}

//obs: um heap com n (>=1) elementos tem floor(log n)+1 níveis

void heapfica(float v[], int n)
{
    int i;
    for(i=(n-1)/2; i>=0; i--)
    {
        rebaixa(v,n,i);
    }

}
//Numa primeira análise, executamos n/2 vezes o rebaixa, portanto O(n log n)
//Mas n/2 são folhas, e pra eles não vai rodar nada
//Pros pais de primeiro nível, em número de n/4, só vai executar uma vez o rebaixa
//Pros n/8 pais de segundo nível vai executar duas vezes; e assim por diante, até a raiz, que tem o maior número de execuções porém é única
//Se fizer a soma de todos os níveis, teremos uma soma convergente e portanto o tempo total de execução é <= n (tempo linear)

void heapsortAtualizado(float v[], int n)
{
    heapfica(v, n);
    for (i=n-1; i>0; i--)
    {
        troca(v, 0, i);
        rebaixa(v, i, 0);
    }
}


