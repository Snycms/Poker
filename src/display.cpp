#include <iostream>
#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>
#include <locale.h>
#include <ncursesw/ncurses.h>

#include "display.h"

using namespace std;
//Construtor
  display::display(void) {
// Inicializacao do terminal 
  // Necessário para exibir os naipes das cartas, combinado com UTF-8 configurado no terminal.  
    setlocale(LC_ALL,"en_US.utf-8");

  //nicializa tela ncurses
    initscr(); 
  //cores do terminal
    start_color();
  // limpa a tela
    clear();
  // teclas digitadas nao serao exibidas
    noecho();
  // cada carcatere digitado e lido imediatamente
    cbreak(); 
  // habilita o uso de teclas na funcao 
    keypad(stdscr, TRUE);
  // todos os eventos do mouse serao capturados
    mousemask(ALL_MOUSE_EVENTS, NULL); 
  // tempo pra captura de entrada
    halfdelay(5); 

  // largura e altura da tela
    cols = 80;
    lines = 24;
  // atualiza a dimensao
    handleResize(0);
  // delocamneto de uma linha
    lineBoundaryOffset = 1;

  //cores das cartas
    init_pair(1, COLOR_CYAN, COLOR_BLACK); // for card outline
    init_pair(2, COLOR_BLUE, COLOR_BLACK); // for spades and clubs
    init_pair(3, COLOR_RED, COLOR_BLACK);  // for hearts and diamonds
    init_pair(4, COLOR_GREEN, COLOR_BLACK); // for turned over card
    init_pair(5, COLOR_GREEN, COLOR_BLACK); // for box drawing
    init_pair(6, COLOR_GREEN, COLOR_BLACK); // for banner display
  }

// Destructor.
   display::~display() 
  endwin(); 
}

int display::captureInput(void) {	

  int ch=getch(); 

  switch (ch) {
    case KEY_MOUSE: 
      {
        MEVENT mevent; 
        getmouse(&mevent); 
        mouseEventX = mevent.x; 
        mouseEventY = mevent.y; 
        mouseEventButton = mevent.bstate; 
        return -1; 
      }
      break;
    case ERR: 
      {
        return 0; 
      }
      break;
    default: 
      return ch; 
  }

  return 0; 
}

void display::handleResize(int sig) {
#ifdef TIOCGSIZE 
  struct ttysize ts;
  ioctl(STDIN_FILENO, TIOCGSIZE, &ts); 
  cols = ts.ts_cols;
  lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
  struct winsize ts;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ts); 
  cols = ts.ws_col;
  lines = ts.ws_row;
#endif 
  resizeterm(lines, cols); 
}


void display::displayCard(int x, int y, int suit, int number, int printAtt) {

  attron(COLOR_PAIR(1) | printAtt);
  
  if (x>=0 && y>=0 && x<cols-6 && y<lines-lineBoundaryOffset) {
    mvprintw(y,x,"\u250c\u2500\u2500\u2500\u2500\u2510");
    if (y<lines-1-lineBoundaryOffset) {
      move(y+1,x); 
      printFace(suit,number,0, printAtt); 
    }
    if (y<lines-2-lineBoundaryOffset) {
      move(y+2,x); 
      printFace(suit,number,1, printAtt); 
    }
    if (y<lines-3-lineBoundaryOffset) {
      move(y+3,x); 
      printFace(suit,number,2, printAtt); 
    }
    if (y<lines-4-lineBoundaryOffset) { 
      
      mvprintw(y+4,x,"\u2514\u2500\u2500\u2500\u2500\u2518");
    }
  }
  attroff(COLOR_PAIR(1) | printAtt);
}


  printw("\u2502");

  if (suit==2 || suit==4) { 
    attron(COLOR_PAIR(3) | printAtt);
  } else { 
    attron(COLOR_PAIR(2) | printAtt);
  }

  if (number==15) {
    if (line==0)
      printw("J%s  ", joker);
    if (line==1)
      printw("oker");
    if (line==2)
      printw("  J%s", joker);
  } else if (suit>=1 && suit <=4 && number>=2 && number<=14) {
    if (line==0) {
      printSuit(suit); 
      printNumber(number); 
      if (number!=10)
        printw(" ");
      printw(" ");	
    } else if (line==2) {
      if (number!=10)
        printw(" ");
      printw(" ");
      printNumber(number); 
      printSuit(suit);	
    } else {
      printw("    ");
    }
  } else {
    attron(COLOR_PAIR(4) | printAtt);
    if (line==0)
      printw("%s  %s", spades, hearts);
    if (line==1)
      printw("Play");
    if (line==2)
      printw("%s  %s", diamonds, clubs);
    attroff(COLOR_PAIR(1) | printAtt);
  }

  // turn on the card edge color settings
  attron(COLOR_PAIR(1) | printAtt);
  // print the right edge of the card
  printw("\u2502");
}

void display::printSuit(int suit) {
  switch (suit) {
    case 1:
      printw("%s",spades);
      break;
    case 2:
      printw("%s",diamonds);
      break;
    case 3:
      printw("%s",hearts);
      break;
    case 4:
      printw("%s",clubs);
      break;
    default:
      printw(" ");
      break;
  }
}

void display::printNumber(int number) {
  switch (number) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      printw("%i",number);
      break;
    case 11:
      printw("%c",'J');
      break;
    case 12:
      printw("%c",'Q');
      break;
    case 13:
      printw("%c",'K');
      break;
    case 14:
      printw("%c",'A');
      break;
    default:
      printw(" ");
      break;
  }
}
