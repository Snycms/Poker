#ifndef COMPUTADOR_CPP
#define COMPUTADOR_CPP

#include "Computador.hpp"

Computador::Computador(int dificuldade){
    setDificuldade(dificuldade);
    }

Computador::~Computador(){}

void Computador::fazer_jogada(){
    if(getDificuldade() == 1){}
    else if(getDificuldade() == 2){}
    else if(getDificuldade() == 3){}
}

//GETTERS E SETTERS ---------------------------------------

int Computador::getDificuldade(){
    return _dificuldade;
    }

void Computador::setDificuldade(int dificuldade){
    _dificuldade = dificuldade;
    }

#endif