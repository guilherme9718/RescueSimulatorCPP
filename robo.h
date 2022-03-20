#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Robo
{
    protected:

    int posx;
    int posy;
    float bateria;
    float tempo;

    public:
    
    Robo(float bat, float temp);
    ~Robo();
    
};