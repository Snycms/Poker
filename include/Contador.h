
#ifndef CONTADOR_H
#define CONTADOR_H


#include <iostream>
#include <string>
#include "Baralho.h"

using namespace std;
using namespace Baralhos;

namespace Contador {

    class ContadorDeBaralho {
        public :
            static bool ocorreuStraightFlush(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa);  // 20 pontos
            static bool ocorreuQuadra(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa);  // 19 pontos
            static bool ocorreuFullHouse(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa);  // 18 pontos
            static bool ocorreuFlush(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa); // 17 pontos
            static bool ocorreuSequencia(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa); // 16 pontos
            static bool ocorreuDoisPares(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa); // 15 pontos
            static bool ocorreuPares(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa); // 14 pontos
            static int pontuarJogada(vector<Carta> cartas_jogador, vector<Carta> cartas_mesa);
            static std::string nomearJogada(int pontuacao);
    };
    
}
#endif