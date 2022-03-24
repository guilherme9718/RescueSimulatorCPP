#include "robo.h"

Robo::Robo(float bat, float temp)
{
    posx = posy = 0;
    bateria = bat;
    tempo = temp;
    completou = false;
}

Robo::~Robo()
{
}

vector<int> Robo::a_estrela(vector<vector<int>>* mapa,  
    int x, int y, int objetivox, int objetivoy, double(*heuristica)Node) {

    vector<Node> fronteira;
    Node* aux;
    for(int i=-1; i < 2; i++) {
        for(int j=-1; j < 2; j++) {

            if(NoValido(x+i, y+j, mapa)) {
                double custo;
                if(i != 0 && j != 0)
                    custo = 1.5;
                else
                    custo = 1;
                aux = new Node(x+i, y+j, nullptr, custo, custo);
                aux->heuri = heuristica(*aux);
                aux->custo_total = aux->custo_acum + aux->heuri;
                fronteira.push_back(*aux);
            }
        }
    }

}

bool Robo::IndiceSeguroMatriz(int i, int j, int maxI, int maxJ)
{
    if (i >= 0 && i < maxI && j >= 0 && j < maxJ)
    {
        return true;
    }
    return false;
}

bool Robo::NoValido(int i, int j, vector<vector<int>>* mapa) {
    if(IndiceSeguroMatriz(i, j, mapa->size(), mapa->at(i).size())) {
                if(i != 0 || j != 0) {
                    if(mapa->at(i).at(j) > 0) {
                        return true;
                    }
                }
            }
    return false;
}