#include "roboSalv.h"

RoboSalv::RoboSalv(int carg, float bat, float temp):
Robo(bat, temp)
{
    carga = carg;
}

RoboSalv::~RoboSalv()
{
    
}

void RoboSalv::imprimirDados()
{
    cout << "Robo Salvador dados: " << "bateria = " << bateria 
    << "; tempo = " << tempo << 
    "; carga = " << carga << endl;
}

void RoboSalv::recebeMatrizes(vector<vector<int>> lab, vector<vector<float>> vit)
{
    labirinto = lab;
    vitimas = vit;
}

int RoboSalv::busca_menor_distancia(Pos p)
{
    int indice1 = 0;
    float menor = calculaDist(make_pair(p.first,p.second), make_pair(vitimas[0][6], vitimas[0][7]));
    for(int i = 1; i < vitimas.size(); i++)
    {
        float aux =  calculaDist(make_pair(0,0), make_pair(vitimas[i][6], vitimas[i][7]));
        if(aux < menor)
        {
            indice1 = i;
            menor = aux;
        }
    }
}

void RoboSalv::planejar()
{
    priority_queue<Vitima, vector<Vitima>, greater<Vitima>> heap_vitimas; //heap para as vitimas
    
    //Preenche o heap com as vitimas da matriz de vitimas
    for(int i = 0; i < vitimas.size(); i++)
    {
        float d = calculaDist(make_pair(0,0), make_pair(vitimas[i][6], vitimas[i][7]));
        heap_vitimas.push(make_pair(d,i));
    }

    //matriz do planejamento, cada posicao eh o codigo de uma acao
    vector<vector<int>> acoes;
    //loop principal
    while(tempo > 0)
    {
        //tenta encontrar um caminho que socorre o maior numero de vitimas
        Pos atual = make_pair(0,0); //marca a posicao da base como posicao atual
        float t_acumulado = 0;
        for(int i = 0; i < carga; i++)
        {
            //pega a vitima mais perto da base
            Vitima v = heap_vitimas.top();
            //calcula os caminhos, com o a*, ida do atual ate a vitima selecionada e volta da vitima selecionada ate a base
            Caminho ida = a_estrela(atual, make_pair(vitimas[v.second][6], vitimas[v.second][7]), labirinto);
            Caminho volta = a_estrela(make_pair(0,0), make_pair(vitimas[v.second][6], vitimas[v.second][7]), labirinto);

            //caso o tempo acumulado + ir ate a vitima e salva-la + voltar seja menor que o tempo restante
            if(t_acumulado + ida.first + volta.first + 0.5 < tempo)
                if(t_acumulado + ida.first + volta.first + 0.5 < bateria) //o mesmo para a bateria
                {
                    t_acumulado += ida.first + 0.5;
                    //TODO - retirar a volta da matriz de acoes
                    //TODO - adiciona ida na matriz de acoes + salvar vitima
                    //TODO - adicionar a volta na matriz de acoes + carregar carga
                    heap_vitimas.pop();
                    atual = make_pair(vitimas[v.second][6], vitimas[v.second][7]);
                    continue;
                }
            
            break;
        }
        tempo -= t_acumulado;
        bateria -= t_acumulado;
    }
    

}