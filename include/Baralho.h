
#ifndef BARALHO_H
#define BARALHO_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace Baralhos {
    class Carta {
        private:
            std::string naipe;
            std::string valor;
            int codigo;
            int indice;
        public:
            Carta();
            Carta(std::string naipe, std::string valor, int codigo, int indice);
            std::string getNaipe();
            std::string getValor();
            int getIndice();
            int getCodigo();
            void setNaipe(std::string naipe);
            void setIndice(int valor);
            void setValor(std::string valor);
            void setCodigo(int codigo);
            std::string getCarta();
            std::string getSimboloCarta();
            bool operator > (const Carta& str) const;
            bool operator < (const Carta& str) const;
    };

    class BaralhoTotal {
        private:
            int numero_cartas = 52;
            vector<Carta> todas_cartas;
            int cartas_usadas = 0;
        public:
            BaralhoTotal();
            ~BaralhoTotal();
            void iniciarBaralho();
            void embaralhar();
            int getNumeroCartas( );
            int getCartasRestantes( );
            void printBaralho();
            std::vector<Carta> getCartas(int quantidade);
    };
}
#endif