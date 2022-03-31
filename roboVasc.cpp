#include "roboVasc.h"
#include "labirinto.h"

RoboVasc::RoboVasc(int maxLin, int maxCol, float bat, float temp, Labirinto *amb) : Robo(bat, temp)
{
    ultimaPer.posx = 0;
    ultimaPer.posy = 0;
    ultimaPer.sucesso = false;
    vitCount = 0;
    estado = NORMAL;
    i_explorado = 0;
    i_voltando = 0;

    for (int i = 1; i <= 8; i++)
        acoes.push_back(i);
    ambiente = amb;
    for (int i = 0; i < maxLin; i++)
    {
        vector<int> *aux = new vector<int>;
        for (int j = 0; j < maxCol; j++)
            aux->push_back(-1);
        mapa.push_back(*aux);
    }
    mapa[0][0] = 1;
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
        if (mapa[posx][posy] < 2)
            mapa[posx][posy] = ultimaPer.objeto;
        if (ultimaPer.objeto > 1 && mapa[posx][posy] != -1)
        {
            mapa[posx][posy] = vitCount + 2;
            vitimas.push_back(ambiente->LerSinaisVitais(this, ultimaPer.objeto - 2));
            vitimas[vitCount].push_back(posx);
            vitimas[vitCount].push_back(posy);
            vitCount++;
        }
    }
    else
    {
        if ((ultimaPer.posx >= 0 && ultimaPer.posx < mapa.size()) &&
            (ultimaPer.posy >= 0 && ultimaPer.posy < mapa[ultimaPer.posx].size()))
            if (mapa[ultimaPer.posx][ultimaPer.posy] == -1)
            {
                mapa[ultimaPer.posx][ultimaPer.posy] = 0;
            }
        int aux = acoes.front();
        acoes.remove(acoes.front());
        acoes.push_back(aux);
    }
    switch(estado) {
        case NORMAL:
            decidirMovimentoNormal();
            break;
        case EXPLORANDO:
            decidirMovimentoExplorando();
            break;
        case VOLTANDO:
            decidirMovimentoVoltando();
            break;
    }
}

void RoboVasc::decidirMovimentoNormal()
{
    int acaoEscolhida = 0;
    list<int>::iterator it;
    Pos aux(0,0);
    for (it = acoes.begin(); it != acoes.end(); ++it)
    {
        if (explorado(*it, aux) == -1)
        {
            acaoEscolhida = *it;
            break;
        }
    }

    if (acaoEscolhida == 0)
    {
        estado = EXPLORANDO;
        
        Pos aux = procurarObjetivoMaisProximo(-1, posx, posy, &mapa);
        if(aux.first == -1 || aux.second == -1) {
            estado = VOLTANDO;
            caminho = a_estrela(Pos(posx, posy), Pos(0, 0), mapa);
            i_voltando = 0;
            decidirMovimentoVoltando();
            return;
        }

        caminho = a_estrela(Pos(posx, posy), aux, mapa);
        if(caminho.first == -1) {
            estado = VOLTANDO;
            caminho = a_estrela(Pos(posx, posy), Pos(0, 0), mapa);
            i_voltando = 0;
            decidirMovimentoVoltando();
            return;
        }
        i_explorado = 0;
        decidirMovimentoExplorando();
        return;
    }
    verificarBateria(acaoEscolhida);
    Mover(acaoEscolhida);
}

void RoboVasc::decidirMovimentoExplorando() {
    if(i_explorado >= caminho.second.size()) {
        estado = NORMAL;
        decidirMovimentoNormal();
        return;
    }
    verificarBateria(caminho.second[i_explorado]);
    Mover(caminho.second[i_explorado]);
    i_explorado++;
}

void RoboVasc::decidirMovimentoVoltando() {
    if(i_voltando >= caminho.second.size()) {
        completou = true;
        return;
    }
    Mover(caminho.second[i_voltando]);
    i_voltando++;
}

