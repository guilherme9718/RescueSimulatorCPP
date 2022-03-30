#pragma once
#include "robo.h"
#include <chrono>
#include <thread>
using namespace std;

//Para a ser usado na escolha das vitimas a serem salvas, contem a distancia da base e o indice da matriz de vitimas
typedef pair<float, int> Vitima;

//Para a ser usado na escolha das vitimas a serem salvas, contem a distancia da base e o indice da matriz de vitimas
typedef pair<float, int> Vitima;

class RoboSalv: public Robo
{
    private:
    int carga;
    vector<vector<int>> labirinto;

    //matriz de vitimas, cada linha eh uma vitima, cada coluna e um sinal vital, vitimas[][6] e vitimas[][7] sao as coordenadas
    vector<vector<float>> vitimas;

    //matriz do planejamento, cada posicao eh o codigo de uma acao
    vector<vector<int>> acoes;

    public:

    RoboSalv(int carg, float bat, float temp);
    ~RoboSalv();

    void imprimirDados();
    void recebeMatrizes(vector<vector<int>> lab, vector<vector<float>> vit);
    //planeja o caminho, preenchendo a matriz de acoes
    void planejar();

    //executa as acoes conforme o planejamento da matriz de acoes
    void executar_plano();

    //imprime o labirinto durante a execucao do plano
    void imprime_labirinto(Pos robo_pos);
};