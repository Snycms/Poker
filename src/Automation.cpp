#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Jogador.h"
#include "Baralho.h"
#include "Contador.h"
#include "Automation.h"

using namespace std;
using namespace Baralhos;
using namespace Players;
using namespace Automations;
using namespace Contador;

int Automations::Decisor::decidirAcao(
    Jogador *jogador,
    int pote, 
    vector<Carta> cartas_na_mesa,
    int ultima_aposta,
    int jogadores_ativos,
    int rodada,
    int dificuldade
) {
    int acao;
    bool pode_aumentar = false;
    bool pode_cobrir = false;
    bool pode_mesa = false;
    vector<int> acoes = {0};
    if (jogador->getFichas() + jogador->getFichasApostadas() > ultima_aposta) {
        pode_aumentar = true;
        acoes.push_back(1);
    } 
    if (jogador->getFichas() + jogador->getFichasApostadas() >= ultima_aposta) {
        pode_cobrir = true;
        acoes.push_back(2);
    }
    if (rodada > 0) {
        pode_mesa = true;
        acoes.push_back(3);
    }

    if (dificuldade == 0) {
        // escolha aleatoriamente um elemento de acoes
        std::random_device rd;
        std::mt19937 gerador(rd());
        std::uniform_int_distribution<int> distribuicao(0, acoes.size());
        int rand = distribuicao(gerador);

        acao = acoes[rand];
    } else {
        acao = -1;
        if (pode_aumentar == 1) {
            // escolha aleatoriamente um elemento de acoes
            vector<Carta> cartas = jogador->exibirCartas();
            cartas.insert(cartas.end(), cartas_na_mesa.begin(), cartas_na_mesa.end());
            std::sort(cartas.begin(), cartas.end(), greater<Carta>());

            if (
                ContadorDeBaralho::ocorreuStraightFlush(jogador->exibirCartas(), cartas_na_mesa) ||
                ContadorDeBaralho::ocorreuQuadra(jogador->exibirCartas(), cartas_na_mesa) ||
                ContadorDeBaralho::ocorreuFullHouse(jogador->exibirCartas(), cartas_na_mesa) ||
                ContadorDeBaralho::ocorreuFlush(jogador->exibirCartas(), cartas_na_mesa) ||
                ContadorDeBaralho::ocorreuSequencia(jogador->exibirCartas(), cartas_na_mesa) ||
                ContadorDeBaralho::ocorreuDoisPares(jogador->exibirCartas(), cartas_na_mesa) ||
                ContadorDeBaralho::ocorreuPares(jogador->exibirCartas(), cartas_na_mesa)
            ) {
                acao = 3;
            } else {
                int maior_carta = cartas[0].getIndice();
                if (maior_carta > 10) {
                    acoes.push_back(1);
                    acoes.push_back(1);
                    acoes.push_back(1);
                    acoes.push_back(1);
                } else if (maior_carta > 7) {
                    acoes.push_back(1);
                    acoes.push_back(1);
                    acoes.push_back(1);
                } else {
                    acoes.push_back(1);
                    acoes.push_back(1);
                }
                
            }
        } else {
            if (pode_cobrir == 1) {
                acoes.push_back(2);
                acoes.push_back(2);

            } else {
                if (pode_mesa == 1) {
                    acoes.push_back(3);
                    acoes.push_back(3);
                } 
                acoes.push_back(0);
                acoes.push_back(0);
            }
        }
        std::random_device rd;
        std::mt19937 gerador(rd());
        std::uniform_int_distribution<int> distribuicao(0, acoes.size());
        int rand = distribuicao(gerador);
        acao = acoes[rand];
    }
    return acao;

};

int Automations::Decisor::decidirAposta(
    Jogador *jogador,
    int pote, 
    vector<Carta> cartas_na_mesa,
    int ultima_aposta,
    int jogadores_ativos,
    int rodada,
    int dificuldade
) {
    int proposta = ultima_aposta +1;
    int fichas = jogador->getFichas();
    int fichas_apostadas = jogador->getFichasApostadas();
    // if (dificuldade == 0) {
    //     Vector<int> valores = {proposta};
    //     for (int i = 0; i < (fichas+fichas_apostadas) - proposta-1; i++) {
    //         valores.push_back(proposta + i);
    //     }
    //     proposta = valores[rand() % valores.size()];
    // } else {
    //     // bolar estratégia
    // }
    vector<int> valores = {ultima_aposta};
    for (int i = 0; i < (fichas+fichas_apostadas) - proposta-1; i++) {
        valores.push_back(i);
    }
    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_int_distribution<int> distribuicao(0, valores.size());
    int rand = distribuicao(gerador);
    proposta += valores[rand];
    return proposta;
}