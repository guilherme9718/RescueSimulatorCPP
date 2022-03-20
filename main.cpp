#include "labirinto.h"
#include "roboSalv.h"
#include "roboVasc.h"

#include <fstream>
#include <iostream>
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
        while(i < linha.size())
        {
            aux *= 10;
            aux += linha[i]-48;
            i++;
        }
        dados.push_back(aux);
    }

    *v = new RoboVasc(dados[0], dados[1], dados[4], dados[2]);

    *s = new RoboSalv(dados[6], dados[5], dados[3]);

    *l = new Labirinto(dados[0], dados[1]);

}

int main()
{
    RoboVasc* vasc;
    RoboSalv* salv;
    Labirinto* lab;

    inicializarLabirinto(&vasc, &salv, &lab);

    vasc->imprimirDados();
    salv->imprimirDados();
    lab->imprimeLabirinto();

}