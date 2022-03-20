#pragma once
#include "robo.h"

class RoboVasc: public Robo
{
    private:
    vector<vector<int>> labirinto;

    public:

    RoboVasc(int x, int y, float bat, float temp);
    ~RoboVasc();

    void imprimirDados();
    void deliberar();
};