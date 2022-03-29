#pragma once
#include "robo.h"

//Para a ser usado na escolha das vitimas a serem salvas, contem a distancia da base e o indice da matriz de vitimas
typedef pair<float, int> Vitima;

class RoboSalv: public Robo
{
    private:
    int carga;
    vector<vector<int>> labirinto;

    //matriz de vitimas, cada linha eh uma vitima, cada coluna e um sinal vital, vitimas[][6] e vitimas[][7] sao as coordenadas
    vector<vector<float>> vitimas;

    //TODO - colocar ponteiros para mapa e para matriz sinais vitais 

    public:

    RoboSalv(int carg, float bat, float temp);
    ~RoboSalv();

    void imprimirDados();
    void recebeMatrizes(vector<vector<int>> lab, vector<vector<float>> vit);
    //Preenche o heap com as vitimas da matriz de vitimas
    void preenche_heap(priority_queue<Vitima, vector<Vitima>, greater<Vitima>> &heap_vitimas);
    void planejar();
    
    //busca a vitima com menor distancia do ponto p, retorna seu indice da matriz de vitimas
    int busca_menor_distancia(Pos p);
};