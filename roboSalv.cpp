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

void RoboSalv::imprime_labirinto(Pos robo_pos)
{
    for(int i = 0; i < labirinto.size(); i++)
    {
        for(int j = 0; j < labirinto[i].size(); j++)
        {
            if(i == robo_pos.first && j == robo_pos.second)
            {
                cout << "R  ";
                continue;
            }
            switch (labirinto[i][j])
            {
            case -2:
                cout << "S  ";
                break;
            case -1:
                cout << "?  ";
                break;
            case 0:
                cout << "X  ";
                break;
            case 1:
                cout << ".  ";
                break;
            default:
                cout << "V  ";
                break;
            }
        }
        cout << endl;
    }
}

    //Lista de ações
    //1 - Norte
    //2 - Sul
    //3 - Leste
    //4 - Oeste
    //5 - Nordeste
    //6 - Noroeste
    //7 - Sudeste
    //8 - Sudoeste
    //9 - Salvar vitima
    //10 - Carregar carga
    //11 - Carregar Bateria
void RoboSalv::executar_plano()
{
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_for(milliseconds(6000));
    system("clear");
    Pos robo_pos = make_pair(0,0);
    float t = tempo;
    float b = bateria;
    for(int i = 0; i < acoes.size(); i++)
    {
        for(int j = 0; j < acoes[i].size(); j++)
        {
            //Faz a acao do vetor
            switch (acoes[i][j])
            {
            case 1: //Norte
                robo_pos.first += -1;
                cout << "Mover norte" << endl;
                t -= 1;
                cout << "Tempo restante: " << t << endl;
                b -= 1;
                cout << "Bateria restante: " << b << endl;
                break;
            
            case 2: //Sul
                robo_pos.first += 1;
                cout << "Mover sul" << endl;
                t -= 1;
                cout << "Tempo restante: " << t << endl;
                b -= 1;
                cout << "Bateria restante: " << b << endl;
                break;
            case 3: //Leste
                robo_pos.second += 1;
                cout << "Mover leste" << endl;
                t -= 1;
                cout << "Tempo restante: " << t << endl;
                b -= 1;
                cout << "Bateria restante: " << b << endl;
                break;
            case 4: //Oeste
                robo_pos.second += -1;
                cout << "Mover oeste" << endl;
                t -= 1;
                cout << "Tempo restante: " << t << endl;
                b -= 1;
                cout << "Bateria restante: " << b << endl;
                break;
            case 5: //Nordeste
                robo_pos.first += -1;
                robo_pos.second += 1;
                cout << "Mover nordeste" << endl;
                t -= 1.5;
                cout << "Tempo restante: " << t << endl;
                b -= 1.5;
                cout << "Bateria restante: " << b << endl;
                break;
            case 6: //Noroeste
                robo_pos.first += -1;
                robo_pos.second += -1;
                cout << "Mover noroeste" << endl;
                t -= 1.5;
                cout << "Tempo restante: " << t << endl;
                b -= 1.5;
                cout << "Bateria restante: " << b << endl;
                break;
            case 7: //Sudeste
                robo_pos.first += 1;
                robo_pos.second += 1;
                cout << "Mover sudeste" << endl;
                t -= 1.5;
                cout << "Tempo restante: " << t << endl;
                b -= 1.5;
                cout << "Bateria restante: " << b << endl;
                break;
            case 8: //Sudoeste
                robo_pos.first += 1;
                robo_pos.second += -1;
                cout << "Mover sudoeste" << endl;
                t -= 1.5;
                cout << "Tempo restante: " << t << endl;
                b -= 1.5;
                cout << "Bateria restante: " << b << endl;
                break;
            case 9: //Salvar Vitima
                labirinto[robo_pos.first][robo_pos.second] = -2;
                cout << "Salvar vitima" << endl;
                t -= 0.5;
                cout << "Tempo restante: " << t << endl;
                b -= 0.5;
                cout << "Bateria restante: " << b << endl;
                break;
            case 10: //Carregar Carga
                cout << "Carregar carga" << endl;
                t -= 0.5;
                cout << "Tempo restante: " << t << endl;
                b -= 0.5;
                cout << "Bateria restante: " << b << endl;
                break;
            case 11: //Carregar Bateria
                cout << "Carregar bateria" << endl;
                t -= 240;
                cout << "Tempo restante: " << t << endl;
                b = bateria;
                cout << "Bateria restante: " << b << endl;
                break;
            default:
                cout << "Erro, acao invalida" << endl;
                break;
            }
            imprime_labirinto(robo_pos);
            sleep_for(milliseconds(800));
            system("clear");
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
        cout << vitimas[i][6] << " " << vitimas[i][7] << endl;
        heap_vitimas.push(make_pair(d,i));
    }

    float t_restante = tempo;
    float b_restante = bateria;
    cout << "Planejamento:" << endl;
    //loop principal
    while(t_restante > 0)
    {
        //tenta encontrar um caminho que socorre o maior numero de vitimas
        Pos atual = make_pair(0,0); //marca a posicao da base como posicao atual
        float t_acumulado = 0;
        for(int i = 0; i < carga; i++)
        {
            //caso o heap esteja vazio
            if(heap_vitimas.empty())
            {
                cout << "Todas as vitimas encontradas, voltar base" << endl << endl;
                break;
            }

            //pega a vitima mais perto da base
            Vitima v = heap_vitimas.top();
            //calcula os caminhos, com o a*, ida do atual ate a vitima selecionada e volta da vitima selecionada ate a base
            cout << "ida " << endl;
            Caminho ida = a_estrela(atual, make_pair(vitimas[v.second][6], vitimas[v.second][7]), labirinto);
            cout << "volta " << endl;
            Caminho volta = a_estrela(make_pair(vitimas[v.second][6], vitimas[v.second][7]), make_pair(0,0), labirinto);

            //caso o tempo acumulado + ir ate a vitima e salva-la + voltar seja menor que o tempo restante
            if(t_acumulado + ida.first + volta.first + 0.5 < t_restante)
                if(t_acumulado + ida.first + volta.first + 0.5 < b_restante) //o mesmo para a bateria
                {
                    t_acumulado += ida.first + 0.5;

                    //retira a volta anterior da matriz de acoes
                    if(!(atual.first == 0 && atual.second == 0))
                        acoes.erase(acoes.end()-1);
                    //adiciona ida na matriz de acoes + salvar vitima
                    ida.second.push_back(9);
                    acoes.push_back(ida.second);
                    //adiciona a volta na matriz de acoes + carregar carga
                    volta.second.push_back(10);
                    acoes.push_back(volta.second);

                    heap_vitimas.pop();
                    atual = make_pair(vitimas[v.second][6], vitimas[v.second][7]);
                    
                    cout << "Salvar vitima em " << atual.first << "," << atual.second << endl;
                    for(int i = 0; i < acoes.size(); i++)
                    {
                        //cout << "Acao " << i << ": "; 
                        for(int j = 0; j < acoes[i].size(); j++)
                        {
                            //cout << acoes[i][j] << " ";
                        }
                        //cout << endl;
                    }
                    if(i == carga-1)
                        cout << "Voltar base" << endl << endl;
                    continue;
                }
            cout << "Voltar base" << endl << endl;
            break;
        }
        
        if(heap_vitimas.empty())
            break;

        t_restante -= t_acumulado;
        b_restante -= t_acumulado;
        //caso nao tenha saido do lugar
        if(atual.first == 0 && atual.second == 0)
        {
            if(t_restante >= 240)
            {
                cout << "Recarregar bateria" << endl;
                //recarrega bateria
                vector<int> a;
                a.push_back(11);
                acoes.push_back(a);

                t_restante -= 240;
                b_restante = bateria;
            }
            else
            {
                cout << "Sem tempo restante para ir ate prox vitima ou carregar bateria" << endl;
                cout << "Fim do planejamento" << endl;
                t_restante = 0;
            }
        }
    }
    
    executar_plano();
}
