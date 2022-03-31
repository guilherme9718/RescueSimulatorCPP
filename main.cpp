#include "labirinto.h"
#include "roboSalv.h"
#include "roboVasc.h"
#include "a_estrela.h"

#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void inicializarLabirinto(RoboVasc** v, RoboSalv** s, Labirinto** l)
{
    ifstream arq;
    arq.open("config.txt", ios::in);
    string linha;

    if(!arq)
    {
        cout << "Arquivo nao encontrado";
        exit;
    }

    vector<int> dados;

    while(getline(arq,linha))
    {
        int i = static_cast<int>(linha.find('='))+ 1;
        int aux = 0;
        while(linha[i] >= '0' && linha[i] <= '9') // antigo == i < linha.size()
        {
            cout << linha[i]-48 << " ";
            aux *= 10;
            aux += linha[i]-48;
            i++;
        }
        cout << "dados: " << aux << endl;
        dados.push_back(aux);
    }

    for(int i = 0; i < dados.size(); i++)
        cout << endl << dados[i] << " ";

    *l = new Labirinto(dados[0]+1, dados[1]+1);

    *v = new RoboVasc(dados[0]+1, dados[1]+1, dados[4], dados[2], *l);

    *s = new RoboSalv(dados[6], dados[5], dados[3]);

}

int main()
{
    using namespace std::this_thread;
    using namespace std::chrono;

    RoboVasc* vasc;
    RoboSalv* salv;
    Labirinto* lab;

    inicializarLabirinto(&vasc, &salv, &lab);

    vasc->imprimirDados();
    salv->imprimirDados();
    system("clear");
    cout << "---Labirinto original: " << endl;
    lab->imprimeLabirinto();
    sleep_for(milliseconds(6000));

    while(vasc->completou == false) {
        system("clear");
        cout << "---Mapa do robo vasculhador: " << endl;
        vasc->deliberar();
        //lab->imprimeLabirinto();
        vasc->imprimirMapa();
        cout << "Tempo restante: " << vasc->tempo << endl;
        cout << "Estado Robo: " << vasc->estado << endl;
        sleep_for(milliseconds(60));
    }
    system("clear");
    cout << "Robo Vasculhador completou" << endl;
    
    salv->recebeMatrizes(vasc->getMapa(), vasc->getVitimas());
    salv->planejar();

    
    return 0;
}
