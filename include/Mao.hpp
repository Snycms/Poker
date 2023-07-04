#ifndef MAO_HPP
#define MAO_HPP

#include "Carta.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include<algorithm>
class Mao{
  protected:
    std::vector<Carta> _mao;
  
  public:
    //Inicia mao dos jogadores
    Mao();
    //Destrutor
    ~Mao();

    void exibe_mao();

    //Adiciona mais cartas no flop, turn e river = setMao
    void adiciona_carta(Carta carta); 

    //Compara as cartas da mao de um jogador e retorna a maior
    Carta maior_carta(); 

    //Checa se a mão é um par, trinca, quadra ou full house
    //Se não for nenhuma dessas mãos, retorna "cartaAlta"
    std::string getHandRank();

    //Compara as cartas da mao de um jogador e retorna a maior
    Carta menor_carta();
    
    //ordena as cartas da mão do jogador
    void ordena_cartas();

    //Retorna valor da mao do jogador
    std::string valor_mao();

    //confere se as cartas são do mesmo naipe (flush)
    std::string flush();

    //confere se as cartas estão em sequencia (straight)
    std::string straight();

    //confere se as cartas estão em sequência e são do mesmo naipe (straight flush)
    std::string straightFlush();
    
    //checa se a mão é um Royal Flush;
    //retorna 1 se verdadeiro;
    //retorna 0 se falso;
    std::string Royal_flush();

    std::vector<Carta> &getMao();
    
  };

  


    

    /* 
    //POSSIVEIS MAOS--------------------------------------------

    //Royal Flush e Straight Flush
    int royal_flush_e_straight_flush();
    //Quadra e Full House
    int quadra_e_fullHouse();
    //Flush
    int flush();
    //Straight
    int straight();
    //Trinca, Dois Pares, Par e Carta Alta
    int trinca_doisPares_par_cartaAlta();

    //----------------------------------------------------------

    //TESTE ONLINE GDB
    void exibe_mao();
    
    //GETTERS E AUXILIARES---------------------------------------
    
    //Ordena as cartas da mao(maior para a menor)
    static bool ordena_mao_valor(Carta x, Carta y);

    //Get mao
    std::vector<Carta> &getMao();*/

#endif
