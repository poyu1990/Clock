#include "initialize.h"

void initialize()
{
	initscr ();                 //Turn on curses
	cbreak ();                  //Turn off carriage return to enter data
	noecho ();                  //Turn off echoing of input
	nodelay(stdscr, TRUE);      //Super fast snake
	//timeout(500);
	start_color ();             //Turn on coloring of output
	keypad (stdscr, TRUE);      //Turn on F key entry and arrowkeys
	curs_set(0);                //Set screen to default WHITE on BLACK

	if (!has_colors ())         //If colors not available, kill program
    {
		endwin ();
		fputs ("No colors!", stderr); 
		exit (1);
	}
    //Initialize color pairs
	init_pair (COLOR1, COLOR_BLACK, COLOR_YELLOW);
	init_pair (COLOR2, COLOR_WHITE, COLOR_BLACK);
	
	srand(time(NULL));
}     


void myExit()
{
	erase ();
	refresh ();
	endwin ();
	exit(0);
} 
