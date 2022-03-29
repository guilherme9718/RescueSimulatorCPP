#include "a_estrela.h"

bool acessivel(Pos elem, vector<vector<int>> labirinto)
{
    if(elem.first >=0 && elem.first < labirinto.size())             //x esta dentro da matriz
        if(elem.second >=0 && elem.second < labirinto[0].size())    //y esta dentro da matriz
            if(labirinto[elem.first][elem.second] > 0)              // > 0 vago ou pessoa
                return true;

    return false;
}

double calculaDist(Pos p1, Pos p2)
{
    return sqrt(pow((p1.first - p2.first),2) + pow((p1.second - p2.second),2));
}

void constroi_dados(vector<vector<Dados>> &d, Pos max)
{
    Dados d_aux;
    d_aux.f = numeric_limits<float>::max();
    d_aux.g = numeric_limits<float>::max();
    d_aux.pai = make_pair(-1,-1);
    d_aux.acao = 0;

    vector<Dados> aux;
    for(int j = 0; j < max.second; j++)
        aux.push_back(d_aux);

    for(int i = 0; i < max.first; i++)
        d.push_back(aux);
}

Caminho interpreta_caminho(vector<vector<Dados>> elementos, Pos inicial, Pos destino)
{
    vector<int> acoes;
    int i = destino.first;
    int j = destino.second;

    do
    {
        acoes.push_back(elementos[i][j].acao);
        
        int auxi = elementos[i][j].pai.first;
        int auxj = elementos[i][j].pai.second;
        i = auxi;
        j = auxj;
    } while(i != inicial.first && j != inicial.second);

    vector<int> rev;
    for(int i = acoes.size()-1; i >=0; i--)
        rev.push_back(acoes[i]);

    Caminho aux;
    aux.first = elementos[destino.first][destino.second].f;
    aux.second = rev;
    return aux;
}

int interpreta_acao(int i, int j)
{
    if(i == -1 && j == 0)   //norte
        return 1;

    if(i == 1 && j == 0)    //sul
        return 2;

    if(i == 0 && j == 1)    //leste
        return 3;
    
    if(i == 0 && j == -1)   //oeste
        return 4;
    
    if(i == -1 && j == 1)   //nordeste
        return 5;
    
    if(i == -1 && j == -1)  //noroeste
        return 6;
    
    if(i == 1 && j == 1)    //sudeste
        return 7;

    if(i == 1 && j == -1)   //sudoeste
        return 8;

    //algo deu errado, posicao pai == pos filho
    cout << "Erro\n";
    return -1;
}

Caminho a_estrela(Pos inicial, Pos destino, vector<vector<int>> labirinto)
{
    vector<vector<Dados>> elementos;    //retorno desta funcao
    int max_lin = labirinto.size();
    int max_col = labirinto[0].size();

    constroi_dados(elementos, make_pair(max_lin, max_col)); //inicia todos os valores de elementos

    bool ja_visitado[max_lin][max_col]; //matriz nao visitar duas vezes a mesma posicao no a*
    memset(ja_visitado, false, sizeof(ja_visitado)); //coloca tudo em ja_visitado como false

    elementos[inicial.first][inicial.second].f = 0.0;   //coloca os valores da posicao inicial
    elementos[inicial.first][inicial.second].g = 0.0;

    priority_queue<Elemento, vector<Elemento>, greater<Elemento>> viz; //heap para a vizinhanca 
    viz.push(make_pair(0.0, make_pair(inicial.first, inicial.second))); //adiciona o inicial no heap

    while(!viz.empty())
    {
        //retira o elemento com menor f do heap
        Elemento atual = viz.top();
        viz.pop();
        int x = atual.second.first;
        int y = atual.second.second;

        //caso tenha sido visitado ignora
        if(ja_visitado[x][y])
            continue;

        //caso nao tenha sido marca como visitado
        cout << "Selecionou: " << x << " " << y 
        << ", filho de: " << elementos[x][y].pai.first << " " << elementos[x][y].pai.second << endl;
        ja_visitado[x][y] = true;

        //caso o atual seja o destino retorna o caminho
        if(atual.second == destino)
            return interpreta_caminho(elementos, inicial, destino);
        
        //olha a vizinhanca de prox para colocar no heap
        for(int i = -1; i <=1; i++)
        {
            for(int j = -1; j <=1; j++)
            {
                Pos vizinho = make_pair(x+i,y+j); //par do vizinho
                //caso nao seja vago ou vitima ou ja tinha sido visitado, vai pro prox vizinho
                if(!acessivel(vizinho, labirinto) || ja_visitado[vizinho.first][vizinho.second])
                    continue;

                Dados aux;  //dados do vizinho

                aux.g = elementos[x][y].g + 1.0;  //g = g do atual + 1
                if(i != 0 && j != 0)                //caso esteja na diagonal, g = + 0.5 
                    aux.g += 0.5;

                aux.f = aux.g + (float)calculaDist(vizinho, destino);    // f = g do viz + dist ate o destino
                
                //caso f seja menor que o f no elementos, coloca no heap e atualiza a matriz elementos
                if(aux.f < elementos[vizinho.first][vizinho.second].f)
                {
                    //coloca em dados
                    aux.pai = atual.second;
                    aux.acao = interpreta_acao(i,j);
                    elementos[vizinho.first][vizinho.second] = aux;

                    //coloca no heap
                    Elemento e;
                    e.first = aux.f;
                    e.second = make_pair(vizinho.first, vizinho.second);
                    viz.push(e);
                }
            }
        }
        
    }

    cout << "Falha na busca, caminho nao encontrado" << endl;
    Caminho falhou;
    falhou.first = -1;
    return falhou;
}
/*
for(int i = 0; i < max_lin; i++)
    {
        for(int j = 0; j < max_col; j++)
        {
            
        }
    }
*/