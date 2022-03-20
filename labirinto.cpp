#include "labirinto.h"

//-2 = agente
//-1 = desconhecido
//0 = parede
//1 = vago
// > 1 = pessoa

Labirinto::Labirinto(int x, int y)
{
    vitimaCount = 0;
    for(int i = 0; i < x; i++)
    {
        vector<int> aux;
        for(int j = 0; j < y; j++)
            aux.push_back(1);
        labirinto.push_back(aux);
    }

    PreencheLabirinto();
    imprimeLabirinto();
}

Labirinto::~Labirinto()
{
    
}

void Labirinto::imprimeLabirinto()
{
    for(int i = 0; i < labirinto.size(); i++)
    {
        for(int j = 0; j < labirinto[i].size(); j++)
        {
            cout << labirinto[i][j] << " ";
        }
        cout << endl;
    }
}

void Labirinto::PreencheLabirinto() {
    std::ifstream file;
    file.open("ambiente.txt", std::ios_base::in);
    
    if(!file) {
        cout << "ambiente.txt não encontrado" << endl;
        exit(1);
    }

    string line;
    regex regexp(R"regex(\d*,\d*)regex");
    
   
    
    while(getline(file, line)) {
        cout << "getline ----\n";
        int modo = 0;
        smatch m;
        string aux = line.c_str();
        cout << line << endl;
        while(regex_search(aux, m, regexp)) {
            string pos_str = m.str(0);
            int virgula = (int)pos_str.find(",");
            int x=0, y=0;
            string x_str="", y_str="";
            for(int i=0; i < pos_str.size(); i++) {
                if(i < virgula)
                    x_str += pos_str[i];
                else if (i > virgula)
                    y_str += pos_str[i];
            }
            x = stoi(x_str);
            y = stoi(y_str);
            
            cout << x << " " << y << endl;

            if(modo == 0) {
                labirinto[x][y] = -2;
            }
            else if(modo == 1) {
                labirinto[x][y] = 0; 
            }
            else if(modo == 2) {
                labirinto[x][y] = vitimaCount+2;
                vitimaCount++;
            }

            aux = m.suffix();
        }
        modo++;
    }
}