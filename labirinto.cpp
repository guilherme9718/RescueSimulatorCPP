#include "labirinto.h"

//-2 = agente
//-1 = desconhecido
// 0 = parede
// 1 = vago
// > 1 = pessoa

Labirinto::Labirinto(int x, int y)
{
    vitimaCount = roboposx = roboposy = 0;
    for (int i = 0; i < x; i++)
    {
        vector<int> aux;
        for (int j = 0; j < y; j++)
            aux.push_back(1);
        labirinto.push_back(aux);
    }

    PreencheLabirinto();
    imprimeLabirinto();
    preencheSinaisVitais();
    imprimeSinaisVitais();
}

Labirinto::~Labirinto()
{
}

void Labirinto::imprimeLabirinto()
{
    cout << endl
         << "--- Labirinto ---" << endl;
    for (int i = 0; i < labirinto.size(); i++)
    {
        string c = "  ";
        for (int j = 0; j < labirinto[i].size(); j++)
        {
            if(roboposx == i && roboposy == j)
            {
                cout << "R  ";
                continue;
            }
            switch (labirinto[i][j])
            {
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
                c = "V ";
                break;
            }
            cout << c << " ";
        }
        cout << endl;
    }
}

void Labirinto::PreencheLabirinto()
{
    std::ifstream file;
    file.open("ambiente.txt", std::ios_base::in);

    if (!file)
    {
        cout << "ambiente.txt não encontrado" << endl;
        exit(1);
    }

    string line;
    regex regexp(R"regex(\d*,\d*)regex");

    int modo = 0;

    while (getline(file, line))
    {
        cout << "getline ----\n";
        smatch m;
        string aux = line.c_str();
        cout << line << endl;
        while (regex_search(aux, m, regexp))
        {
            string pos_str = m.str(0);
            int virgula = (int)pos_str.find(",");
            int x = 0, y = 0;
            string x_str = "", y_str = "";
            for (int i = 0; i < pos_str.size(); i++)
            {
                if (i < virgula)
                    x_str += pos_str[i];
                else if (i > virgula)
                    y_str += pos_str[i];
            }
            x = stoi(x_str);
            y = stoi(y_str);

            cout << x << " " << y << endl;

            if (modo == 0)
            {
                labirinto[x][y] = 1;
            }
            else if (modo == 1)
            {
                labirinto[x][y] = 0;
            }
            else if (modo == 2)
            {
                labirinto[x][y] = vitimaCount + 2;
                vitimaCount++;
            }

            aux = m.suffix();
        }
        modo++;
    }
}

//Pronto
//Preenche a matriz de float vitais do labirinto com os valores de sinais vitais.txt
void Labirinto::preencheSinaisVitais()
{
    std::ifstream file;
    file.open("sinaisvitais.txt", std::ios_base::in);

    if (!file)
    {
        cout << "sinaisvitais.txt não encontrado" << endl;
        exit(1);
    }

    string line;

    for(int i = 0; i < vitimaCount; i++)
    {
        getline(file, line);
        vector<float> auxV;
        for(int j = 0; j < 30; j = j+5)
        {
            float auxI = 0;
            auxI += (line[j]-48) + (line[j+2]-48)*0.1 + (line[j+3]-48)*0.01;
            auxV.push_back(auxI);
        }
        vitais.push_back(auxV);
    }
}

//Pronto
//Imprime os sinais vitais
void Labirinto::imprimeSinaisVitais()
{
    cout << "--- Sinais Vitais ---\n";
    for(int i = 0; i < vitimaCount; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            cout << vitais[i][j] << " ";
        }
        cout << endl;
    }
}