#ifndef POKER_GAME_CPP
#define POKER_GAME_CPP

#include "Poker_Game.hpp"

Poker_Game::Poker_Game(){
    Baralho _baralho;
    Jogador _jogador;
    Computador _bot;
    int POT = 0; //Premio do vencedor(Soma das apostas)
    int aposta_anterior = 0;
    int _jogador_atual = 0;
    int _rodada = 0;
}

Poker_Game::~Poker_Game(){
    _baralho.~Baralho();
    _jogador.~Jogador();
    _bot.~Computador();
}

std::string Poker_Game::showdown(Jogador &jogador, Jogador &bot){
    jogador.virar_cartas();
    bot.virar_cartas();

    int mao_jogador = jogador.getObjeto_mao_jogador().determinar_valor_mao();
    int mao_bot = bot.getObjeto_mao_jogador().determinar_valor_mao();

    if(mao_jogador > mao_bot){
        jogador.adicionar_fichas(getPOT());
        return "JOGADOR VENCEU";;
    }
    else if(mao_bot > mao_jogador){
        bot.adicionar_fichas(getPOT());
        return "BOT VENCEU";
    }
    else{ //mao_jogador == mao_bot 
        jogador.adicionar_fichas(getPOT()/2);
        bot.adicionar_fichas(getPOT()/2);
        return "JOGO EMPATADO";
    }
}

//Limpa tudo e retorna um novo baralho
Baralho &Poker_Game::limpar_mesa(Baralho &baralho, Jogador &jogador, Computador &bot){
    baralho.~Baralho();
    jogador.getVector_mao_jogador().clear();
    bot.getVector_mao_jogador().clear();
    setPOT(0);
    // Baralho baralho;
    return baralho;
}

//GETTERS E SETTERS ---------------------------------------
        
Baralho &Poker_Game::getBaralho(){return _baralho;}
Jogador &Poker_Game::getJogador(){return _jogador;}
Computador &Poker_Game::getBot(){return _bot;}

int Poker_Game::getPOT(){return _POT;}
void Poker_Game::adiciona_aposta_POT(int valor_aposta){_POT += valor_aposta;}
void Poker_Game::setPOT(int POT){_POT = POT;}

int Poker_Game::getAposta_anterior(){return _aposta_anterior;}
void Poker_Game::setAposta_anterior(int aposta_anterior){_aposta_anterior = aposta_anterior;}

int Poker_Game::getJogador_atual(){return _jogador_atual;}
void Poker_Game::setJogador_atual(int jogador_atual){_jogador_atual = jogador_atual;}

int Poker_Game::getRodada(){return _rodada;}
void Poker_Game::setRodada(int rodada){_rodada = rodada;}


#endif
