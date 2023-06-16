#include "Carta.hpp"
#include "Baralho.hpp"
#include "Mao.hpp"
#include "Jogador.hpp"
//#include "Computador.hpp" 
#include "Poker_Game.hpp"

#include <iostream>
#include <string>
#include <vector>


int main (){
    Baralho baralho;

    baralho.embaralha();
        
    Jogador jogador;

    /*//FLOP
    for(int i=0; i<4; ++i){
            baralho.distribui_carta("FLOP", mao[i]);
    }
    baralho.remove_carta("FLOP");
    //FIM DO FLOP

    //TURN
    for(int i=0; i<4; ++i){
            baralho.distribui_carta("TURN", mao[i]);
    }
    baralho.remove_carta("TURN");
    //FIM DO TURN
        
    //RIVER
    for(int i=0; i<4; ++i){
            baralho.distribui_carta("RIVER", mao[i]);
    }
    baralho.remove_carta("RIVER");
    //FIM DO RIVER*/
}
