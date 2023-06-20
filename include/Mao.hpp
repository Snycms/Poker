#ifndef MAO_HPP
#define MAO_HPP

#include "Carta.hpp"

#include <vector>
#include <string>

class Mao{
  protected:
    std::vector<Carta> _mao;
  
  public:
    //Inicia mao dos jogadores
    Mao();
    //Destrutor
    ~Mao();

    //Adiciona mais cartas no flop, turn e river = setMao
    void adiciona_carta(Carta carta); 

    //Compara as cartas da mao de um jogador e retorna a maior
    Carta maior_carta(); 

    //Compara as cartas da mao de um jogador e retorna a maior
    Carta menor_carta();
    
    //ordena as cartas da mão do jogador
    void ordena_cartas();

    //Retorna valor da mao do jogador
    std::string valor_mao();

    //confere se as cartas são do mesmo naipe
     bool mesmo_naipe();

     //confere se as cartas estão em sequencia
     bool sequencia();

     int mesmo_valor();
    
    virtual bool combina() const = 0;
    
     }



    class Royal_flush : public Mao{
      public:

      //compara se a mão do jogador é um Royal Flush
      bool combina() const override;
    }



    class Straight_flush : public Mao{
       public:

      //compara se a mão do jogador é um Straight Flush
      bool combina() const override;
    }


    class Quadra : public Mao{
       public:

      //compara se a mão do jogador é uma quadra
      bool combina() const override;
    }



    class Full_house : public Mao{ public:

      //compara se a mão do jogador é um Full House
      bool combina() const override;
    }



    class Flush : public Mao{ 
      public:

      //compara se a mão do jogador é um Flush
      bool combina() const override;
    }



    class Trinca : public Mao{
      public:

      //compara se a mão do jogador é uma trinca
      bool combina() const override;
    }



    class Dois_pares : public Mao{
      public:

      //compara se a mão do jogador tem dois pares
      bool combina() const override;
    }



    class Par : public Mao{ 
      public:

      //compara se a mão do jogador tem um par
      bool combina() const override;
    }




    class Carta_alta : public Mao{ 
      public:

      //compara se a mão do jogador tem a carta mais alta
      bool combina() const override;
    }



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

};

#endif
