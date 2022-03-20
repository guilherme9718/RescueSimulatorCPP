#pragma once
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Labirinto
{
    private:

    vector<vector<int>> labirinto;

    public:

    Labirinto(int x, int y);
    ~Labirinto();

    void imprimeLabirinto();
};