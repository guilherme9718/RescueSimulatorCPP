#pragma once
#include <vector>
#include <iostream>
#include "percepcao.h"
using namespace std;

class Percepcao;

class Robo
{
    protected:
    Percepcao ultimaPer;

    public:
    
    Robo(float bat, float temp);
    ~Robo();

    int posx;
    int posy;
    float bateria;
    float tempo;

    bool completou;
    
};