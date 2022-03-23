#pragma once
#include "robo.h"
#include <list>
class Labirinto;

class RoboVasc: public Robo
{
    //Lista de ações
    //1 - Norte
    //2 - Sul
    //3 - Leste
    //4 - Oeste
    //5 - Nordeste
    //6 - Noroeste
    //7 - Sudeste
    //8 - Sudoeste

    private:
    Labirinto* ambiente;
    list<int> acoes;
    Percepcao ultimaPer;

    vector<vector<int>> mapa;
    vector<vector<float>> sinaisVitais;
    int vitCount;

    void decidirMovimento();
    int explorado(int mov);

    public:
    
    RoboVasc(int x, int y, float bat, float temp, Labirinto* amb);
    ~RoboVasc();

    void imprimirDados();
    void imprimirMapa();

    void deliberar();
    bool IndiceSeguroMatriz(int i, int j, int maxI, int maxJ);
    
};