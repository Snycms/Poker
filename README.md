#Index<br>
1.[Descrição](#Descrição)

2.[Funcionalidades](#funcionalidades) 

3.[Tecnologias Utilizadas](#tecnologias)

4.[CRC Cards](#crccards)

5.[Status](#status)

<h1 id = Descrição>Descrição</h1>  

Projeto feito para colocar em prática os conhecimentos adquiridos na disciplina de Programação e Desenvolvimento de Software da UFMG. Consiste em um jogo de Texas Holdem Poker, feito para até quatro jogadores, com um bot que faz contagem de cartas para determinar a melhor jogada.<br><br>

Projeto executado por:<br><br>

Daniel Moreira dos Santos<br>
Pedro Henrique Esteves Dalla-Lana<br>
Sarah Aline Caetano Cruz<br>
Sanny Cristiane Moreira de Sales

<br><br><br>
<h1 id = funcionalidades>Funcionalidades</h1>

<h2>1- Guardar nome e valores de aposta de jogadores.<br></h2>
<br>
Para cada jogador da rodada, o sistema guarda o nome, a mão e os valores de aposta<br><br>

<h2>2- Apostar, desistir, continuar</h2><br>
Em cada rodada, cada jogador tem a opção de desistir e perder o valor apostado, continuar com a aposta feita ou aumentar a aposta.<br><br>

<h2>3- Comparar cartas e sets de cartas</h2> <br>
As funções comparam as cartas da mão e da mesa e selecionam a melhor combinação feita com até 5 delas.<br><br>


<h1 id = Tecnologias>Tecnologias Utilizadas</h1>

<h5>C++</h4>
<br><br>

<h1 id = projeto> Projeto </h1><br>



<h1 id = crccards> CRC Cards </h1><br>

![](Images/classe_carta.png)

<br> Compara valores uma a uma e deixa a carta virada com o rosto para cima ou para baixo<br><br>

![](Images/classe_baralho.png)

 Distribui as cartas aos jogadores, cria um novo baralho a cada jogo iniciado, embaralha as cartas e mostra a carta do topo<br><br>

![](Images/classe_mão.png)

<br>Compara a mão do jogador e adiciona uma carta à mão, caso necessário<br><br>

![](Images/classe_jogador.png)
<br> Fazer uma aposta, comparar mão do jogador com cartas na mesa, igualar a aposta, dobrar a aposta, limpar a mesa (caso bot) mostrar resultado<br><br>

![](Images/classe_computador.png)

<br> Fazer o movimento do bot de acordo com a dificuldade escolhida <br><br>

![](Images/classe_jogo.png)
<br>Inicia o jogo e define a dificuldade do bot<br><br>







<h1 id = status>Status</h1><br>
Em andamento.








