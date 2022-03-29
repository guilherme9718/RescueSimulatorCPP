#pragma once
#include "robo.h"
#include <list>
class Labirinto;

enum Estado
{
        NORMAL=0,
        EXPLORANDO=1,
        VOLTANDO=2
};

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
    vector<vector<float>> vitimas;
    int vitCount;

    int i_explorado;
    int i_voltando;
    Caminho caminho;

    
    int explorado(int mov, Pos &pos);

    public:
    
    RoboVasc(int x, int y, float bat, float temp, Labirinto* amb);
    ~RoboVasc();

    void imprimirDados();
    void imprimirMapa();

    void deliberar();
    bool IndiceSeguroMatriz(int i, int j, int maxI, int maxJ);
    Caminho consegueVoltarBateria(Pos objetivo, bool &consegue);
    void verificarBateria(int acaoEscolhida);
    void Mover(int acao);

    void decidirMovimentoNormal();
    void decidirMovimentoExplorando();
    void decidirMovimentoVoltando();

    Estado estado;
};

