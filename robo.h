#pragma once
#include <vector>
#include <iostream>
#include "percepcao.h"
#include "a_estrela.h"
using namespace std;

class Percepcao;

class Robo
{
    protected:
    public:
    
    Robo(float bat, float temp);
    ~Robo();

    int posx;
    int posy;
    float bateria;
    float tempo;

    bool completou;

};