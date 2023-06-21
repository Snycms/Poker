#ifndef RODADA_H
#define RODADA_H

#include <iostream>
#include <vector>
#include "Poker_game.hpp"
#include "resultado.hpp"


class Rodada{

    protected:
    int _nPartidas;
    int _apostaInicial;
    std::vector<PokerGame> _partidas;
    Resultado _resultado;

    public:

    Rodada();
    Rodada(int nPartidas, int apostaInicial, std::vector<Poker_Game> partidas, Resultado resultado );
    
    ///getters
    int getNPartidas() const {return nPartidas; }
    int getApostaInicial() const {return apostaInicial;}
    Resultado getResultado() const {return _result;}
    std::vector<Poker_Game>() const {return _partidas;}

    //setters
    void setNPartidas(int nPartidas){_nPartidas = nPartidas;}
    void setApostaInicial(int apostaInicial){ _apostaInicial = apostaInicial;}
    void setResultado(Resultado resultado){_resultado = resultado;}
    void setPartidas(std::vector<PokerGame> partidas){_partidas = partidas;}



}

#endif
