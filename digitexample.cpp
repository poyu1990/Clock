#include <cstdlib>
#include <iostream>
#include <ctime>
#include "clock.h"

using namespace std;

/*     DIRECTIONS
 *  F1  - Military Time
 *  F3  - Show seconds
 *  F6  - Enter/Exit time set mode
 *  F7  - Change from Time to Alarm in set mode
 *  F8  - Hour +1
 *  F9  - Hour -1
 *  F10 - Minute +1
 *  F11 - Minute -1
 */
 
int main(int argc, char *argv[])
{
    initialize();
    
    Clock myClock; 
    time_t rawTime;
    tm *currentTime;
    int nowSec = 0;
    int counter = 0;
    char input = 0;
    char storedInput = 0;
    bool lastWorked = 0;
    
    while(true)
    { 
        time(&rawTime);
        currentTime = localtime(&rawTime);
        if( (currentTime->tm_sec) != nowSec )
        {
           nowSec = currentTime->tm_sec;
           myClock.addTime();
        }
        
        input = getch();
        
        if( (input > 8 && input < 21) || input == ' ' || input == '\n' || input == 27 ) // if F1-F12, or space or enter or escape
        { // if F1-F12, or space or enter or escape
            storedInput = input;
            counter++;
        }
        if (clock()%250 <50)
        {
            if (!lastWorked)
                if( counter>=2 && (storedInput == 18 || storedInput == 19) )
                {
                   for(int i=0;i<5;i++)
                      myClock.button(storedInput);                            
                   storedInput = 0;
                   counter = 0;
                }
                else
                {
                    myClock.button(storedInput);
                    storedInput = 0;
                    counter = 0;
                }

            lastWorked = 1;
          }
          else 
               lastWorked = 0;
    }
    
    myExit();
    system("PAUSE");
    return EXIT_SUCCESS;
}
