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
    vector<vector<int>> mapa;
    vector<vector<float>> sinaisVitais;
    public:
    
    Robo(float bat, float temp);
    ~Robo();

    int posx;
    int posy;
    float bateria;
    float tempo;

    bool completou;

    void imprimirMapa(); 
    bool IndiceSeguroMatriz(int i, int j, int maxI, int maxJ);
    bool NoValido(int i, int j, vector<vector<int>>* mapa);
    vector<int> a_estrela(vector<vector<int>>* mapa,  
    int x, int y, int objetivox, int objetivoy, double(*heuristica)Node);
};

class Node {
    public:
    int posx;
    int posy;
    Node* ant;
    double custo_acum;
    double custo_total;
    double heuri;
    Node(int x, int y, Node* anterior, double acum=1.5, double total=1.5) {
        posx = x;
        posy = y;
        anterior = ant;
        custo_acum = acum;
        custo_total = total;
    }

    bool operator()(const Node& a,
                    const Node& b)
    {
        // Compare on basis of roll number
        if (a.custo_total < b.custo_total) {
            return true;
        }
        return false;
    }
};