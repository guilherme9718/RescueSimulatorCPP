#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "percepcao.h"
using namespace std;

class Percepcao;

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

    static bool cmpNode(const Node* a, const Node* b) {
        return a->custo_total < b->custo_total;
    }
};

class Robo
{
    protected:
    Percepcao ultimaPer;
    vector<vector<int>> mapa;
    vector<vector<float>> sinaisVitais;

    double heuristica_distancia(const Node &no);
    void explorar_fronteira(vector<vector<int>> *mapa, vector<Node*>* fronteira, Node* atual);
    bool NoValido(int i, int j, vector<vector<int>>* mapa);
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

    vector<int> a_estrela(vector<vector<int>>* mapa,  
    int x, int y, int objetivox, int objetivoy);
    vector<int> custo_uniforme(vector<vector<int>>* mapa,  
    int x, int y, int objetivox, int objetivoy);
    };

