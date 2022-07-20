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
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

typedef struct formiga{
    vector<int> visitados;
};

typedef struct grafof
{
    int vert;
    int **adj;
    double **ferom;
} grafof;

int randInt(int max, int min);
void atualizaMatriz(grafof rot);
double randouble(int max, int min); 
void formigaAnda(formiga ant, grafof grafo, int vert);
double probCalculo(int index, int j, grafof grafo);

#define factF 0.1
#define nIter 30
#define alfa 1
#define beta 1
#define diminuiFer 0.01
#define atualizaFer 10

int main()
{
    // inicializar parâmetros
    formiga a1;
    grafof rot;
    int count = 0;
    srand(time(NULL));

    // quantos vertices?
    scanf("%d", &rot.vert);

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
        formigaAnda(a1, rot, rot.vert); // criar funcao para fazer a rota da formiga e armazená-la

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

void formigaAnda(formiga ant, grafof grafo, int vert){
    ant.visitados.push_back(0);
    int index = 0;
    for(int j = 0; j < vert; j++)
    {
        double probab;
        probab = probCalculo(index, j, grafo);
        double random;
        random = randouble(1, 0);

        if(random <= probab)
        {
            ant.visitados.push_back(j);
            break;
        }
    }

    bool nTerminou = true;

    while(nTerminou)
    {
        index = ant.visitados.back();
        for(int j = 0; j < vert; j++)
        {
            double probab;
            probab = probCalculo(index, j, grafo);
            double random;
            random = randouble(1, 0);

            if(random <= probab)
            {
                // falta verificar se o vértice ja nao foi visitado !!!!!!!!!!!!!!!
                ant.visitados.push_back(j);
                break;
            }
        }

        if(ant.visitados.size() == grafo.vert)
            nTerminou = false;
    }

}

double probCalculo(int index, int j, grafof grafo){
    double nVisib;
    nVisib = 1.0 / grafo.adj[index][j];
    double p;
    double soma = 0;
    for(int i = 0; i < grafo.vert; i++){
        soma += (grafo.ferom[index][i] * (1.0/(grafo.adj[index][i])));
    } //; ==> laço for para calcular o somatorio de todas as probabilidades
    p = (grafo.ferom[index][j] * nVisib) / (soma);

    return p;
}

void atualizaMatriz(grafof rot){
    for(int i = 0; i < rot.vert; i++)
    {
        for(int j = 0; j < rot.vert; j++)
        {
            rot.ferom[i][j] = (1 - diminuiFer) * rot.ferom[i][j]; // + SOMATORIO DO FEROMONIO QUE TODAS AS FORMIGAS DEIXARAM NESSA ARESTA
                                                                  // PRECISA FAZER O CALCULO DO FEROMONIO
                                                                  // DEIXADO POR TODAS AS FORMIGAS NA
                                                                  // ARESTA, AINDA NAO APLIQUEI
        }
    }
}
