#include "robo.h"

Robo::Robo(float bat, float temp)
{
    posx = posy = 0;
    bateria = bateria_i = bat;
    tempo = temp;
    completou = false;
}

Robo::~Robo()
{
}