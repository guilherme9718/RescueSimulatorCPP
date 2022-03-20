#include "roboVasc.h"

RoboVasc::RoboVasc(int x, int y, float bat, float temp):
Robo(bat, temp)
{
    for(int i = 0; i < x; i++)
    {
        vector<int> aux;
        for(int j = 0; j < y; j++)
            aux.push_back(-1);
        labirinto.push_back(aux);
    }
}

RoboVasc::~RoboVasc()
{
    int x = labirinto[0].size();
    for(int i = 0; i < x; i++)
        labirinto[i].clear();
    labirinto.clear();
}

void RoboVasc::imprimirDados()
{
    cout << labirinto.size() << " X " << labirinto[0].size() << " " << bateria << " " << tempo << endl;
}

void RoboVasc::deliberar()
{
    
}