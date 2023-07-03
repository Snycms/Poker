#ifndef RESULTADO_H
#define RESULTADO_H

#include <vector>
#include "jogador.h"

class Resultado{
protected:
    int _numVencedores;
    int _montanteGanhador;
    std::string _vencedorPartida;
    std::vector<std::string> _vencedores;

public:
    Resultado();
    Resultado(int numVencedores, int montanteGanhador, std::string vencedorPartida, std::vector<std::string> vencedores);
    

    int getNumVencedores() const {return _numVencedores; }
    int getMontanteGanhador() const { return _montanteGanhador; }
    std::string getVencedorPartida() const {return _vencedorPartida; }
    std::vector<std::string> getVencedores() const { return _vencedores; }
    void setNumVencedores(int numVencedores) {_numVencedores = nujmVencedores; }
    void setMontanteGanhador(int montanteGanhador) {_montanteGanhador; }
    void setVencedorPartida(std::string vencedorPartida) {_vencedorPartida = vencedorPartida; }
    void setVencedores (std::vector<std::string> vencedores) { _vencedores = vencedores; }

    void print();

}