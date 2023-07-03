#ifndef COMPUTADOR_CPP
#define COMPUTADOR_CPP

#include "Computador.hpp"

#include <cstdlib>
#include <ctime>

Computador::Computador(){
    setDificuldade(0);

    setEsta_jogando(true);
    setNome("");
    setFichas(100);
    Mao _mao;
    setNum_vitoria(0);
    setTipo("");

    std::string listas_nomes_bot[] = {"Enzo", "Helena", "Miguel", "Alice", "Arthur", "Laura", "Gael", "Valentina", "Heitor", "Sophia"};

    unsigned int semente = time(0);
    srand(semente);
    int nome_bot = rand() % 10;

    setNome(listas_nomes_bot[nome_bot]);

}


//fazer_jogada(int &pot, int qtd_raise_bet, qtd_jogadores_presentes, qtd_nao_jogaram, int aposta_anterior)

int Computador::fazer_jogada(int pot, int &qtd_raise_bet, int aposta_anterior, bool &aumentou_aposta){
    //Jogador aleatório
    if(getDificuldade() == 1){
        unsigned int semente = time(0);
        srand(semente);
        int jogada = (rand() % 6) + 1;

        if(jogada == 1){dar_check_ou_fold("DESISTIR"); return 0;}

        else if(jogada == 2){return apostar_fichas("CALL", aposta_anterior);}

        else if(jogada == 3){
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("AUMENTAR", 3*aposta_anterior);
        }
        else if(jogada == 4){
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("AUMENTAR", 12*aposta_anterior);
        }
        else if(jogada == 5){
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("AUMENTAR", 33*aposta_anterior);
        }
        else{
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("APOSTAR TUDO", aposta_anterior);
        }
    }

    //Relação de Jean Rachlin e Gary Higgins
    //Relação depende das variaveis POT(soma de todas as apostas), qtd_raise_bet(numero de vezes que alguem aumentou ou apostou)
    //qtd_jogadores_presentes(2), qtd_nao_jogaram(1), raise(aposta minima para continuar = aposta anterior)
    //qtd_jogadores_presentes = 2, qtd_nao_jogaram = 1
    else if(getDificuldade() == 2){;

        float t = 0.01; //Determina a agressividade do bot (Menor mais agressivo) 
        float v = pot / ((qtd_raise_bet+1) * 2 * 1 * aposta_anterior);

        if(v < t){dar_check_ou_fold("DESISTIR"); return 0;}

        else if(v < 20*t){return apostar_fichas("CALL", aposta_anterior);}

        else if(v < 50*t){
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("AUMENTAR", 2*aposta_anterior);
        }
        else if(v < 100*t){
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("AUMENTAR", 10*aposta_anterior);
        }
        else if(v < 1000*t){
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("AUMENTAR", 30*aposta_anterior);
        }
        else{
            qtd_raise_bet += 1;
            aumentou_aposta = true;
            return apostar_fichas("APOSTAR TUDO", aposta_anterior);
        }
    }

    else if(getDificuldade() == 3){}
}

//GETTERS E SETTERS ---------------------------------------

int Computador::getDificuldade(){return _dificuldade;}
void Computador::setDificuldade(int dificuldade){_dificuldade = dificuldade;}


#endif
