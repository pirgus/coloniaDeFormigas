/*
    Grupo 05

Tema: Problema de Roteamento
Método: Colônia de Formigas
Estratégia: o vértice inicial é sempre o primeiro vértice do grafo.

Entrada: arquivos em formato txt contendo o número de vértices que compõe o grafo o a sua devida lista de adjacências , contendo
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
void atualizaMatriz(grafof rot, double** matriz_formigas);
double randouble(int max, int min); 
void formigaAnda(formiga ant, grafof grafo, double** matrizFer);
double probCalculo(int index, int j, grafof grafo);
int escolhaAresta(vector<double> probabilidades);
double formigaAndouQnt(formiga ant, grafof grafo);
void formigaMFeromonio(double** matrizFeromonio, formiga ant, double qtdAndou);

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
    //formigas
    formiga a1, a2, a3;

    //grafo que armazena a rota
    //matriz de adjacência e matriz de feromônios
    grafof rot;

    //controle de iterações
    int count = 0;


    //matriz que armazena feromonios deixados pelas formigas
    double **matrizFormigas;
    srand(time(NULL));

    // quantos vertices?
    scanf("%d", &rot.vert);

    // alocação da matriz de adjacencia
    rot.adj = (int**) malloc(sizeof(int*) * rot.vert);

    for(int i = 0; i < rot.vert; i++)
        rot.adj[i] = (int*) malloc(sizeof(int) * rot.vert);
    // ----------------------------------------------------
    cout << "alocou matriz de adjacencia" << endl;

    // alocação da matriz de feromonios
    rot.ferom = (double**) malloc(sizeof(double*) *rot.vert);
    
    for(int i = 0; i < rot.vert; i++)
        rot.ferom[i] = (double*) malloc(sizeof(double) * rot.vert);
    // -----------------------------------------------------------
    cout << "alocou matriz de feromonio" << endl;

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
    cout << "leu matriz de adjacencia" << endl;

    matrizFormigas = (double**) malloc(sizeof(double*) * rot.vert);
    for(int i = 0; i < rot.vert; i++){
        matrizFormigas[i] = (double*) malloc(sizeof(double) * rot.vert);
    }
    cout << "alocou matrizFormigas" << endl;

    while(count < nIter)
    {
          // preencher com nadaaaa
        for(int i = 0; i < rot.vert; i++){
            for(int j = 0; j < rot.vert; j++){
                matrizFormigas[i][j] = 0.0;
            }
        }

        cout << "***********************" << endl;
        cout << "Iteracao " << count << endl;
        cout << "***********************" << endl;

        // construir soluções possíveis
        formigaAnda(a1, rot, matrizFormigas); // aqui ta dando problema, segmentation fault
        cout << "1a formiga andou" << endl;
        formigaAnda(a2, rot, matrizFormigas);
        cout << "2a formiga andou" << endl;
        formigaAnda(a3, rot, matrizFormigas);
        cout << "3a formiga andou" << endl;

        // atualizar matriz de feromonios
        atualizaMatriz(rot, matrizFormigas);

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

int escolhaAresta(vector<double> probabilidades){

    int vertice{0};
    double prob;

    //roleta
    vector<double> linha;

    // salva o ultimo ponto registrado para somar com a probabilidade atual
    double ultimo_ponto{0.0};

    for(int i = 0; i < probabilidades.size(); i++){
        linha.push_back(probabilidades[i] + ultimo_ponto);
        ultimo_ponto = linha.back();
    }

    prob = randouble(1, 0);


    // acho que aqui mora o problema, ele ja seleciona o primeiro que tenha probabilidade menor ou igual a linha[i]
    for(int i = 0; i < linha.size(); i++){
        if((prob > 0) && (prob <= linha[i])){
            vertice = i;
            break;
        }
    }

    if(vertice != 0)
        return vertice;
    else
        return escolhaAresta(probabilidades);
}

// MAIOR PROBLEMA AQUI ===== FORMIGA NAO PARA DE ESCOLHER UMA ARESTA PARA IR

void formigaAnda(formiga ant, grafof grafo, double** matrizFer){
    cout << "formiga começou a andar" << endl;

    ant.visitados.push_back(pVertice);
    int vAtual = pVertice;

    vector<double> probabilidades;
    
    //cout << "1 - probabildidades.size() no formigaAnda = " << probabilidades.size() << endl;

    while(ant.visitados.back() != ultimoVertice){
        
        double prob = 0;
        //cout << "grafo.vert = " << grafo.vert - 1 << endl;
        for(int i = 0; i < grafo.vert; i++){
            auto it = find(ant.visitados.begin(), ant.visitados.end(), i);
            //se a aresta existe e a formiga não visitou ainda
            if(grafo.adj[vAtual][i] != 0 && (it == ant.visitados.end())){
                prob = probCalculo(vAtual, i, grafo);
                probabilidades.push_back(prob);
            }
            else
                probabilidades.push_back(0);
        }

        // for (double i: probabilidades){
        //     std::cout << i << " " << endl;
        // }

        //---------------------------------------------TÁ DANDO ERRO AQUIIIIIIIIIIIIIIIII----------------------------------------------------
        vAtual = escolhaAresta(probabilidades);
        //cout << "escolheu uma aresta para a formiga ir" << endl;
        //cout << "aresta = " << vAtual << endl;
        // por que ta escolhendo aresta = 0???????????????????
        //-----------------------------------------------------------------------------------------------


        //cout << "vAtual = " << vAtual << endl;
        probabilidades.clear(); // precisa dar clear se nao fica acumulando
        ant.visitados.push_back(vAtual); 
        
    }

    cout << "visitados = " << endl;
    for(int i: ant.visitados){
        cout << i << " - ";
    }
    cout << endl;

    double qtdAndou = 0;

    qtdAndou = formigaAndouQnt(ant, grafo);
    cout << "calculou fator de feromonio deixado pela formiga" << endl;
    formigaMFeromonio(matrizFer, ant, qtdAndou);
    cout << "atualizou matriz de feromonio das formigas" << endl;

}

void formigaMFeromonio(double** matrizFeromonio, formiga ant, double qtdAndou){
    for(int i = 0; i < ant.visitados.size(); i++){
        matrizFeromonio[ant.visitados[i]][ant.visitados[i + 1]] += qtdAndou;
    }
}

double formigaAndouQnt(formiga ant, grafof grafo){
    int distancia = 0;
    for(int i = 0; i < ant.visitados.size() - 1; i++){
        distancia += grafo.adj[ant.visitados[i]][ant.visitados[i + 1]];
    }

    double qtdFeromonio;
    qtdFeromonio = atualizaFer / double(distancia);

    return qtdFeromonio;
}

double probCalculo(int index, int j, grafof grafo){
    double nVisib;
    nVisib = 1.0 / (grafo.adj[index][j]);
    double p = 0;
    double soma = 0;
    for(int i = 0; i < grafo.vert; i++){
        if(grafo.adj[index][i] != 0)
            soma += (grafo.ferom[index][i] * (1.0/(grafo.adj[index][i])));
        else
            soma += 0;
    } //; ==> laço for para calcular o somatorio de todas as probabilidades
    //cout << "somatorio = " << soma << endl;
    p = (grafo.ferom[index][j] * nVisib) / (soma);
    //cout << "probabilidade calculada = " << p << endl;

    return p;
}

void atualizaMatriz(grafof rot, double **matriz_formigas){
    for(int i = 0; i < rot.vert; i++)
    {
        for(int j = 0; j < rot.vert; j++)
        {
            rot.ferom[i][j] = ((1 - diminuiFer) * rot.ferom[i][j]) + matriz_formigas[i][j]; // + SOMATORIO DO FEROMONIO QUE TODAS AS FORMIGAS DEIXARAM NESSA ARESTA
        }
    }
}