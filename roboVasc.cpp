#include "roboVasc.h"
#include "labirinto.h"

RoboVasc::RoboVasc(int x, int y, float bat, float temp, Labirinto *amb) : Robo(bat, temp)
{
    ultimaPer.posx = x;
    ultimaPer.posy = y;
    ultimaPer.sucesso = false;

    for (int i = 0; i < 8; i++)
        acoes.push_back(i);
    ambiente = amb;
    for (int i = 0; i < x; i++)
    {
        vector<int> aux;
        for (int j = 0; j < y; j++)
            aux.push_back(-1);
        mapa.push_back(aux);
    }
}

RoboVasc::~RoboVasc()
{
    int x = mapa[0].size();
    for (int i = 0; i < x; i++)
        mapa[i].clear();
    mapa.clear();
}

void RoboVasc::imprimirDados()
{
    cout << "Robo Vasculhador dados: "
         << "bateria = " << bateria
         << "; tempo = " << tempo
         << "; tamanho = " << mapa.size() << " X " << mapa[0].size() << endl;
}

void RoboVasc::deliberar()
{
    if (ultimaPer.sucesso)
    {
        posx = ultimaPer.posx;
        posy = ultimaPer.posy;
        if (ultimaPer.objeto > 1)
        {
            // TODO - ler sinais vitais
            // auto sinais = ambiente->LerSinaisVitais(this);
        }
    }
    else
    {
        int aux = acoes.front();
        acoes.remove(acoes.front());
        acoes.push_back(aux);
    }
    decidirMovimento();
}

void RoboVasc::decidirMovimento()
{
    switch (acoes.front())
    {
    case 1:
        ultimaPer = ambiente->moverNorte(this);
        break;
    case 2:
        ultimaPer = ambiente->moverSul(this);
        break;
    case 3:
        ultimaPer = ambiente->moverLeste(this);
        break;
    case 4:
        ultimaPer = ambiente->moverOeste(this);
        break;
    case 5:
        ultimaPer = ambiente->moverNordeste(this);
        break;
    case 6:
        ultimaPer = ambiente->moverNoroeste(this);
        break;
    case 7:
        ultimaPer = ambiente->moverSudeste(this);
        break;
    case 8:
        ultimaPer = ambiente->moverSudoeste(this);
        break;
    default:
        break;
    }
}
