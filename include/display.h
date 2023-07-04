#include <ncursesw/ncurses.h>
#include <iostream>
#include <cstdio>

using namespace std;

#define LEFT_UP    1
#define LEFT_DOWN  2
#define LEFT_CLICK 4
#define LEFT_DOUBLECLICK 24

#define RIGHT_UP    4096
#define RIGHT_DOWN  8192
#define RIGHT_CLICK 16384
#define LEFT_CLICK 4
#define LEFT_DOUBLECLICK 24

#define RIGHT_UP    4096
#define RIGHT_DOWN  8192
#define RIGHT_CLICK 16384
#define RIGHT_DOUBLECLICK 32768

#define MIDDLE_ROLLUP    1048576
#define MIDDLE_ROLLDOWN  256

const char joker[]	  = {0xE2, 0x98, 0xBA, 0};
const char clubs[]    = {0xE2, 0x99, 0xA3, 0};
const char diamonds[] = {0xE2, 0x99, 0xA6, 0};
const char hearts[]   = {0xE2, 0x99, 0xA5, 0};
const char spades[]   = {0xE2, 0x99, 0xA0, 0};

class display {
public:
	display(void);
	~display(); // destructor


	int captureInput(void);
	void handleResize(int sig);
	
	void displayCard(int x, int y, int suit, int number, int printAtt);
	void eraseBox(int x, int y, int sizeX, int sizeY);
	
	int getCols(void) {return cols;}
	int	getLines(void) {return lines;}
	int getMouseEventX(void) {return mouseEventX;}
  int getMouseEventY(void) {return mouseEventY;}
  int getMouseEventButton(void) {return mouseEventButton;}
