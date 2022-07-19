/*
    Grupo 05

Tema: Problema de Roteamento
Método: Colônia de Formigas
Estratégia: o vértice inicial é sempre o primeiro vértice do grafo.

Entrada: arquivos em formato txt contendo o número de vértices que compõe o grafo o a sua devidalista de adjacências , contendo
o peso das arestas entre cada par de vértices
--> valores iguais a zero indicam a ausência de conexão entre os vértices
--> os grafos são ponderados
--> os grafos são não direcionados
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct grafof
{
    int vert;
    int **adj;
    double **ferom;
} grafof;


int randInt(int max, int min);
formiga andaFormiga(formiga ant);
grafof atualizaMatriz(grafof rot);
double randouble(int max, int min); 

int main()
{
    // inicializar parâmetros
    grafof rot;
    double factF = 0.1;
    int count = 0, nIter = 30;
    double alfa = 1, beta = 1;
    double diminuiFer = 0.01;
    double atualizaFer = 10;

    // quantos vertices?
    scanf("%d", &rot.vert);
    vector<int> a1, a2, a3, a4, a5;

    // alocação da matriz de adjacencia
    rot.adj = (int**) malloc(sizeof(int*) * rot.vert);

    for(int i = 0; i < rot.vert; i++)
        rot.adj[i] = (int*) malloc(sizeof(int) * rot.vert);
    // ----------------------------------------------------

    // alocação da matriz de feromonios
    rot.ferom = (double**) malloc(sizeof(double*) *rot.vert);
    
    for(int i = 0; i < rot.vert; i++)
        rot.ferom[i] = (double*) malloc(sizeof(double) * rot.vert);
    // -----------------------------------------------------------

    // inicializar matriz de feromonios
    for(int i = 0; i < rot.vert; i++)
        for(int j = 0; j < rot.vert; j++)
            rot.ferom[i][j] = factF;
    // ---------------------------------

    // leitura dos pesos de cada aresta na matriz de adjacencia
    for(int i = 0; i < rot.vert; i++)
        for(int j = 0; j < rot.vert; j++)
            scanf("%d", &rot.adj[i][j]);
    // ----------------------------------

    while(count < nIter)
    {
        // construir soluções possíveis
        formigaAnda(a1, rot.adj);
        formigaAnda(a2, rot.adj);
        formigaAnda(a3, rot.adj);
        formigaAnda(a4, rot.adj);
        formigaAnda(a5, rot.adj);

        // atualizar matriz de feromonios
        atualizaMatriz(rot);

        // iterador++
        count++;

    }

    return 0;
}

int randInt(int max, int min)
{
    //srand(time(NULL));
    int r = rand();
    r = (min + r / (RAND_MAX / (max - min + 1) + 1));
    while(r == 0)
        r = (min + rand() / (RAND_MAX / (max - min + 1) + 1));
    //printf("random da funcao int %d \n", r);
    return r;
}

double randouble(int max, int min)
{
    double r = rand();
    r = (r/(RAND_MAX/(max-min)));
    while(r == 0)
        r = (double(rand())/(RAND_MAX/(max-min)));
    return r;
}

