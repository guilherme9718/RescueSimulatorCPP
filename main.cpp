#include "labirinto.h"
#include "roboSalv.h"
#include "roboVasc.h"
#include "a_estrela.h"

#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int tam_max;

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

    // *v = new RoboVasc(dados[0]+1, dados[1]+1, dados[4], dados[2], *l);
    *v = new RoboVasc(tam_max, tam_max, dados[4], dados[2], *l);

    *s = new RoboSalv(dados[6], dados[5], dados[3]);

}

int main()
{
    cout << "Digite tam max da matriz: ";
    cin >> tam_max;

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
    //sleep_for(milliseconds(6000));

    while(vasc->completou == false) {
        //system("clear");
        //cout << "---Mapa do robo vasculhador: " << endl;
        vasc->deliberar();
        //lab->imprimeLabirinto();
        //vasc->imprimirMapa();
        //cout << "Tempo restante: " << vasc->tempo << endl;
        //cout << "Estado Robo: " << vasc->estado << endl;
        //sleep_for(milliseconds(60));
    }

    int soma = 0;
    for(int i = 0; i < tam_max; i++)
    {
        for(int j = 0; j < tam_max; j++)
        {
            if(vasc->getMapa()[i][j] == -1)
                soma++;
        }
    }
    cout << "Matriz: " << tam_max << " X " << tam_max << endl;
    cout << "Numero de explorados: " << (tam_max * tam_max) - soma << endl;
    cout << "Bateria gasta: " << vasc->bateria_i - vasc->bateria << endl;
    sleep_for(milliseconds(6000));

    system("clear");
    cout << "Robo Vasculhador completou" << endl;
    
    salv->recebeMatrizes(vasc->getMapa(), vasc->getVitimas());
    salv->planejar();

    
    return 0;
}
