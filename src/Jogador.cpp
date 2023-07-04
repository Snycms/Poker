#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Baralho.h"
#include "Jogador.h"


using namespace std;
using namespace Baralhos;
using namespace Players;

Players::Dealer::Dealer(int id, std::string nome) {
    this->id = id;
    this->nome = nome;
    this->baralho = vector<Carta>();
};

Players::Dealer::~Dealer() {
    this->limparBaralho();
};

void Players::Dealer::limparBaralho(){
    this->baralho.clear();
};
int Players::Dealer::getId() {
    return this->id;
};
string Players::Dealer::getNome() {
    return this->nome;
};
void Players::Dealer::setId(int id) {
    this->id = id;
};
void Players::Dealer::setNome(std::string nome) {
    this->nome = nome;
};
void Players::Dealer::receberBaralho(vector<Carta> baralho) {
    this->baralho = baralho;
};  
vector<Carta> Players::Dealer::exibirCartas(int quantidade) {
    int maximal = min(int(this->baralho.size()), quantidade);
    vector<Carta> cartas = this->baralho;
    cartas.resize(maximal);
    return cartas;
};

Players::Jogador::Jogador(int id, bool bot, std::string nome) {
    this->id = id;
    this->bot = bot;
    this->atividade = true;
    this->nome = nome;
    this->fichas = 100; // Inicialização padrão do valor de fichas.
    this->fichas_apostadas = 0; // Inicialização padrão do valor de fichas.
    this->pontos = 0; //
    this->baralho = vector<Carta>();
};
Players::Jogador::~Jogador() {
    this->baralho.clear();
    this->bot = false;
    this->atividade = true;
    this->fichas = 100; // Inicialização padrão do valor de fichas.
    this->fichas_apostadas = 0;
    this->pontos = 0; //
};
void Players::Jogador::limparBaralho(){
    this->baralho.clear();
};
string Players::Jogador::getNome() {
    return this->nome;
};
int Players::Jogador::getId() {
    return this->id;
};
int Players::Jogador::getPontos() {
    return this->pontos;
};
bool Players::Jogador::getAtividade() {
    return this->atividade;
};
bool Players::Jogador::getBot() {
    return this->bot;
};
int Players::Jogador::getFichas() {
    return this->fichas;
};
int Players::Jogador::getFichasApostadas() {
    return this->fichas_apostadas;
};

void Players::Jogador::setFichasApostadas(int fichas) {
    this->fichas_apostadas = fichas;
};
void Players::Jogador::setPontos( int pontos) {
    this->pontos = pontos;
};
void Players::Jogador::setId( int id) {
    this->id = id;
};
void Players::Jogador::setFichas( int fichas) {
    this->fichas = fichas;
};
void Players::Jogador::setBot( bool bot) {
    this->bot = bot;
};
void Players::Jogador::setAtividade( bool ativadade) {
    this->atividade = ativadade;
};
void Players::Jogador::setNome(std::string nome) {
    this->nome = nome;
};
void Players::Jogador::adicionarFichas(int fichas) {
    this->fichas += fichas;
};
void Players::Jogador::apostarFichas(int fichas) {
    this->fichas -= fichas;
    this->fichas_apostadas += fichas;
};
void Players::Jogador::adicionarPontos(int pontos) {
    this->pontos += pontos;
};
void Players::Jogador::receberBaralho(vector<Carta> baralho) {
    this->baralho = baralho;
};

vector<Carta> Players::Jogador::exibirCartas() {
    return this->baralho;
};
