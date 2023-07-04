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
   display::~display() {
  // this is turns off all the special settings and returns the terminal to normal
  endwin(); 
  // insert deletion of dynamically created objects here too
}

/*
 * Function: This captures all the userinput.
 * Description: It captures mouse and keyboard events.
 * 		Returns "Positive Number" 
 *			- for user keypress
 *			- this is a character code typed
 * 		Returns "0" - for no user input
 *			- this is when nothing is typed for half a second
 *			- allows for other timed operations to occur
 *		Returns "-1" - for mouse event
 *			- details of the mouse event must be fetched from this class
 *			- use getMouseEventX, getMouseEventY and getMouseEventButton
 */
int display::captureInput(void) {	
  // obtain one mouse event or keypress
  int ch=getch(); 
  // this is a switch statement for the result of getch
  switch (ch) {
    case KEY_MOUSE: // this occurs when an mouse event occurs
      {
        MEVENT mevent; // this is a variable declared of type MEVENT
        getmouse(&mevent); // this gets the mouse event from ncurses (library)
        mouseEventX = mevent.x; // get the column location of the event
        mouseEventY = mevent.y; // get the row location of the event
        mouseEventButton = mevent.bstate; // get the button state of the mouse
        return -1; // -1 is for a mouse event
      }
      break;
    case ERR: // this occurs when there is a timeout
      {
        return 0; // 0 is when nothing occurs
      }
      break;
    default: // this occurs when a key is pressed
      return ch; // a character is when the user types something
  }

  return 0; // this is never called, but is used to stop compiler complaints
}

/*
 * Function: Updates all the information in the display class on window resize
 * Description: This function just updates information, it requires the call
 *		from a static singal handler. Signal handlers service interrupts and require
 *		a static function to be called, because they are not part of the main
 * 		program control flow. The signal handler should be declared in the main
 *		class, because your game should redraw the display on a resize.
 */
void display::handleResize(int sig) {
#ifdef TIOCGSIZE // operating system dependant differences
  struct ttysize ts;
  ioctl(STDIN_FILENO, TIOCGSIZE, &ts); // get the information of the terminal
  cols = ts.ts_cols;
  lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
  struct winsize ts;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ts); // get the information of the terminal
  cols = ts.ws_col;
  lines = ts.ws_row;
#endif /* TIOCGSIZE */
  resizeterm(lines, cols); // sets the ncurses window size correctly
}

/*
 * Function: Displays various cards on the game screen
 * Description: This function displays various playing cards on the screen.
 *		The first two arguments are the x and y coordinates of the top left corner
 * 		of the card. 
 *			The suit values are: 1=spades, 2=hearts, 3=clubs, 4=diamonds
 * 			The numbers are: 1=Ace, 2-10=2-10, 11=Jack, 12=Queen, 13=King, 14=Joker
 *		Any suit and number that do not match the valid numberrs generates a face down
 *		card.
 *			The printAtt allows for one or more any of the following display settings:
 *				A_NORMAL        Normal display (no highlight)
 *				A_STANDOUT      Best highlighting mode of the terminal.
 *				A_UNDERLINE     Underlining
 *				A_REVERSE       Reverse video
 *				A_BLINK         Blinking
 *				A_DIM           Half bright
 *				A_BOLD          Extra bright or bold
 *				A_PROTECT       Protected mode
 *				A_INVIS         Invisible or blank mode
 *				A_ALTCHARSET    Alternate character set
 *				A_CHARTEXT      Bit-mask to extract a character
 *				COLOR_PAIR(n)   Color-pair number n 
 */

void display::displayCard(int x, int y, int suit, int number, int printAtt) {

  // Ncurses drawing settings
  attron(COLOR_PAIR(1) | printAtt);
  // prevent draw if it off the screen
  if (x>=0 && y>=0 && x<cols-6 && y<lines-lineBoundaryOffset) {
    // print the top lines of the card
    mvprintw(y,x,"\u250c\u2500\u2500\u2500\u2500\u2510");
    // the next 4 if statements prevent draw if it is over the bottom of the screen
    if (y<lines-1-lineBoundaryOffset) {
      move(y+1,x); // move command
      printFace(suit,number,0, printAtt); // call function to print card face
    }
    if (y<lines-2-lineBoundaryOffset) {
      move(y+2,x); // move command
      printFace(suit,number,1, printAtt); // call function to print card face
    }
    if (y<lines-3-lineBoundaryOffset) {
      move(y+3,x); // move command
      printFace(suit,number,2, printAtt); // call function to print card face
    }
    if (y<lines-4-lineBoundaryOffset) { 
      // prints the bottom lines of the card
      mvprintw(y+4,x,"\u2514\u2500\u2500\u2500\u2500\u2518");
    }
  }
  // Ncurses turn off the drawing settings
  attroff(COLOR_PAIR(1) | printAtt);
}

/*
 * Function: Print a single line of what is written on the card.
* Description: This copies suit, number and printAtt from the calling function.
 *		Also includes what line of the card face is being drawn.
 */
void display::printFace(int suit, int number, int line, int printAtt) {	
  // draw left edge of the card
  printw("\u2502");

  if (suit==2 || suit==4) { // Red for Hearts and Diamonds
    attron(COLOR_PAIR(3) | printAtt);
  } else { // Black for Spades and Clover
    attron(COLOR_PAIR(2) | printAtt);
  }

  // this the display of the joker
  if (number==15) {
    if (line==0)
      printw("J%s  ", joker);
    if (line==1)
      printw("oker");
    if (line==2)
      printw("  J%s", joker);
    // this is the display for the cards with suits and numbers
  } else if (suit>=1 && suit <=4 && number>=2 && number<=14) {
    if (line==0) {
      printSuit(suit); // function to draw suit
      printNumber(number); // function to draw number
      if (number!=10)
        printw(" ");
      printw(" ");	
    } else if (line==2) {
      if (number!=10)
        printw(" ");
      printw(" ");
      printNumber(number); // function to draw number
      printSuit(suit);	// function to draw suit
    } else {
      printw("    ");
    }
    // this is for a face down card
  } else {
    // the face down cards have a special color
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

/*
 * Function: Print the suit of the card
 * Description: This is just a look up table. 
 */
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

/*
 * Function: Prints the number on the card
 * Description: This is just a look up table.
 */
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
