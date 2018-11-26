void hanoi(int n, char origem, char aux, char destino)
{
    //n >= 0
    if (n>0)
    {
        hanoi(n-1, origem, destino, aux);
        printf("Mova o disco %d de %c pra %c\n", n, origem, destino);
        hanoi(n-1, aux, origem, destino);
    }
    else{
        a = 1
        // Do nothing
    }
}