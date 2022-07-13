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

typedef struct grafo
{
    int vert;
    int **adj;
} grafo;

int main()
{
    grafo rot;

    scanf("%d", &rot.vert);
    rot.adj = (int**) malloc(sizeof(int*) * rot.vert);

    for(int i = 0; i < rot.vert; i++)
        rot.adj[i] = (int*) malloc(sizeof(int) * rot.vert);

    for(int i = 0; i < rot.vert; i++)
        for(int j = 0; j < rot.vert; j++)
            scanf("%d", &rot.adj[i][j]);

    return 0;
}