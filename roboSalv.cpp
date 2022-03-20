#include "roboSalv.h"

RoboSalv::RoboSalv(int carg, float bat, float temp):
Robo(bat, temp)
{
    carga = carg;
    labirinto = nullptr;
}

RoboSalv::~RoboSalv()
{
    
}

void RoboSalv::imprimirDados()
{
    cout << bateria << " " << tempo << " " << carga << endl;
}