
#ifndef AUTOMATION_H
#define AUTOMATION_H


#include <iostream>
#include <string>
#include "Baralho.h"
#include "Jogador.h"

using namespace std;
using namespace Baralhos;
using namespace Players;

namespace Automations {
    class Decisor {
        public:
            static int decidirAcao(
                Jogador *jogador,
                int pote, 
                vector<Carta> cartas_na_mesa,
                int ultima_aposta,
                int jogadores_ativos,
                int rodada,
                int dificuldade
            );
            static int decidirAposta(
                Jogador *jogador,
                int pote, 
                vector<Carta> cartas_na_mesa,
                int ultima_aposta,
                int jogadores_ativos,
                int rodada,
                int dificuldade
            );
    };
    
}
#endif