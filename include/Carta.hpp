#ifndef CARTAS_HPP
#define CARTAS_HPP

#include <string>

class Carta{
    private:
        int _valor;
        std::string _nome;
        std::string _naipe;
        bool _rosto_baixo;

    public:
        //Inicia as cartas
        Carta(int valor, std::string nome, std::string naipe, bool rosto_baixo);
        ~Carta();

        //GETTERS E SETTERS ---------------------------------------

        //Get valor da Carta
        int getValor();
        //Set valor da Carta
        void setValor(int valor);

        //Get nome da Carta
        std::string getNome();

        //Get naipe da Carta
        std::string getNaipe();

        //Get se a Carta esta virada
        bool getRosto_baixo(); 
        //Set se a Carta esta virada
        void setRosto_baixo(bool rosto_baixo);
};

#endif
