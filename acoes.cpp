#include "labirinto.h"


bool Labirinto::validaAcao(Robo* robo, int posx, int posy) {
    if(robo->bateria > 0 && robo->tempo > 0) {
        if(posx >= 0 && posx < labirinto.size()) {
            if(posy >=0 && posy < labirinto[posx].size()) {
                if(labirinto[posx][posy] > 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

Percepcao Labirinto::mover(Robo* robo, int movX, int movY) {
    Percepcao per;
    int movimentoX=robo->posx+movX, movimentoY=robo->posy+movY;
    if(movX && movY) {
        robo->bateria -= 1.5;
        robo->tempo -= 1.5;
    }
    else {
        robo->bateria -= 1.0;
        robo->tempo -= 1.0;
    }

    if(validaAcao(robo, movimentoX, movimentoY)) {
        per.posx = movimentoX;
        per.posy = movimentoY;
        per.objeto = labirinto[movimentoX][movimentoY];
        per.sucesso = true;
        labirinto[robo->posx][robo->posy] = 1;
        //TODO - Pode sobrepor a vítima no labirinto
        labirinto[movimentoX][movimentoY] = -2;
    }
    else {
        per.posx = robo->posx;
        per.posy = robo->posy;
        per.sucesso = false;
    }

    robo->posx = per.posx;
    robo->posy = per.posy;
    return per;
}

Percepcao Labirinto::moverNorte(Robo* robo) {
    int movX=-1, movY=0;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::moverSul(Robo* robo) {
    int movX=1, movY=0;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::moverLeste(Robo* robo) {
    int movX=0, movY=1;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::moverOeste(Robo* robo) {
    int movX=0, movY=-1;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::moverNordeste(Robo* robo) {
    int movX=-1, movY=1;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::moverNoroeste(Robo* robo) {
    int movX=-1, movY=-1;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::moverSudeste(Robo* robo) {
    int movX=1, movY=1;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::moverSudoeste(Robo* robo) {
    int movX=1, movY=-1;
    return mover(robo, movX, movY);
}
Percepcao Labirinto::pegarVitima(Robo* robo) {

}

vector<int>* Labirinto::LerSinaisVitais(Robo* robo) {
    vector<int>* sinais;
    robo->bateria -= 2;
    robo->tempo -= 2;

    if(robo->bateria > 0 && robo->tempo > 0) {
        if(robo->posx >= 0 && robo->posx < labirinto.size()) {
            if(robo->posy >=0 && robo->posy < labirinto[robo->posx].size()) {
                if(labirinto[robo->posx][robo->posy] > 1) {
                    return sinais;
                }
            }
        }
    }
    return nullptr;
}