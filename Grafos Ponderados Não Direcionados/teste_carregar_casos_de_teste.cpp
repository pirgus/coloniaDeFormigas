#include <iostream>
#include <fstream> 

int** alocarMatrizContigua (int m, int n){
    
    int **M;
    M = (int**)malloc(sizeof(int*) * m);
    M[0] = (int*)malloc(sizeof(int) * m * n);
    for(int i = 1; i < m; i++){
        M[i] = M[0] + i * n;
    }
    
    return M;
}

int main(){

    int nos, x;
    int **matriz_adjacencia; 

    std::cin >> nos; 
    matriz_adjacencia = alocarMatrizContigua(nos, nos);

    for (int i{0}; i < nos; i++){
        for (int j{0}; j < nos; j++){
            std::cin >> matriz_adjacencia[i][j];
            std::cout << matriz_adjacencia[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}