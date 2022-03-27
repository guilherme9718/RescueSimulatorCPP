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
    int x, int y, int objetivox, int objetivoy) {
    
    vector<Node*> fronteira;
    Node* atual = new Node(x, y, nullptr, 0);
    atual->custo_acum = heuristica_distancia(*atual);
    Node* aux;
    for(int i=-1; i < 2; i++) {
        for(int j=-1; j < 2; j++) {
            if(NoValido(x+i, y+j, mapa)) {
                double custo;
                if(i != 0 && j != 0)
                    custo = 1.5;
                else
                    custo = 1;
                
                aux = new Node(x+i, y+j, atual, custo, custo);
                aux->heuri = heuristica_distancia(*aux);
                aux->custo_total = aux->custo_acum + aux->heuri;
                fronteira.push_back(aux);
            }
        }
    }

    while (fronteira.size() > 0)
    {
        
    }
    
    cout << "antes" << endl;
    for(int i=0; i < fronteira.size(); i++) {
        cout << "x = " << fronteira[i]->posx << "y = " << fronteira[i]->posy << endl;;
    }

    make_heap(fronteira.begin(), fronteira.end(), Node::cmpNode);
    cout << "heap" << endl;
    for(int i=0; i < fronteira.size(); i++) {
        cout << "x = " << fronteira[i]->posx << "y = " << fronteira[i]->posy << endl;;
    }
    sort_heap(fronteira.begin(), fronteira.end(), Node::cmpNode);
    cout << "ordenado" << endl;
    for(int i=0; i < fronteira.size(); i++) {
        cout << "x = " << fronteira[i]->posx << "y = " << fronteira[i]->posy << endl;;
    }
}

void Robo::explorar_fronteira(vector<vector<int>> *mapa, vector<Node*>* fronteira, Node* atual) {
    Node* aux;
    for(int i=-1; i < 2; i++) {
        for(int j=-1; j < 2; j++) {
            if(NoValido(atual->posx+i, atual->posy+j, mapa)) {
                double custo;
                if(i != 0 && j != 0)
                    custo = 1.5;
                else
                    custo = 1;
                aux = new Node(atual->posx+i, atual->posy+j, atual, custo+atual->custo_acum);
                aux->heuri = heuristica_distancia(*aux);
                aux->custo_total = aux->custo_acum + aux->heuri;
                
                fronteira->push_back(aux);
                push_heap(fronteira->begin(), fronteira->end(), Node::cmpNode);
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


vector<int> Robo::custo_uniforme(vector<vector<int>>* mapa,  
    int x, int y, int objetivox, int objetivoy) {
        return a_estrela(mapa, x, y, objetivox, objetivoy);
}

double Robo::heuristica_distancia(const Node &no) {
    return 0.0;
}