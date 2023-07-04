#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include "Baralho.h"

using namespace std;
using namespace Baralhos;

Baralhos::Carta::Carta() {
    this->naipe = "";
    this->valor = "";
    this->codigo = -1;
    this->indice = -1;
}

Baralhos::Carta::Carta(std::string naipe, std::string valor, int codigo, int indice) {
    this->naipe = naipe;
    this->valor = valor;
    this->codigo = codigo;
    this->indice = indice;
}

std::string Baralhos::Carta::getNaipe() {
    return this->naipe;
}

std::string Baralhos::Carta::getValor() {
    return this->valor;
}

int Baralhos::Carta::getCodigo() {
    return this->codigo;
}

int Baralhos::Carta::getIndice() {
    return this->indice;
}

void Baralhos::Carta::setNaipe(std::string naipe) {
    this->naipe = naipe;
}

void Baralhos::Carta::setValor(std::string valor) {
    this->valor = valor;
}

void Baralhos::Carta::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Baralhos::Carta::setIndice(int valor) {
    this->indice = valor;
}

std::string Baralhos::Carta::getCarta(){ 
    return this->valor + " de " + this->naipe;
}

std::string Baralhos::Carta::getSimboloCarta(){ 
    std::string simbolo =  "";
    if (this->naipe == "Copas") {
        simbolo = "♥";
    } else if (this->naipe == "Espadas") {
        simbolo = "♠";
    } else if (this->naipe == "Ouros") {
        simbolo = "♦";
    } else if (this->naipe == "Paus") {
        simbolo = "♣";
    }
    return this->valor + " " + simbolo + " | " + this->valor + " de " + this->naipe;
}

bool Baralhos::Carta::operator > (const Carta& str) const {
    return (this->codigo > str.codigo);

};
bool Baralhos::Carta::operator < (const Carta& str) const {
    return (this->codigo < str.codigo);
};

Baralhos::BaralhoTotal::BaralhoTotal() {
    this->iniciarBaralho();
}

Baralhos::BaralhoTotal::~BaralhoTotal() {
    this->todas_cartas.clear();
    this->cartas_usadas = 0;
}

void Baralhos::BaralhoTotal::iniciarBaralho() {
    this->todas_cartas = vector<Carta>();
    this->cartas_usadas = 0;

    std::string naipes[4] = {"Copas", "Espadas", "Ouros", "Paus"};
    int valores_indices[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::string valores[13] = {"2", "3", "4", "5", "6", "7", "8","9", "10", "J", "Q", "K", "A"};
    int codigo = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++, codigo++) {
            this->todas_cartas.push_back(Carta(naipes[i], valores[j], codigo, valores_indices[j]));
        }
    }
    reverse(this->todas_cartas.begin(), this->todas_cartas.end());
}

void Baralhos::BaralhoTotal::embaralhar() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(this->todas_cartas.begin(), this->todas_cartas.end(), generator);
}

vector<Carta> Baralhos::BaralhoTotal::getCartas(int quantidade) {
    vector<Carta> cartas = this->todas_cartas;

    // Resize the vector to the desired sample size
    cartas.resize(quantidade);
    for (Carta carta : cartas) {
        int code = carta.getCodigo();
        this->todas_cartas.erase(std::remove_if(this->todas_cartas.begin(), this->todas_cartas.end(), [code](Carta c) {
            return c.getCodigo() == code;
        }), this->todas_cartas.end());
    }
    this->cartas_usadas += quantidade;
    return cartas;
}

void Baralhos::BaralhoTotal::printBaralho() {
    for (unsigned int i = 0; i < this->todas_cartas.size(); i++) {
        std::cout << this->todas_cartas[i].getCarta() << std::endl;
    }
}

int Baralhos::BaralhoTotal::getCartasRestantes() {
    return this->numero_cartas - this->cartas_usadas; 
}
