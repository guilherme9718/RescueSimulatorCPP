#pragma once
#include <utility>
#include <cmath>
#include <vector>
#include <iostream>
#include <limits>
#include <cstring>
#include <queue>

using namespace std;

//Par para coordenada
typedef pair<int, int> Pos;

//Par para elemento a ser adicionado no heap, 
//sendo do tipo <f do a*, coordenada>
typedef pair<float, Pos> Elemento;

//Retorno do a* para o robo, sendo o custo para chegar ate o destino e um vetor de acoes
typedef pair<float, vector<int>> Caminho;

//Dados de cada elemento que sera retornado para o robo sendo eles
typedef struct dados
{
	Pos pai;	//posicao do labirinto que chegou nele
	int acao;	//acao que o pai fez pra chegar nele
	float f;	//f do a*
	float g;	//g = bateria/tempo gasto para chegar nele
} Dados;

//Auxilia a calcular se elemento esta dentro do labirinto
//e nao bloqueado por pedra
bool acessivel(Pos elem, vector<vector<int>> labirinto);

//Calcula a distancia euclideana para os dois pontos,
//vai ser usada na heuristica
double calculaDist(Pos p1, Pos p2);

//Constroi a matriz de dados
void constroi_dados(vector<vector<Dados>> &d, Pos max);

//Retorna a acao que o pai fez para chegar no filho
int interpreta_acao(int i, int j);

Caminho interpreta_caminho(vector<vector<Dados>> elementos);

//Faz o a* e retorna uma matriz contendo os dados dos elementos do labirinto
Caminho a_estrela(Pos inicial, Pos destino, vector<vector<int>> labirinto);

pair<int, int> procurarObjetivoMaisProximo(int codObjetivo, int posxInicial, int posyInicial, vector<vector<int>> *mapa);