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
        while(linha[i] != 13) // antigo == i < linha.size()
        {
            cout << linha[i]-48 << " ";
            aux *= 10;
            aux += linha[i]-48;
            i++;
        }
        cout << endl;
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
    lab->imprimeLabirinto();

    while(vasc->completou == false) {
        //system("clear");
        cout << "Tempo restante: " << vasc->tempo << endl;
        cout << "Estado Robo: " << vasc->estado << endl;
        vasc->deliberar();
        lab->imprimeLabirinto();
        vasc->imprimirMapa();
        sleep_for(milliseconds(600));
    }
    /* cout << "Robo Vasculhador completou" << endl;
    Caminho cam;
    cout << "--- Teste a* de 0,0 para 0,1 ---" << endl;
    cam = a_estrela(make_pair(1,4), make_pair(0,2), lab->getLabirinto());

    cout << "Acoes: ";
    for(int i = 0; i < cam.second.size(); i++)
    {
        cout << cam.second[i] << " ";
    }
    cout << endl;
    cout << "Custo: " << cam.first << endl << endl;

    cout << "Deu certo o/" << endl;


    cout << "--- Teste a* de 0,0 para 1,4 ---" << endl;
    cam = a_estrela(make_pair(2,0), make_pair(0,0), lab->getLabirinto());

    cout << "Acoes: ";
    for(int i = 0; i < cam.second.size(); i++)
    {
        cout << cam.second[i] << " ";
    }
    cout << endl;
    cout << "Custo: " << cam.first << endl << endl;

    cout << "Deu certo o/" << endl;


    cout << "--- Teste a* de 0,0 para 2,3 ---" << endl;
    cam = a_estrela(make_pair(3,0), make_pair(0,0), lab->getLabirinto());

    cout << "Acoes: ";
    for(int i = 0; i < cam.second.size(); i++)
    {
        cout << cam.second[i] << " ";
    }
    cout << endl;
    cout << "Custo: " << cam.first << endl << endl;

    cout << "Deu certo o/" << endl; */

    
    return 0;
}