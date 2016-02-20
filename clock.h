#include "digit.h"
#include <ctime>
#include "irrKlang-1.1.3\\include\\irrKlang.h"

using namespace irrklang; 
//#pragma comment(lib, "irrKlang-1.1.3\\lib\\Win32-gcc\\irrKlang.lib") 

enum ClockMode { CLOCK, TIME_SET, ALARM_SET, ALARM };

class Clock
{
  public:
         Clock();
         ~Clock();
         

         void button(char input);
         void addTime(int seconds = 1, bool toAlarm = 0);     
  private:
          void updateClock();
          void display(tm *currentTime);
          void displayDate();
          void clear();
          void pm(bool on);
          void colon(bool on);
          void colon2(bool on);
          void checkAlarm(); 
          void clockMode(); 
          DIGIT hour1,   hour2;
          DIGIT minute1, minute2;
          DIGIT second1, second2;    

          DIGIT month;
          DIGIT day1, day2;   
          DIGIT year1, year2;      
          ClockMode mode;
          
          bool militaryTime;
          bool showSeconds;
          bool blink;
          bool alarmOn;
          
          ISoundEngine* engine;
          bool isPlaying;
          
          
          
          tm clockTime, alarm, snooze;
};
