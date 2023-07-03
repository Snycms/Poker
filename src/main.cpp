#include "Poker_Game.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

//No poker com 2 jogadores o Dealer também é o Small Blind

int main (){
    std::string opcao_jogo;
    std::cout << "tela inicial" << std::endl;
    std::cin >> opcao_jogo;

    Poker_Game poker;

    while(opcao_jogo == "Novo Jogo"){

        Baralho baralho = poker.getBaralho();
        Jogador jogador = poker.getJogador();
        Computador bot = poker.getBot();

        std::string nome;
        std::cout << "Tela Digite o nome" << std::endl;
        std::cin >> nome;
        jogador.setNome(nome);

        int dificuldade;
        std::cout << "Tela selecione a dificuldade de jogo" << std::endl;
        std::cin >> dificuldade;
        bot.setDificuldade(dificuldade);
        
        //Depois que o jogador escolher a dificuldade jogo comeca
        int proxima_rodada = 0;

        do{
            bool fim_rodada = false;

            do{
                poker.setRodada(proxima_rodada);
                baralho.embaralhar_cartas();
                
                //PARTE 1 (SORTEIO DO DEALER)-------------------------------------------------------------------------

                if(poker.getRodada() == 0){ //Primeira parte dealer é sorteado quando o jogo começa
                    unsigned int semente = time(0);
                    srand(semente);
                    int dealer = (rand() % 2) + 1; //Numero aleatorio (1 ou 2)
                    
                    //Dealer é o jogador e o bot é Small Blind
                    if(dealer == 1){jogador.setTipo("DEALER"); bot.setTipo("BIG BLIND");}
                    //Dealer é o bot e o jogador é o Small Blind
                    else{jogador.setTipo("BIG BLIND"); bot.setTipo("DEALER");}
                }
                else{ //se não, o dealer é trocado
                    if(jogador.getTipo() == "DEALER"){jogador.setTipo("BIG BLIND"); bot.setTipo("DEALER");}
                    else{jogador.setTipo("DEALER"); bot.setTipo("BIG BLIND");}
                }
                
                //FIM PARTE 1-----------------------------------------------------------------------------------------


                //Aposta minima e obrigatória
                const int aposta_minima = 4;
                //Variavel para salvar as apostas dos jogadores
                int aposta_anterior = aposta_minima;


                //PARTE 2 (APOSTAS OBRIGATÓRIAS)----------------------------------------------------------------------

                if(jogador.getTipo() == "DEALER"){
                    aposta_anterior = jogador.apostar_fichas("APOSTAR", aposta_minima/2);
                    poker.adiciona_aposta_POT(aposta_anterior);;
                    aposta_anterior = bot.apostar_fichas("APOSTAR", aposta_minima);
                    poker.adiciona_aposta_POT(aposta_anterior);;
                }
                else{
                    aposta_anterior = bot.apostar_fichas("APOSTAR", aposta_minima/2);
                    poker.adiciona_aposta_POT(aposta_anterior);;
                    aposta_anterior = jogador.apostar_fichas("APOSTAR", aposta_minima);
                    poker.adiciona_aposta_POT(aposta_anterior);;
                }

                //FIM PARTE 2-----------------------------------------------------------------------------------------


                //Parte 3 (Distribui as cartas)-----------------------------------------------------------------------

                //Distribuindo as cartas para Big Blind depois Dealer
                if(jogador.getTipo() == "BIG BLIND"){
                    for(int i=0; i<2; ++i){
                        //Uma carta para o BIG BLIND - Tira do baralho
                        baralho.distribuir_cartas("DAR CARTAS", jogador.getObjeto_mao_jogador());
                        baralho.remover_carta("DAR CARTAS");
                        //Uma carta para o Dealer - Tira do baralho
                        baralho.distribuir_cartas("DAR CARTAS", bot.getObjeto_mao_jogador());
                        baralho.remover_carta("DAR CARTAS");
                    }
                }else{
                    for(int i=0; i<2; ++i){
                        //Uma carta para o Big Blind - Tira do baralho
                        baralho.distribuir_cartas("DAR CARTAS", bot.getObjeto_mao_jogador());
                        baralho.remover_carta("DAR CARTAS");
                        //Uma carta para o Dealer - Tira do baralho
                        baralho.distribuir_cartas("DAR CARTAS", jogador.getObjeto_mao_jogador());
                        baralho.remover_carta("DAR CARTAS");
                    }
                }

                //FIM PARTE 3-----------------------------------------------------------------------------------------
                
                
                //Qtd de vezes que alguem aumentou a aposta (bot precisa dessa variável)
                int qtd_raise_bet = 0;
                //Verifica se o bot aumentou a aposta
                bool aumentou_aposta = false;

                //PARTE 4 (PRÉ-FLOP)----------------------------------------------------------------------------------

                if(jogador.getTipo() == "BIG BLIND"){
                    //Jogador joga primeiro depois o bot------------------------------------
                    std::string tipo_jogada;
                    std::cout << "Escolha a jogada " << std::endl;
                    std::cin >> tipo_jogada;

                    if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                        jogador.dar_check_ou_fold(tipo_jogada);
                    }
                    else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                        //Qtd de fichas que vai apostar
                        if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                            std::cout << "Digite numero de fichas" << std::endl;
                            std::cin >> aposta_anterior;
                        }

                        aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                        poker.adiciona_aposta_POT(aposta_anterior);

                        if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){qtd_raise_bet += 1;}
                    }
                    //Jogador terminou a jogada---------------------------------------------
                    
                    //Vez do bot
                    aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                    poker.adiciona_aposta_POT(aposta_anterior);;
                }
                else{
                    aumentou_aposta = false;
                    //Bot joga primeiro depois o jogador
                    aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                    poker.adiciona_aposta_POT(aposta_anterior);;

                    //Vez jogador -------------------------------------------------------

                    if(aumentou_aposta == true){
                        //JOGADOR NÃO PODE FAZER CHECK
                    }

                    std::string tipo_jogada;
                    std::cout << "Escolha a jogada " << std::endl;
                    std::cin >> tipo_jogada;

                    if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                        jogador.dar_check_ou_fold(tipo_jogada);
                    }
                    else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                        //Qtd de fichas que vai apostar
                        if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                            std::cout << "Digite numero de fichas" << std::endl;
                            std::cin >> aposta_anterior;
                        }

                        aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                        poker.adiciona_aposta_POT(aposta_anterior);
                        qtd_raise_bet += 1;
                    }
                    //Jogador terminou a jogada------------------------------------------
                }
                
                //Verifica se alguém desistiu
                if(jogador.getEsta_jogando() == false){
                    std::cout << "BOT VENCEU" << std::endl;
                    bot.adicionar_fichas(poker.getPOT());
                    break;
                }
                else if(bot.getEsta_jogando() == false){
                    std::cout << "JOGADOR VENCEU" << std::endl;
                    jogador.adicionar_fichas(poker.getPOT());
                    break;
                }
                //FIM PARTE 4-----------------------------------------------------------------------------------------
                    

                //PARTE 5 (FLOP)--------------------------------------------------------------------------------------
                
                baralho.distribuir_cartas("FLOP", jogador.getObjeto_mao_jogador());
                baralho.distribuir_cartas("FLOP", bot.getObjeto_mao_jogador());
                baralho.remover_carta("FLOP");

                if(jogador.getTipo() == "BIG BLIND"){
                    if(jogador.getFichas() > 0){//Só joga se tiver fichas 
                        //Jogador joga primeiro depois o bot------------------------------------
                        std::string tipo_jogada;
                        std::cout << "Escolha a jogada " << std::endl;
                        std::cin >> tipo_jogada;

                        if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                            jogador.dar_check_ou_fold(tipo_jogada);
                        }
                        else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                            //Qtd de fichas que vai apostar
                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                                std::cout << "Digite numero de fichas" << std::endl;
                                std::cin >> aposta_anterior;
                            }

                            aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                            poker.adiciona_aposta_POT(aposta_anterior);

                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){qtd_raise_bet += 1;}
                        }
                        //Jogador terminou a jogada---------------------------------------------
                    }
                    if(bot.getFichas() > 0){
                        //Vez do bot
                        aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                        poker.adiciona_aposta_POT(aposta_anterior);;
                    }
                }
                else{
                    aumentou_aposta = false;
                    
                    if(bot.getFichas() > 0){
                        //Vez do bot
                        aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                        poker.adiciona_aposta_POT(aposta_anterior);;
                    }
                    if(jogador.getFichas() > 0){
                        //Vez do Jogador--------------------------------------------------------
                        if(aumentou_aposta == true){
                            //JOGADOR NÃO PODE FAZER CHECK
                        }

                        std::string tipo_jogada;
                        std::cout << "Escolha a jogada " << std::endl;
                        std::cin >> tipo_jogada;

                        if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                            jogador.dar_check_ou_fold(tipo_jogada);
                        }
                        else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                            //Qtd de fichas que vai apostar
                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                                std::cout << "Digite numero de fichas" << std::endl;
                                std::cin >> aposta_anterior;
                            }

                            aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                            poker.adiciona_aposta_POT(aposta_anterior);

                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){qtd_raise_bet += 1;}
                        }
                        //Jogador terminou a jogada---------------------------------------------
                    }
                }

                //Verifica se alguém desistiu
                if(jogador.getEsta_jogando() == false){
                    std::cout << "BOT VENCEU" << std::endl;
                    bot.adicionar_fichas(poker.getPOT());
                    break;
                }
                else if(bot.getEsta_jogando() == false){
                    std::cout << "JOGADOR VENCEU" << std::endl;
                    jogador.adicionar_fichas(poker.getPOT());
                    break;
                }

                //FIM PARTE 5-----------------------------------------------------------------------------------------


                //PARTE 6 (TURN)--------------------------------------------------------------------------------------

                baralho.distribuir_cartas("TURN", jogador.getObjeto_mao_jogador());
                baralho.distribuir_cartas("TURN", bot.getObjeto_mao_jogador());
                baralho.remover_carta("TURN");

                if(jogador.getTipo() == "BIG BLIND"){
                    if(jogador.getFichas() > 0){
                        //Jogador joga primeiro depois o bot------------------------------------
                        std::string tipo_jogada;
                        std::cout << "Escolha a jogada " << std::endl;
                        std::cin >> tipo_jogada;

                        if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                            jogador.dar_check_ou_fold(tipo_jogada);
                        }
                        else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                            //Qtd de fichas que vai apostar
                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                                std::cout << "Digite numero de fichas" << std::endl;
                                std::cin >> aposta_anterior;
                            }

                            aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                            poker.adiciona_aposta_POT(aposta_anterior);

                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){qtd_raise_bet += 1;}
                        }
                        //Jogador terminou a jogada---------------------------------------------
                    }
                    if(bot.getFichas() > 0){
                        //Vez do bot
                        aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                        poker.adiciona_aposta_POT(aposta_anterior);;
                    }
                }
                else{
                    aumentou_aposta = false;
                    
                    if(bot.getFichas() > 0){
                        //Vez do bot
                        aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                        poker.adiciona_aposta_POT(aposta_anterior);;
                    }
                    if(jogador.getFichas() > 0){
                        //Vez do Jogador--------------------------------------------------------
                        if(aumentou_aposta == true){
                            //JOGADOR NÃO PODE FAZER CHECK
                        }

                        std::string tipo_jogada;
                        std::cout << "Escolha a jogada " << std::endl;
                        std::cin >> tipo_jogada;

                        if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                            jogador.dar_check_ou_fold(tipo_jogada);
                        }
                        else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                            //Qtd de fichas que vai apostar
                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                                std::cout << "Digite numero de fichas" << std::endl;
                                std::cin >> aposta_anterior;
                            }

                            aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                            poker.adiciona_aposta_POT(aposta_anterior);

                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){qtd_raise_bet += 1;}
                        }
                        //Jogador terminou a jogada---------------------------------------------
                    }
                }

                //Verifica se alguém desistiu
                if(jogador.getEsta_jogando() == false){
                    std::cout << "BOT VENCEU" << std::endl;
                    bot.adicionar_fichas(poker.getPOT());
                    break;
                }
                else if(bot.getEsta_jogando() == false){
                    std::cout << "JOGADOR VENCEU" << std::endl;
                    jogador.adicionar_fichas(poker.getPOT());
                    break;
                }
                //FIM PARTE 6-----------------------------------------------------------------------------------------


                //PARTE 7 (RIVER)-------------------------------------------------------------------------------------

                baralho.distribuir_cartas("RIVER", jogador.getObjeto_mao_jogador());
                baralho.distribuir_cartas("RIVER", bot.getObjeto_mao_jogador());
                baralho.remover_carta("RIVER");

                if(jogador.getTipo() == "BIG BLIND"){
                    if(jogador.getFichas() > 0){
                        //Jogador joga primeiro depois o bot------------------------------------
                        std::string tipo_jogada;
                        std::cout << "Escolha a jogada " << std::endl;
                        std::cin >> tipo_jogada;

                        if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                            jogador.dar_check_ou_fold(tipo_jogada);
                        }
                        else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                            //Qtd de fichas que vai apostar
                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                                std::cout << "Digite numero de fichas" << std::endl;
                                std::cin >> aposta_anterior;
                            }

                            aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                            poker.adiciona_aposta_POT(aposta_anterior);

                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){qtd_raise_bet += 1;}
                        }
                        //Jogador terminou a jogada---------------------------------------------
                    }
                    if(bot.getFichas() > 0){
                        //Vez do bot
                        aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                        poker.adiciona_aposta_POT(aposta_anterior);;
                    }
                }
                else{
                    aumentou_aposta = false;
                    
                    if(bot.getFichas() > 0){
                        //Vez do bot
                        aposta_anterior = bot.fazer_jogada(poker.getPOT(), qtd_raise_bet, aposta_anterior, aumentou_aposta);
                        poker.adiciona_aposta_POT(aposta_anterior);;
                    }
                    if(jogador.getFichas() > 0){
                        //Vez do Jogador--------------------------------------------------------
                        if(aumentou_aposta == true){
                            //JOGADOR NÃO PODE FAZER CHECK
                        }

                        std::string tipo_jogada;
                        std::cout << "Escolha a jogada " << std::endl;
                        std::cin >> tipo_jogada;

                        if(tipo_jogada == "CHECK" || tipo_jogada == "FOLD"){
                            jogador.dar_check_ou_fold(tipo_jogada);
                        }
                        else if(tipo_jogada == "CALL" || tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){
                            //Qtd de fichas que vai apostar
                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR"){
                                std::cout << "Digite numero de fichas" << std::endl;
                                std::cin >> aposta_anterior;
                            }

                            aposta_anterior = jogador.apostar_fichas(tipo_jogada, aposta_anterior);
                            poker.adiciona_aposta_POT(aposta_anterior);

                            if(tipo_jogada == "APOSTAR" || tipo_jogada == "AUMENTAR" || tipo_jogada == "APOSTAR TUDO"){qtd_raise_bet += 1;}
                        }
                        //Jogador terminou a jogada---------------------------------------------
                    }
                }

                //Verifica se alguém desistiu
                if(jogador.getEsta_jogando() == false){
                    std::cout << "BOT VENCEU" << std::endl;
                    bot.adicionar_fichas(poker.getPOT());
                    break;
                }
                else if(bot.getEsta_jogando() == false){
                    std::cout << "JOGADOR VENCEU" << std::endl;
                    jogador.adicionar_fichas(poker.getPOT());
                    break;
                }

                //FIM PARTE 7)----------------------------------------------------------------------------------------


                //PARTE 8 (SHOWDOWN)----------------------------------------------------------------------------------

                std::string resultado = poker.showdown(jogador, bot);
                std::cout << resultado << std::endl;

                //FIM PARTE 8----------------------------------------------------------------------------------------

                fim_rodada = true;

            }while(fim_rodada == false);

            //PARTE 9 (LIMPA MESA)-------------------------------------------------------------------------------

            baralho = poker.limpar_mesa(baralho, jogador, bot);

            //FIM PARTE 9----------------------------------------------------------------------------------------

            proxima_rodada += 1;

        }while(jogador.getFichas() > 0 || bot.getFichas() > 0);

        if(jogador.getFichas() == 0){bot.adicionar_vitoria();}
        else if(bot.getFichas() == 0){jogador.adicionar_vitoria();}

        std::cin >> opcao_jogo;
    }   

    if(opcao_jogo == "Sair"){
        poker.~Poker_Game();
        EXIT_SUCCESS;}
}
