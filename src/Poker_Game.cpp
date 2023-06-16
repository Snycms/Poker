#ifndef POKER_GAME_CPP
#define POKER_GAME_CPP

#include "Poker_Game.hpp"

Poker_Game::Poker_Game(){
    Jogador _jogador[4];
    int POT = 0;
    int _jogador_atual = 0;
    Baralho _baralho;
    int _rodada = 0;
}
Poker_Game::~Poker_Game(){
    for(int i=0; i<4; ++i){_jogador[i].~Jogador();}
    _baralho.~Baralho();
}

void Poker_Game::jogar_rodada(){
    for(int i=0; i<4;++i){

    }
}

int Poker_Game::getJogador_atual(){}
int Poker_Game::getRodada(){}

#endif