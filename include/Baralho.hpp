#ifndef BARALHO_HPP
#define BARALHO_HPP

#include "Carta.hpp"
#include "Mao.hpp"

#include <string>
#include <vector>

class Baralho{
  private:
    std::vector<Carta> _baralho;
  
  public:
    Baralho();
    ~Baralho();
    
    void embaralha();
    
    //Retorna primeira carta de cima do baralho 
    Carta carta_topo(int posicao);

    //Remove carta do topo
    void remove_carta(std::string jogada);

    //Da as primeiras 2 cartas, Flop(3 cartas), Turn(1 cartas) e o River(1 carta)
    void distribui_carta(std::string jogada, Mao &mao);

    //TESTE ONLINE GDB
    void imprime_baralho();
};

#endif