#ifndef MAO_CPP
#define MAO_CPP

#include "Mao.hpp"

#include <algorithm>
//TESTE ONLINE GDB
#include <iostream>


Mao::Mao() : _mao() {}


Mao::~Mao(){}



void Mao::adiciona_carta(Carta carta){
    
    _mao.push_back(carta);
    
}




void Mao::ordena_cartas(){
    std::sort(_mao.begin(), _mao.end());
}


Carta Mao::maior_carta(){
    ordena_cartas();
    Carta maior = *(_mao.end());
    return maior;
}

Carta Mao:: menor_carta(){
    ordena_cartas();
    Carta menor = _mao.back();
    return menor;
}

std::string Mao::getHandRank(){
    std::unordered_map<std::string, int> cardCount;

    for(int i = 0; i < _mao.size(); i++){
        if(cardCount.find(_mao.at(i).getNaipe()) == cardCount.end()){
            cardCount[_mao.at(i).getNaipe()] = 1;
        }
        
        else cardCount[_mao.at(i).getNaipe()]++;
    }

    int parCount = 0;
    int trincaCount = 0;
    int quadraCount = 0;

    for (const auto& count : cardCount) {
        if (count.second == 2) {
            parCount++;
        } else if (count.second == 3) {
            trincaCount++;
        } else if (count.second == 4) {
            quadraCount++;
        }
    }

    if (quadraCount > 0) {
        return "quadra";
    } else if (trincaCount > 0 && parCount > 0) {
        return "fullHouse";
    } else if (trincaCount > 0) {
        return "trinca";
    } else if (parCount >= 2) {
        return "doisPares";
    } else if (parCount == 1) {
        return "par";
    } else {
        return "cartaAlta";
    }

     
}

std::string Mao::flush(){
    if (!_mao.empty()){
        Carta menor = menor_carta();
        for (int i = 0; i < _mao.size(); ++i){
            Carta atual = _mao.at(i);
            if (menor.getNaipe() != atual.getNaipe()){
                return false;
            }
        }
        return "flush";
    }
    return "cartaAlta";
}

std::string Mao::straight() {
    if (_mao.empty() || _mao.size() <= 2) {
        return false;
    }
    Carta atual = _mao.at(0);
    Carta prox = _mao.at(1);

    for (int i = 0; i < _mao.size() - 1; ++i) {
        
        atual = _mao.at(i);
        
        if(i + 1 < _mao.size()){
            prox = _mao.at(i + 1);
        }

        if (atual.getValor()+ 1 != prox.getValor()) {
            return "cartaAlta";
        }
    }

    return "straight";
}

std::string Mao::straightFlush() {
    if(straight() == "straight" && flush() == "flush") return "straightFlush";
    else return false;
}

std::string Mao::Royal_flush() {
    if (flush() != "flush"){
        return "cartaAlta";
    }
    std::vector <std::string> sequencia = {"10", "J", "Q", "K", "A"};
    for (int i=0; i<_mao.size() -1; ++i){
        Carta atual = _mao.at(i);
        if(atual.getNaipe() != sequencia[i]){
            return 0;
        } 
    }
    return "royalFlush";
}





