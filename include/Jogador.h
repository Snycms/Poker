
#ifndef JOGADOR_H
#define JOGADOR_H


#include <iostream>
#include <string>
#include "Baralho.h"

using namespace std;
using namespace Baralhos;

namespace Players {
    // class Persona {
    //     private:
    //         int id;
    //         std::string nome;
    //     public:
    //         Persona(int id, std::string nome);
    //         ~Persona();
    //         std::string getNome();
    //         int getId();
    //         void setNome(std::string nome);
    //         void setId(int id);

    // }
    class Jogador {
        private:
            int id;
            bool bot;
            bool atividade;
            std::string nome;
            int fichas;
            int fichas_apostadas;
            int pontos;
            vector<Carta> baralho;
        public:
            Jogador(int id, bool bot, std::string nome);
            ~Jogador();
            std::string getNome();
            int getId();
            int getPontos();
            bool getAtividade();
            bool getBot();
            int getFichas();
            int getFichasApostadas();
            void setPontos( int pontos);
            void setId( int id);
            void setFichas( int fichas);
            void setFichasApostadas(int fichas);
            void setBot( bool bot);
            void setAtividade( bool ativadade);
            void setNome(std::string nome);
            void adicionarFichas(int fichas);
            void apostarFichas(int fichas);
            void adicionarPontos(int pontos);
            void limparBaralho();
            void receberBaralho(vector<Carta> baralho);
            vector<Carta> exibirCartas();


    };

    class Dealer {
        private:
            int id;
            std::string nome;
            vector<Carta> baralho;
        public:
            Dealer(int id, std::string nome);
            ~Dealer();
            std::string getNome();
            int getId();
            void setNome(std::string nome);
            void setId(int id);
            void receberBaralho(vector<Carta> baralho);
            void limparBaralho();
            vector<Carta> exibirCartas(int quantidade);
    };
}
#endif