#ifndef COMPUTADOR_HPP
#define COMPUTADOR_HPP

#include "Jogador.hpp"

class Computador: public Jogador{
    private:
        int _dificuldade;
    
    public: 
        Computador(int dificuldade);
        
        ~Computador();

        void fazer_jogada();

        //GETTERS E SETTERS ---------------------------------------

        //Get dificuldade do computador
        int getDificuldade();
        //Set dificuldade do computador
        void setDificuldade(int dificuldade);
};

#endif