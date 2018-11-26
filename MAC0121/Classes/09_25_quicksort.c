void Quicksort (float v*, int ini, int fim)
{
    int pivo;
    if (fim - ini >= 2)
    {
        pivo = separa(v, ini, fim);
        Quicksort(v, ini, pivo);
        Quicksort(v,pivo+1,fim);
    }
}

int separa(flood v[], int ini, int fim)
{
    //Closing gap. Hoave(?)/Hoare 60
    //Essa versão tem muitos casos ruins
    int p = ini, q = fim - 1;
    float pivo = v[ini];
    while (p < q)
    {
        while(v[q]>pivo) q = q-1;
        if (q < p) troca(v,p,q);
        while (p < q && v[p]<=pivo) p++;
        if (p<q) troca(v,p,q);
    }
    return (p); //indíce atual
}

//Separa: é linear. Cada elemento é comparado no máximo duas vezes. Comparações: O(fim-ini). O número de trocas é menor
//Quicksort: No melhor caso é O(n log n). No pior caso é O(n^2)

/*
Versão do Sedgewick pro separa:
O pivô é o último elemento. Tem um índice j que vai andando pelos outros elementos do vetor, e tudo que está antes do j
deve ser menor que o pivô. Para cada elemento acessado no índice j, se ele for menor ou igual ao pivô, troca ele de lugar
com o primeiro dos elementos que não é maior (i.e. aquilo que está em j)

Tudo que está antes de i é menor ou igual ao pivô. É menor ou igual? Ando com o i e troco. Se não, anda com o j. Tudo que está
depois do j deve ser maior

O separa vai achar a posição exata de um único elemento (o pivô) - eu acho
*/

int separadois (float v[], int ini, int fim)
//Versão Sedgewick. Orientando do Donald Knuth - "The art of computer coding"
{
    int i = ini-1, j; //O i é o último dos que são menores; no começo nenhum está ordenado
    float pivo = v[fim-1];
    for (j=ini; j<fim; j++)
    {
        if (v[j]<=pivo) //única comparação desse algoritmo
        {
            i = i +1;
            troca(v,i,j);
        }
    }
    return i;
}

/*
Análise de caso médio

Seja C(n) o número total de comparações (*) executadas para ordenar um vetor com n elementos.
Na média, considerando que a probabilidade do separa devolver qualquer índice é a mesma.
C(n) = 0, se n = 1 ou 0 (ele só compara se tem pelo menos 2 elementos)
Para n >=2:
C(n) = prob(separa devolver o primeiro elemento)*(C(0) + C(n-1)) + prob(devolver o segundo elemento)*(C(1) + C(n-2))  + prob(devolver o terceiro elemento)*(C(2) + C(n-3))
+ ... + prob(devolver o último)*(C(n-1) + C(0))

Total:

C(n) = n (número de comparações feitas pelo separa) + 2/n somatória de 0 a n-1 de C(i)

Ele desenvolveu essa soma, e deu que é menor ou igual a 
2/1 + 2/n-2 + 2/n-1 + 2/n + 2/ n + 1 = 2 * somatória de 1 a n +1 de 1/i    -> Essa soma não é convergente, mas é harmônica
Os valores somados vão ficar embaixo de uma curva, então poderemos dizer que isso tudo é menor ou igual
à integral de 1 a n+1 1/x dx = [ln x] ^ n+1
= ln (n + 1)

Então na média
C(n) <= (n+1) ln (n+1)
*/