#ifndef JOGADORES_HPP
#define JOGADORES_HPP

#include "Mao.hpp"

#include <string>

class Jogador{
    private:
        bool _esta_jogando;
        std::string _nome;
        int _fichas;
        Mao _mao;
        int _num_vitoria;
        //Pode ser Dealer, Small Blind ou Big Blind
        std::string _tipo; 
    
    public:
        Jogador();
        ~Jogador();
        
        //Acoes que os jogadores podem realizar----------------------

        //Passa a vez sem apostar(CHECK) e desistir(DESISTIR)
        int check_desistir(std::string acao, int jogador_atual);

        //Tipos de aposta:
        //Aposta normal - Aumentar aposta
        //Call(Aposta mesma quantidade que o ultimo jogador)
        //All-in(Aposta tudo)

        int aposta(std::string tipo_aposta, int valor_aposta);

        //------------------------------------------------------------

        void limpar_mesa();
        
        //TESTE GDB ONLINE
        void exibe_jogador();
        
        //GETTERS E SETTERS ---------------------------------------
    
        //Get estado do Jogador
        bool getEsta_jogando(); 
        //Set estado do Jogador
        void setEsta_jogando(bool esta_jogando); 

        //Get nome do Jogador
        std::string getNome();
        //Set nome do Jogador
        void setNome(std::string nome); 

        //Get numero de fichas do Jogador
        int getFichas(); 
        //Set numero de fichas do Jogador
        void setFichas(int fichas); 

        //Get numero de vitorias do Jogador
        int getNum_vitoria(); 
        //Set numero de vitorias do Jogador
        void setNum_vitoria(int num_vitoria); 

        //Get objeto mao do Jogador
        Mao &getObjeto_mao_jogador();
        //Get vector mao do Jogador
        std::vector<Carta> &getVector_mao_jogador();
    
        //Get tipo de Jogador(Dealer, Small Blind ou Big Blind)
        std::string getTipo();
        //Set tipo de Jogador(Dealer, Small Blind ou Big Blind)
        void setTipo(std::string tipo);
};

#endif