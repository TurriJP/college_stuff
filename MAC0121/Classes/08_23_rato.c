int caminho (int **lab, int m, int n, posicaoR, posicaoQ)
{
    Pilha P = CriaPilha(m*n);
    posicaoA = posicaoR;
    int passos = 0, temsol = 1, dir = 0, ok;
    while ((atual.linha != queijo.linha || atual.col != queijo.col) && temsol)
    {
        ok = 0;
        while (dir <= 4 && ok == 0)
        {
            if (PodeAndar(lab,m,n,atual,dir))
            {
                ok = 1
            }
            else
            {
                dir++;
            }
        }
        if (ok == 1)
        {
            passos++;
            lab[atual.linha][atual.col] = passos;
            atual = anda(atual, dir);
            Empilha(P,dir); dir = 0;
        }
        else
        {
            /*backtrack*/
            if (PilhaVazia(P))
            {
                temsol = 0;
            }
            else
            {
                dir = TopoDaPilha(P);
                Desempilha(P);
                passos--;
                atual = anda(atual, (dir+2)%4);
                dir++;
            }
        }
    }
}

int PodeAndar (int **lab, int m, int n, posicao p, int d)
{
    /*Ele apagou cazzo!! Era algo com um switch */
}



/* FILA */

typedef TipoDaFila string;
typedef struct {
    TipoDaFila *v;
    int max;
    int inicio;
    int fim;
} fila;
typedef fila * Fila;

Fila CriaFila(int tam)
{
    Fila F = malloc(sizeof(fila));
    *F.inicio = *F.fim = 0;
    *F.max = tam; //escrito na lousa como F seta max
    *F.v = malloc(tam*sizeof(TopoDaFilaa));
    return(F);
}

void insere (Fila F, TipoDaFila x)
{
    if((*F.fim + 1) % *F.max == *F.inicio)
    {
        resize(F);
    }
    *F.v[*F.fim] = x;
    *F.fim = (*F.fim + 1) % *F.max;
}

int FilaVazia (Fila F)
{
    return(*F.inicio == *F.fim);
}

void remove(Fila F)
{
    if(FilaVazia(F))
    {
        printf("Erro!");
    }
    else {
        *F.inicio = (*F.inicio + 1) % *F.max;
    }
    TipoDaFila PrimeiroDaFila(Fila F)
    {
        if(FilaVazia(F))
        {
            printf("Erro!")
            return(???)
            // return(*F.v[*F.inicio])
        }
    }
}