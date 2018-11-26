/* Representação de polinômios usando lista ligada
Exemplo: p(x) = 35 - 7x**19+3.14x**123-0.3x**1279

Ideia ruim: usar um vetor colocando no índice i o coeficiente do termo de grau i. Precisa saber o grau máximo e criar um vetor com esse tamanho

Esta representação tem como desvantagem o desperdício de espaço caso o polinômio seja esparso, ou seja, ele tenha poucos coeficentes não nulos

Usai então a lista ligada, ó ímpios

Cada célula da lista ligada guarda o grau e o coeficiente não-nulo do termo. Vamos considerar que os termos estão ordenados em ordem crescente de grau:
p = [[3.5, 0]->[7,19]->[3.14,123]->[0.3,1279]] 
*/

typedef struct cel {
    float coef; //coeficiente
    int expo; //expoente
    struct cel * prox;
} celula;

typedef celula * polinomio;



float avalia(polinomio p, float x)
{
    //Devolve p(x)

    /*
    int i = 0;
    float parcial = 0;
    while (polinomio[i] != NULL)
    {
        parcial = polinomio[i][0]*x**polinomio[i][1]; 
    }
    */

   float resultado = 0.0;
   polinomio ap = p;
   while (ap != NULL)
   {
       resultado += ap->coef*eleva(x, ap->expo);
       ap = ap->prox;
   }
   return(resultado);
}

/*
Se eu tenho um polinômio de grau máximo k, m termos não nulos, o número de somas é m e o tempo p/ todos os "elevas" é k

Na representação por vetor é proporcional ao grau máximo; aqui, economiza espaço e é basicamente equivalente
*/

polinomio soma(polinomio p, polinomio q)
//MINHA TENTATIVA
{
    polinomio somado;
    polinomio ap = p;
    polinomio aq = q;
    while(ap!=NULL && aq!=NULL)
    {
        if (ap->expo == aq->expo)
        {
            somado->coef = ap->coef + aq->coef;
            somado->expo = ap->expo
            ap = ap-> prox;
            aq = aq->prox; 
        } 
        else if (ap->expo > aq->expo)
        {
            somado->coef = ap->coef;
            somado->expo = ap->expo;
        }
        else
        {
            somado->coef = aq->coef;
            somado->expo = aq->expo;
        }
        somado = somado->prox;
    }
}

polinomio criacelula(float c, int e)
{
    polinomio novo = malloc(sizeof(celula));
    novo->coef = c;
    novo->expo = e;
    novo->prox = NULL;
    return novo;
}

polinomio somaOficial(polinomio p, polinomio q)
//Nesse caso é bem mais eficiente que por vetor, que seria proporcional ao grau máximo
{
    polinomio soma, ult, ap=p, aq=q;
    while(ap!=NULL && aq!=NULL)
    {
        if(ap->expo<aq->expo)
        {
            novo = criacelula(ap->coef,ap->expo);
            novo->coef = ap->coef;
            novo->expo = ap->expo;
            ap = ap->prox;
        }
        else if(aq->expo<ap->expo)
        {
            novo = criacelula(aq->coef,aq->expo);
            aq = aq->prox;
        }
        else
        {
            if(ap->coef+aq->coef!=0.0) //Não pode fazer isso num código "de verdade", para o computador 1 - 0.9999... é diferente de zero
                {
                    novo = criacelula(ap->coef+aq->coef,ap->expo);
                }
            ap = ap->prox;
            aq = aq->prox;
        }
        if (novo!=NULL)
        {
            if (soma==NULL) soma = ult = novo;
            else {
                ult->prox=novo;
                ult = novo;
            }
        }
        }
    }

    while(ap!=NULL)
    {
        novo = criacelula(ap->coef,ap->expo);
        ap = ap->prox;
        if (soma==NULL) soma = ult = novo; //Poderia evitar isso usando uma "cabeça de lista" - assim a lista nunca é NULL
        else{
            ult->prox=novo;
            ult=novo;
        }
    }
    while(aq!=NULL)
    {
        novo = criacelula(aq->coef,aq->expo);
        aq = aq->prox;
        if (soma==NULL) soma = ult = novo;
        else{
            ult->prox=novo;
            ult=novo;
        }
    }
    return soma;
}

//Runtime: proporcional ao número de coeficentes não nulos