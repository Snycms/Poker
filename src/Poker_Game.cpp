#ifndef POKER_GAME_HPP
#define POKER_GAME_HPP

#include "Carta.hpp"
#include "Mao.hpp"
#include "Baralho.hpp"
#include "Jogador.hpp"
#include "Computador.hpp"

class Poker_Game{
    private:
        Baralho _baralho;
        Jogador _jogador;
        Computador _bot;
        int _POT; //Premio do vencedor(Soma das apostas)
        int _aposta_anterior;
        int _jogador_atual;
        int _rodada;
    
    public:
        Poker_Game();
        ~Poker_Game();

        //Parte final do jogo
        std::string showdown(Jogador &jogador, Jogador &bot);

        Baralho &limpar_mesa(Baralho &baralho, Jogador &jogador, Computador &bot);

        //GETTERS E SETTERS ---------------------------------------

        Baralho &getBaralho();
        Jogador &getJogador();
        Computador &getBot();

        int getPOT();
        void adiciona_aposta_POT(int valor_aposta);
        void setPOT(int valor_aposta);

        int getAposta_anterior();
        void setAposta_anterior(int aposta_anterior);

        int getJogador_atual();
        void setJogador_atual(int jogador_atual);

        int getRodada();
        void setRodada(int rodada);
};

#endif
