#include "labirinto.h"

//-1 = desconhecido
//0 = parede
//1 = vago
// > 1 = pessoa

Labirinto::Labirinto(int x, int y)
{
    for(int i = 0; i < x; i++)
    {
        vector<int> aux;
        for(int j = 0; j < y; j++)
            aux.push_back(1);
        labirinto.push_back(aux);
    }

    ifstream arq;
    arq.open("ambiente.txt", ios::in);
    if(!arq)
    {
        cout << "Arquivo nao encontrado";
        exit;
    }

    string linha;
    getline(arq,linha);

    getline(arq,linha);
    int i;
    i = static_cast<int>(linha.find(' '))+ 1;
    while(i < linha.size())
    {
        int x = 0;
        while(linha[i] != ',')
        {
            x *= 10;
            x += linha[i]-48;
            i++;
        }
        i++;
        int y = 0;
        while(linha[i] != ',')
        {
            y *= 10;
            y += linha[i]-48;
            i++;
        }

        labirinto[x][y] = 0;
        i++;
    }
}

Labirinto::~Labirinto()
{
    
}

void Labirinto::imprimeLabirinto()
{
    for(int i = 0; i < labirinto.size(); i++)
    {
        for(int j = 0; j < labirinto[0].size(); j++)
        {
            cout << labirinto[i][j];
        }
        cout << endl;
    }
}