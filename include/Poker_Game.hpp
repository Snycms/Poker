#ifndef POKER_GAME_HPP
#define POKER_GAME_HPP

#include "Carta.hpp"
#include "Mao.hpp"
#include "Baralho.hpp"
#include "Jogador.hpp"
#include "Computador.hpp"

class Poker_Game{
    private:
        Jogador _jogador[4];
        //Premio do vencedor(Soma das apostas)
        int POT;
        int _jogador_atual;
        Baralho _baralho;
        int _rodada;
    
    public:

        //inicia o jogo de poker, baralho e rodadas com bolsa de apostas
         
        Poker_Game();
        ~Poker_Game();

        void jogar_rodada();

        int getJogador_atual();
        void setJogador_atual();

        int getRodada();
        void setRodada();
};

#endif