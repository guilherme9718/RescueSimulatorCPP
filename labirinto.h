#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;

class Labirinto
{
    private:

    vector<vector<int>> labirinto;
    int vitimaCount;

    public:

    Labirinto(int x, int y);
    ~Labirinto();

    void imprimeLabirinto();
    void PreencheLabirinto();
};