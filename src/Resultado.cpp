#ifndef RESULTADO_CPP
#define RESULTADO_CPP


Resultado::Resultado(){
    _numVencedores = 0;
    _montanteGanhador = 0;
    _vencedorPartida = "";
    _vencedores = std::vector<std::string>();
}

Resultado::Resultado(int numVencedores, int montanteGanhador, std::string vencedorPartida, std::vector<std::string> vencedores){
    _numVencedores = numVencedores;
    _montanteGanhador = montanteGanhador;
    _vencedorPartida = vencedorPartida;
    _vencedores = vencedores;
}

Resultado::print(){
    std::cout<< _numVencedores<< " "<<_montanteGanhador<<" "<<_vencedorPartida<<std::endl;
    _vencedores.sort();
    for(int i=0; i<_vencedores.lenght(); ++i){
        std::cout<< _vencedores.get(i)<< std::endl;
    }
}