/*std::string Mao::valor_mao(){
    if(royal_flush_e_straight_flush() != 0){
        int valor = royal_flush_e_straight_flush();
        if(valor >= 270){
            std::string mao = "Royal Flush: " + std::to_string(valor);
            return mao;}
        else{
            std::string mao = "Straight Flush: " + std::to_string(valor);
            return mao;}
    }
    else if(quadra_e_fullHouse() != 0){
        int valor = quadra_e_fullHouse();
        if(valor >= 210){
            std::string mao = "Quadra: " + std::to_string(valor);
            return mao;}
        else{
            std::string mao = "Full House: " + std::to_string(valor);
            return mao;}
    }
    else if(flush() != 0){
        int valor = flush();
        std::string mao = "Flush: " + std::to_string(valor);
        return mao;
    }
    else if(straight() != 0){
        int valor = straight();
        std::string mao = "Straight: " + std::to_string(valor);
        return mao;
    }
    else if(trinca_doisPares_par_cartaAlta() != 0){
        int valor = trinca_doisPares_par_cartaAlta();
        if(valor >= 90 && valor < 120){
            std::string mao = "Trinca: " + std::to_string(valor);
            return mao;}
        else if(valor >= 60 && valor < 90){
            std::string mao = "Dois Pares: " + std::to_string(valor);
            return mao;}
        else if(valor >= 30 && valor < 60){
            std::string mao = "Um par: " + std::to_string(valor);
            return mao;}
        else if(valor < 30){
            std::string mao = "Carta Alta: " + std::to_string(valor);
            return mao;}
    }
}

//POSSIVEIS MAOS-----------------------------------------------------------------------------------------------------

int Mao::royal_flush_e_straight_flush(){
    std::vector<Carta> cartas_jogador = {_mao.front(), _mao.at(1)}; //Cartas recebidas pelo jogador
    std::sort(cartas_jogador.begin(), cartas_jogador.end(), ordena_mao_valor); //Ordena maior para menor

    std::vector<Carta> mao_mesa = _mao; //Cartas da mesa
    std::sort(mao_mesa.begin(), mao_mesa.end(), ordena_mao_valor); //Ordena maior para menor
    
    //Se a 1° for As ele terá valor 0, para uma sequencia de As, 2, 3, 4, 5
    if(mao_mesa.front().getValor() == 13){
        Carta copia_aux = mao_mesa.front();
        copia_aux.setValor(0);
        mao_mesa.push_back(copia_aux);
        copia_aux.~Carta();
    }
    
    
    std::sort(mao_mesa.begin(), mao_mesa.end(), ordena_mao_valor); //Ordena de novo
    
    int Royal_Flush[5] = {13, 12, 11, 10, 9}; //Array auxiliar
    int Straight_Flush[5]; 
    std::vector<Carta> mao_aux; //Criando a mao com as cartas da mao, se der certo iguala a mao do jogador
    
    int confere_royal_flush;
    int confere_straight_flush;
    int it; //Iterator

    if(mao_mesa.front().getValor() > 4){ //Carta alta sempre tem que ser maior que 4 - menor sequencia possivel é 4 ,3 ,2 ,1 ,0 -> (5, 4, 3, 2, As)
        for(it=0; it<4; ++it){
            confere_royal_flush = 0;
            confere_straight_flush = 0;
            Straight_Flush[0] = mao_mesa.at(it).getValor();

            for(int j=1; j<5; ++j){Straight_Flush[j] = Straight_Flush[0] - j;} //Criando um Straight Flush para comparar

            int *pri_elemento = std::find(Straight_Flush, Straight_Flush + 5, cartas_jogador.front().getValor());
            int *seg_elemento = std::find(Straight_Flush, Straight_Flush + 5, cartas_jogador.back().getValor()); 
            
            mao_aux = cartas_jogador; 
            
            if(pri_elemento != Straight_Flush + 5 && seg_elemento != Straight_Flush + 5){
                for(int j=0; j<5; ++j){
                    if(mao_mesa.at(it + j).getValor() == Royal_Flush[j] && mao_mesa.at(it).getNaipe() == mao_mesa.at(it + j).getNaipe()){
                        confere_royal_flush += 1;
                        mao_aux.push_back(mao_mesa.at(j));
                    }
                    
                    else if(mao_mesa.at(it + j).getValor() == Straight_Flush[j] && mao_mesa.at(it).getNaipe() == mao_mesa.at(it + j).getNaipe()){ 
                        mao_aux.push_back(mao_mesa.at(j));
                        confere_straight_flush += 1;}
                        
                    else{break;}
                }
            }else{continue;}
            
            if(confere_royal_flush == 5){
                int valor_mao = 270 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
                _mao = mao_aux;
                mao_aux.clear();
                mao_mesa.clear();
                cartas_jogador.clear();
                return valor_mao;
            }
            if(confere_straight_flush == 5){ //Deleta todos vector's e retorna o valor do Straight Flush
                int valor_mao = 240 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
                _mao = mao_aux;
                mao_aux.clear();
                mao_mesa.clear();
                cartas_jogador.clear();
                return valor_mao;
            }
            else{continue;}
        }
    }
    
    else{cartas_jogador.clear(); mao_mesa.clear(); mao_aux.clear(); return 0;} //Deleta todos vector's e retorna o valor 0
    //Se ja fez todas iteracoes possiveis e o confere_sequencia menor que 5, jogador nao tem um Straight Flush - Deleta todos vector's e retorna o valor 0
    if(it == 4 && confere_straight_flush < 5){cartas_jogador.clear(); mao_mesa.clear(); mao_aux.clear(); return 0;} 
}

int Mao::quadra_e_fullHouse(){
    std::vector<Carta> cartas_jogador = {_mao.front(), _mao.at(1)};//Cartas recebidas pelo jogador
    std::sort(cartas_jogador.begin(), cartas_jogador.end(), ordena_mao_valor); //Ordena maior para menor

    std::vector<Carta> mao_mesa = {_mao.begin()+2, _mao.end()}; //Cartas da mesa
    std::sort(mao_mesa.begin(), mao_mesa.end(), ordena_mao_valor); //Ordena maior para menor
    
    std::vector<Carta> mao_aux;
    int confere_um = 0;
    int confere_dois = 0;
    int it; //iterator
    
    mao_aux = cartas_jogador;
    
    for(int j=0; j<5; ++j){
        if(mao_aux.at(0).getValor() == mao_mesa.at(j).getValor()){
            mao_aux.push_back(mao_mesa.at(j));
            confere_um += 1;
        }
        else if(mao_aux.at(1).getValor() == mao_mesa.at(j).getValor()){
            mao_aux.push_back(mao_mesa.at(j));
            confere_dois += 1;
        }
        else{continue;}
    }
    
    if(confere_um == 4 || confere_dois == 4){//Se for uma Quadra iguala a mao_aux a _mao, deleta os vector's e retorna o valor + o valor das duas cartas
        int valor_mao = 210 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
        _mao = mao_aux;
        mao_aux.clear();
        mao_aux.clear();
        cartas_jogador.clear();
        return valor_mao;
    }
    else if(confere_um == 3 && confere_dois == 2 || confere_um == 2 && confere_dois == 3){ //Se for uma Trinca iguala a mao_aux a _mao, deleta os vector's e retorna o valor + o valor das duas cartas
        int valor_mao = 180 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
        mao_aux.clear();
        mao_aux.clear();
        cartas_jogador.clear();
        return valor_mao;
    }
    else{mao_aux.clear(); mao_aux.clear(); cartas_jogador.clear(); return 0;} //Deleta todos vector's e retorna 0
}

int Mao::flush(){
    std::vector<Carta> cartas_jogador = {_mao.front(), _mao.at(1)};//Cartas recebidas pelo jogador
    std::sort(cartas_jogador.begin(), cartas_jogador.end(), ordena_mao_valor); //Ordena maior para menor

    std::vector<Carta> mao_mesa = {_mao.begin()+2, _mao.end()}; //Cartas da mesa
    std::sort(mao_mesa.begin(), mao_mesa.end(), ordena_mao_valor); //Ordena maior para menor
    
    std::vector<Carta> mao_aux = cartas_jogador;
    int confere_flush = 0;
    
    if(cartas_jogador.front().getNaipe() == cartas_jogador.back().getNaipe()){
        for(int i=0; i<5; ++i){
            if(cartas_jogador.front().getNaipe() == mao_mesa.at(i).getNaipe()){
                confere_flush += 1;
                mao_aux.push_back(mao_mesa.at(i));
            }else{continue;}
        }
        if(confere_flush == 5 && mao_aux.size() == 5){ 
            int valor_mao = 150 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
            _mao = mao_aux;
            mao_aux.clear();
            mao_mesa.clear();
            cartas_jogador.clear();
            return valor_mao;
        }
    }
    else{cartas_jogador.clear(); mao_mesa.clear(); mao_aux.clear(); return 0;}
    
    if(confere_flush == 5 && mao_aux.size() < 5){cartas_jogador.clear(); mao_mesa.clear(); mao_aux.clear(); return 0;}
    else{cartas_jogador.clear(); mao_mesa.clear(); mao_aux.clear(); return 0;}
}
    
int Mao::straight(){
    std::vector<Carta> cartas_jogador = {_mao.front(), _mao.at(1)}; //Cartas recebidas pelo jogador
    std::sort(cartas_jogador.begin(), cartas_jogador.end(), ordena_mao_valor); //Ordena maior para menor

    std::vector<Carta> mao_mesa = _mao; //Cartas da mesa
    std::sort(mao_mesa.begin(), mao_mesa.end(), ordena_mao_valor); //Ordena maior para menor
    
    std::vector<Carta> mao_aux = cartas_jogador;

    if(mao_mesa.front().getValor() == 13){
        Carta copia_aux = mao_mesa.front();
        copia_aux.setValor(0);
        mao_mesa.push_back(copia_aux); //Se a 1° for As cria uma copia, para uma possivel sequencia de As, 2, 3, 4, 5, e adiciona no vector com o valor 0
        copia_aux.~Carta();
    }

    int confere_sequencia;
    int Straight[5]; 
    int it; //Iterator

    if(mao_mesa.front().getValor() > 4){ //Carta alta sempre tem que ser maior que 4 - menor sequencia possivel é 4 ,3 ,2 ,1 ,0 -> (5, 4, 3, 2, As)
        for(it=0; it<4; ++it){
            confere_sequencia = 0;

            Straight[0] = mao_mesa.at(it).getValor();
            for(int j=1; j<5; ++j){Straight[j] = Straight[0] - j;} //Criando um Straight para comparar
            
            int *pri_elemento = std::find(Straight, Straight + 5, cartas_jogador.front().getValor());
            int *seg_elemento = std::find(Straight, Straight + 5, cartas_jogador.back().getValor()); 
            
            if(pri_elemento != Straight + 5 && seg_elemento != Straight + 5){
                for(int j=0; j<5; ++j){
                    if(mao_mesa.at(it + j).getValor() == Straight[j]){ 
                        confere_sequencia += 1;
                        mao_aux.push_back(mao_mesa.at(it + j));
                    }
                    else{break;}
                }
            }else{continue;}
            //Se for verdadeiro deleta todos vector's e retorna o valor do Straight + o valor das cartas do jogador
            if(confere_sequencia == 5 && mao_aux.size() == 5){
                int valor = 120 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
                _mao = mao_aux;
                mao_aux.clear();
                mao_mesa.clear();
                cartas_jogador.clear();
                return valor;
            } 
            else{continue;}
        }
    }
    else{mao_aux.clear(); cartas_jogador.clear(); mao_mesa.clear(); return 0;}
    //Se ja fez todas iteracoes possiveis e o confere_sequencia menor que 5, jogador nao tem um Straight - Deleta todos vector's e retorna o valor 0
    if(it == 4 && confere_sequencia < 5){mao_aux.clear(); cartas_jogador.clear(); mao_mesa.clear(); return 0;}
}

int Mao::trinca_doisPares_par_cartaAlta(){
    std::vector<Carta> cartas_jogador = {_mao.front(), _mao.at(1)};//Cartas recebidas pelo jogador
    std::sort(cartas_jogador.begin(), cartas_jogador.end(), ordena_mao_valor); //Ordena maior para menor

    std::vector<Carta> mao_aux = _mao;

    std::vector<Carta> trinca_doisPares_par_cartaAlta;

    int confere_um = 1; //Tenho 1 carta, vou conferir se tenho mais
    int confere_dois = 1; //Tenho 1 carta, vou conferir se tenho mais
    int it; //iterator

    for(it = 0; it<6; ++it){
        for(int i=0; i<7; ++i){
            if(mao_aux.at(it).getNaipe() != mao_aux.at(i).getNaipe() && mao_aux.at(it).getValor() == mao_aux.at(i).getValor()){
                trinca_doisPares_par_cartaAlta.push_back(mao_aux.at(i));
                confere_um += 1;
            }
            else if(mao_aux.at(it+1).getNaipe() != mao_aux.at(i).getNaipe() && mao_aux.at(it).getValor() == mao_aux.at(i).getValor()){
                trinca_doisPares_par_cartaAlta.push_back(mao_aux.at(i));
                confere_dois += 1;
            }
            else{continue;}
        }
        int tamanho = trinca_doisPares_par_cartaAlta.size();
        int Valores[tamanho];
        std::string Naipes[tamanho];

        for(int j=0; j<tamanho; ++j){
            Valores[j] = trinca_doisPares_par_cartaAlta.at(j).getValor();
            Naipes[j] =  trinca_doisPares_par_cartaAlta.at(j).getNaipe();
        }

        int *pri_confere_valor_presente = std::find(Valores, Valores + tamanho, cartas_jogador.front().getValor());
        int *seg_confere_valor_presente = std::find(Valores, Valores + tamanho, cartas_jogador.back().getValor()); 

        if(cartas_jogador.front().getNaipe() == (*std::find(Naipes, Naipes + tamanho, cartas_jogador.front().getNaipe())) && cartas_jogador.back().getNaipe() == (*std::find(Naipes, Naipes + tamanho, cartas_jogador.back().getNaipe())) && pri_confere_valor_presente != Valores + tamanho && seg_confere_valor_presente != Valores + tamanho){
            if(confere_um == 3 || confere_dois == 3){
            int valor_mao = 90 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
            _mao = trinca_doisPares_par_cartaAlta;
            trinca_doisPares_par_cartaAlta.clear();
            mao_aux.clear();
            cartas_jogador.clear();
            return valor_mao;
            }
            else if(confere_um == 2 && confere_dois == 2){
                int valor_mao = 60 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
                _mao = trinca_doisPares_par_cartaAlta;
                mao_aux.clear();
                trinca_doisPares_par_cartaAlta.clear();
                cartas_jogador.clear();
                return valor_mao;
            }
            else if(confere_dois == 2 || confere_um == 2){
                int valor_mao = 30 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
                _mao = trinca_doisPares_par_cartaAlta;
                mao_aux.clear();
                trinca_doisPares_par_cartaAlta.clear();
                cartas_jogador.clear();
                return valor_mao;
            }
            else{
                int valor_mao = 0 + cartas_jogador.front().getValor() + cartas_jogador.back().getValor();
                _mao = trinca_doisPares_par_cartaAlta;
                mao_aux.clear();
                trinca_doisPares_par_cartaAlta.clear();
                cartas_jogador.clear();
                return valor_mao;
            }
        }else{continue;}
    }
    if(it == 6 && trinca_doisPares_par_cartaAlta.size() > 5){mao_aux.clear(); trinca_doisPares_par_cartaAlta.clear(); cartas_jogador.clear(); return 0;}
}

//-------------------------------------------------------------------------------------------------------------------


//TESTE ONLINE GDB
void Mao::exibe_mao(){
    std::cout << "Sua mao: " << std::endl;
    for(std::vector<Carta>::iterator it = _mao.begin(); it != _mao.end(); ++it){
        it->exibe_carta();}
    std::cout << std::endl;
}

//GETTERS E AUXILIARES ---------------------------------------

bool Mao::ordena_mao_valor(Carta x, Carta y){return (x.getValor() > y.getValor());}

std::vector<Carta> &Mao::getMao(){return _mao;}*/


#endif