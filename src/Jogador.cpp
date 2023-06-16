#ifndef JOGADOR_CPP
#define JOGADOR_CPP

#include "Jogador.hpp", 

#include <iostream>

Jogador::Jogador(){
    setEsta_jogando(true);
    setNome("");
    setFichas(100);
    Mao _mao;
    setNum_vitoria(0);
    setTipo("");
}
        
Jogador::~Jogador(){getObjeto_mao_jogador().~Mao();}

//Acoes que os jogadores podem realizar-----------------------------
        
int Jogador::check_desistir(std::string acao, int jogador_atual){
    if(acao == "DESISTIR"){
        setEsta_jogando(false);
        return jogador_atual + 1;
    }
    else if(acao == "CHECK"){return jogador_atual + 1;}
}

int Jogador::aposta(std::string tipo_aposta, int valor_aposta){
    //Aposta normal
    
    switch(tipo_aposta){

        case "Aposta":
        setFichas(getFichas() - valor_aposta);
        return valor_aposta;
        break;

        case "Aumentar":
        setFichas(getFichas() - valor_aposta);
        return valor_aposta;
        break;

        case "CALL":
        setFichas(getFichas() - valor_aposta);
        return valor_aposta;
        break;

        case "APOSTAR TUDO":
        valor_aposta = getFichas();
        setFichas(0);
        return valor_aposta;
        break;

    }
    /*/if(tipo_aposta == "Aposta"){
        setFichas(getFichas() - valor_aposta);
        return valor_aposta;
    }
    //Aumenta a aposta
    else if(tipo_aposta == "Aumentar"){
        setFichas(getFichas() - valor_aposta);
        return valor_aposta;
    }
    //Aposta mesma quantidade que o ultimo jogador
    else if(tipo_aposta == "CALL"){
        setFichas(getFichas() - valor_aposta);
        return valor_aposta;
    }
    //All-in(Aposta tudo)
    else if(tipo_aposta == "APOSTAR TUDO"){
        valor_aposta = getFichas();
        setFichas(0);
        return valor_aposta;
    }*/
}
//-------------------------------------------------------------------

void Jogador::limpar_mesa(){}

//TESTE GDB ONLINE

void Jogador::exibe_jogador(){
    std::cout << "Esta jogando: " << getEsta_jogando() << std::endl;
    std::cout << "Nome: " << getNome() << std::endl;
    std::cout << "Fichas: "<< getFichas() << std::endl;
    std::cout << "Sua mao: " << std::endl;
    _mao.exibe_mao();
    std::cout << "Vitorias: " << getNum_vitoria() << std::endl;
    std::cout << "Tipo: " << getTipo();
    std::cout << std::endl;
}

//GETTERS E SETTERS ---------------------------------------

bool Jogador::getEsta_jogando(){return _esta_jogando;} 
void Jogador::setEsta_jogando(bool esta_jogando){_esta_jogando = esta_jogando;} 
        
std::string Jogador::getNome(){return _nome;}
void Jogador::setNome(std::string nome){_nome = nome;} 

int Jogador::getFichas(){return _fichas;} 
void Jogador::setFichas(int fichas){_fichas = fichas;} 

Mao &Jogador::getObjeto_mao_jogador(){return _mao;}
std::vector<Carta> &Jogador::getVector_mao_jogador(){return _mao.getMao();}

int Jogador::getNum_vitoria(){return _num_vitoria;} 
void Jogador::setNum_vitoria(int num_vitoria){_num_vitoria = num_vitoria;} 

std::string Jogador::getTipo(){return _tipo;} 
void Jogador::setTipo(std::string tipo){_tipo = tipo;}

#endif