int RoboVasc::explorado(int mov, Pos &pos)
{
    switch (mov)
    {
    case 1:
        pos = Pos(-1, 0);
        if (IndiceSeguroMatriz(posx - 1, posy, mapa.size(), mapa[0].size()))
            return mapa[posx - 1][posy];
        break;
    case 2:
        pos = Pos(1, 0);
        if (IndiceSeguroMatriz(posx + 1, posy, mapa.size(), mapa[0].size()))
            return mapa[posx + 1][posy];
        break;
    case 3:
        pos = Pos(0, 1);
        if (IndiceSeguroMatriz(posx, posy + 1, mapa.size(), mapa[0].size()))
            return mapa[posx][posy + 1];
        break;
    case 4:
        pos = Pos(0, -1);
        if (IndiceSeguroMatriz(posx, posy - 1, mapa.size(), mapa[0].size()))
            return mapa[posx][posy - 1];
        break;
    case 5:
        pos = Pos(-1, 1);
        if (IndiceSeguroMatriz(posx - 1, posy + 1, mapa.size(), mapa[0].size()))
            return mapa[posx - 1][posy + 1];
        break;
    case 6:
        pos = Pos(-1, -1);
        if (IndiceSeguroMatriz(posx - 1, posy - 1, mapa.size(), mapa[0].size()))
            return mapa[posx - 1][posy - 1];
        break;
    case 7:
        pos = Pos(1, 1);
        if (IndiceSeguroMatriz(posx + 1, posy + 1, mapa.size(), mapa[0].size()))
            return mapa[posx + 1][posy + 1];
        break;
    case 8:
        pos = Pos(1, -1);
        if (IndiceSeguroMatriz(posx + 1, posy - 1, mapa.size(), mapa[0].size()))
            return mapa[posx + 1][posy - 1];
        break;
    default:
        return 0;
        break;
    }
    return 0;
}

bool RoboVasc::IndiceSeguroMatriz(int i, int j, int maxI, int maxJ)
{
    if (i >= 0 && i < maxI && j >= 0 && j < maxJ)
    {
        return true;
    }
    return false;
}

Caminho RoboVasc::consegueVoltarBateria(Pos objetivo, bool &consegue)
{
    Caminho cam;
    cam.first = -1;
    int custoObj = 1;
    consegue = true;
    if(0 == posx && 0 == posy)
        return cam;
    cam = a_estrela(Pos(posx, posy), Pos(0, 0), mapa);
    if ((objetivo.first - posx != 0) && (objetivo.second - posy != 0))
        custoObj = 1.5;
    if (cam.first > bateria - custoObj || cam.first > tempo - custoObj)
        consegue = false;
    return cam;
}

void RoboVasc::verificarBateria(int acaoEscolhida) {
    Pos objetivo(0,0);
    explorado(acaoEscolhida, objetivo);
    bool consegue = true;
    Caminho caminho_volta = consegueVoltarBateria(objetivo, consegue);
    if(!consegue && caminho_volta.first != -1) {
        estado = VOLTANDO;
        caminho = a_estrela(Pos(posx, posy), Pos(0, 0), mapa);
        i_voltando = 0;
        decidirMovimentoVoltando();
        return;
    }
}

void RoboVasc::imprimirMapa()
{
    cout << endl
         << "--- Mapa Robo ---" << endl;
    for (int i = 0; i < mapa.size(); i++)
    {
        string c = "  ";
        for (int j = 0; j < mapa[i].size(); j++)
        {
            switch (mapa[i][j])
            {
            case -1:
                c = "? ";
                break;
            case -2:
                c = "O ";
                break;
            case 0:
                c = "X ";
                break;
            case 1:
                c = ". ";
                break;
            default:
                string aux = "";
                aux += mapa[i][j] + 46;
                aux += " ";
                c = aux;
                break;
            }
            cout << c << " ";
        }
        cout << endl;
    }

    // cout << "--- Sinais vitais encontrados ---\n";
    // for (int i = 0; i < vitimas.size(); i++)
    // {
    //     cout << "Vitima " << i << ": ";
    //     for (int j = 0; j < vitimas[i].size(); j++)
    //     {
    //         cout << vitimas[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}

void RoboVasc::Mover(int acao) {
    switch (acao)
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

vector<vector<int>> RoboVasc::getMapa() {
    return mapa;
}