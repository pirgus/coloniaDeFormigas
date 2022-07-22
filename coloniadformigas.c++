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
#include <algorithm>
using namespace std;

typedef struct formiga{
    vector<int> visitados;
} formiga;

typedef struct grafof
{
    int vert;
    int **adj;
    double **ferom;
} grafof;

int randInt(int max, int min);
void atualizaMatriz(grafof rot);
double randouble(int max, int min); 
void formigaAnda(formiga ant, grafof grafo);
double probCalculo(int index, int j, grafof grafo);
int escolhaAresta(vector<double> probabilidades, vector<int> vertices);

//#define factF 0.1
//#define nIter 30
//#define alfa 1
//#define beta 1
//#define diminuiFer 0.01
//#define atualizaFer 10

const double factF = 0.1;
const int nIter = 30;
const int alfa = 1;
const int beta = 1;
const int diminuiFer = 0.01;
const int atualizaFer = 10;
const int pVertice = 0;
const int ultimoVertice = 8;

int main()
{
    // inicializar parâmetros
    formiga a1, a2, a3;
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
        formigaAnda(a1, rot); // criar funcao para fazer a rota da formiga e armazená-la
        formigaAnda(a2, rot);
        formigaAnda(a3, rot);

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

int escolhaAresta(vector<double> probabilidades, vector<int> vertices){

    int vertice{0};
    double prob;

    vector<double> linha{0};
    //linha.clear();

    // --------------------------------------
    // ele tá acumulando os dados na linha e quando dou clear
    // no vetor linha ele fica rodando pra sempre (???????)
    // socorroooooooo
    // acho que arrumei um pouquinho mas tá bem estranho ainda

    double ultimo_ponto{0};
    for(int i = 0; i < probabilidades.size(); i++){
        linha.push_back(probabilidades[i] + ultimo_ponto);
        ultimo_ponto = linha.back();
        printf("linha[%d] = %lf ", i, linha.back());
    }
    printf("\n");
    printf("chegay\n");

    prob = randouble(1, 0);
    printf("probabilidade = %lf\n", prob);

    //possivel problema -> sorteio do 0 
    for(int i = 0; i < linha.size(); i++){
        if(prob <= linha[i]){
            cout << i << endl;
            vertice = i;
            printf("vertice escolhido = %d\n", i);
            break;
        }
    }
    return vertice;
}

void formigaAnda(formiga ant, grafof grafo){
    ant.visitados.push_back(pVertice);
    int vAtual = pVertice;
    vector<double> probabilidades{0};
    probabilidades.clear();

    while(ant.visitados.back() != ultimoVertice){
        double somatorio = 0;
        for(int i = 0; i < grafo.vert; i++){
            if(grafo.adj[vAtual][i] != 0){
                somatorio += grafo.ferom[vAtual][i] * (1.0 / (grafo.adj[vAtual][i]));
            }
            else{
                somatorio += 0;
            }
        }

        double prob = 0;
        for(int i = 0; i < grafo.vert; i++){

            auto it = find(ant.visitados.begin(), ant.visitados.end(), i);

            if(grafo.adj[vAtual][i] != 0 && (it == ant.visitados.end())){
                prob = (grafo.ferom[vAtual][i] * (1.0 / (grafo.adj[vAtual][i]))) / (somatorio);
                probabilidades.push_back(prob);
            }
            else{
                probabilidades.push_back(0);
            }
        }
        //printf("toaqui");


        //---------------------------------------------TÁ DANDO ERRO AQUIIIIIIIIIIIIIIIII----------------------------------------------------
        vAtual = escolhaAresta(probabilidades, ant.visitados);
        //exit(0);
        //-----------------------------------------------------------------------------------------------
        ant.visitados.push_back(vAtual); 
        
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
        }
    }
}
