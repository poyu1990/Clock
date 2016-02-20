#include "clock.h"

Clock::Clock(){

    hour1.setPos(8,4);
    hour2.setPos(17,4);
    minute1.setPos(29,4);
    minute2.setPos(38,4); 
    second1.setPos(50,4);
    second2.setPos(59,4);
    
    day1.setPos(4,14);
    day2.setPos(13,14); 
    
    year1.setPos(55,14);
    year2.setPos(64,14);

    militaryTime = 0;
    showSeconds = 0;
    
    // get starting time/date for clock
    time_t rawTime;
    tm *currentTime;
    int nowSec = 0;
    time(&rawTime);
    currentTime = localtime(&rawTime);
    
    clockTime = *currentTime;
    alarm = *currentTime;
    
    // set time/alarm to 12:00 by default
    clockTime.tm_sec = 0;
    clockTime.tm_min = 0;
    clockTime.tm_hour = 0;
    
    alarm.tm_sec = 0;
    alarm.tm_min = 0;
    alarm.tm_hour = 0;
    
    snooze = alarm;
    
    // make the user start by setting the time
    mode = TIME_SET;
    blink = 1;
    
    engine = createIrrKlangDevice();
        
    isPlaying = 0;
    alarmOn = 0;                   
}

Clock::~Clock(){
    engine->drop();
}

void Clock::button(char input)
{
                   
    switch( input ){
    case 9:  // F1
         militaryTime = !militaryTime;  
         break;   
    case 11: // F3
         showSeconds = !showSeconds;
         break;   
    case 14: //F6
         if( mode == CLOCK )
             mode = TIME_SET;
         else if (mode == ALARM)
             mode = ALARM_SET;
         else if (mode == ALARM_SET)
             mode = ALARM; 
         else if (mode == TIME_SET)
             mode = CLOCK;     
         blink = 0;
         break;
    case 15: //F7
         if( mode == TIME_SET )
             mode = ALARM_SET;
         else if( mode == ALARM_SET )
             mode = TIME_SET;
         else if (mode == CLOCK)
             mode = ALARM;
         else if (mode == ALARM)
             mode = CLOCK; 
         break;
    case 16:  // F8
         if( mode == TIME_SET )
             addTime(3600,0);
         else if( mode == ALARM_SET)
             addTime(3600,1); 
         break;    
    case 17:  // F9         
         if( mode == TIME_SET )
             addTime(-3600,0);
         else if( mode == ALARM_SET)
             addTime(-3600,1);
         break;
    case 18:  // F10
         if( mode == TIME_SET )
             addTime(60,0);
         else if( mode == ALARM_SET)
             addTime(60,1);   
         break;
    case 19:  // F11
         if( mode == TIME_SET )
             addTime(-60,0);
         else if( mode == ALARM_SET)
             addTime(-60,1);   
         break;                    
    case 27: // Escape
         exit(1);
         break;
    case ' ':
         if( alarmOn && isPlaying ){
             snooze.tm_min += 10;
             engine->stopAllSounds(); 
             isPlaying = 0;
         }    
         break;
    case '\n':
         if( isPlaying ){
             engine->stopAllSounds();
             snooze = alarm;
             isPlaying = 0;
             alarmOn = 0;
         }
         if (alarmOn)
            alarmOn = 0;
         else if (!alarmOn)
            alarmOn = 1;
         break;
    }  

    updateClock();
  
}

void Clock::addTime(int seconds, bool toAlarm){ 
     
     tm* target = toAlarm ? &alarm : &clockTime;
     
     target->tm_sec += seconds;
     
     while( target->tm_sec >= 60 ){
         target->tm_sec -= 60;
         target->tm_min += 1;
         
         if( mode == CLOCK )
             checkAlarm();
             
     }
     while( target->tm_sec < 0 ){
         target->tm_sec += 60;
         target->tm_min -= 1;
     }         
     
     while( target->tm_min >= 60 ){
         target->tm_min -= 60;
         target->tm_hour += 1;
     }
     while( target->tm_min < 0 ){
         target->tm_min += 60;
         target->tm_hour -= 1;
     }
       
     while( target->tm_hour >= 24 )
         target->tm_hour -= 24;
     while( target->tm_hour < 0 )
         target->tm_hour += 24;
                
     if( toAlarm )
         snooze = alarm;
 
     updateClock();    

}

void Clock::updateClock(){
     
     displayDate();
     mvprintw(0,0,"F1-Military Time F3-Show seconds F6-Enter/Exit time set mode Esc- exit clock");
     mvprintw(1,0,"F7-Time <-> Alarm in set mode F8-Hour+1 F9-Hour-1 F10-Minute +1 F11-Minute -1");
     mvprintw(2,0,"Space Bar- gives 10 minute snooze time Enter- on/off alarm");
     
     attron(COLOR_PAIR(1));
     if (alarmOn)
        mvprintw(8,69,"  ");
     attroff(COLOR_PAIR(1));
     
     attron(COLOR_PAIR(0));
     if (!alarmOn)
        mvprintw(8,69,"  ");
     attroff(COLOR_PAIR(0));
     mvprintw(8,72,"alarm on");
     
     
     switch(mode){
     case CLOCK:
          clockMode();
          attron(COLOR_PAIR(0));
          mvprintw(4, 69, "  ");
          attroff(COLOR_PAIR(0));  
          display(&clockTime);
          break;             
     case TIME_SET:
          clockMode();  
          if( (clockTime.tm_sec%2) || !blink )
              display(&clockTime);
          else
              clear();
          attron(COLOR_PAIR(1));
          mvprintw(4, 69, "  ");
          attroff(COLOR_PAIR(1));
          mvprintw(4, 72, "set-mode");
          break;
     case ALARM:
          clockMode();
          attron(COLOR_PAIR(0));
          mvprintw(4, 69, "  ");
          attroff(COLOR_PAIR(0));  
          display(&alarm);
          break;
     case ALARM_SET:
          clockMode();
          attron(COLOR_PAIR(1));
          mvprintw(4, 69, "  ");
          attroff(COLOR_PAIR(1));
          mvprintw(4,72,"set-mode");
          display(&alarm);
          break;    
     }
}

void Clock::clear(){
    
    hour1.clear();
    hour2.clear();
    minute1.clear();
    minute2.clear();
    second1.clear();
    second2.clear();
    
    pm(0);
    colon(0);
    colon2(0);
     
}

void Clock::display(tm *currentTime){

     int hour = currentTime->tm_hour;
     bool isPm = 0;

     if( hour>=12 )
         isPm = 1;
     else 
         isPm = 0;

     // military time to 12 hour time
     if(!militaryTime){
         if(hour>12)
             hour -= 12;
         else if(hour == 0)
             hour = 12;
     }
     
     int hourTens = hour/10;
     int hourOnes = hour%10;
     int minuteTens = ((currentTime->tm_min))/10;
     int minuteOnes = ((currentTime->tm_min))%10;
     int secondTens = ((currentTime->tm_sec))/10;
     int secondOnes = ((currentTime->tm_sec))%10;
     
     hour1.display( hourTens );
     hour2.display( hourOnes );
     minute1.display( minuteTens );
     minute2.display( minuteOnes );
     
     if(showSeconds && (mode != ALARM && mode != ALARM_SET)){
          second1.display( secondTens );
          second2.display( secondOnes );
          colon2( currentTime->tm_sec%2 );
          
     }
     else{
          second1.clear();
          second2.clear();
          colon2(0);
     }
          
     if( mode == ALARM || mode == ALARM_SET )
         colon(1);
     else
          colon( currentTime->tm_sec%2 );
          
     pm( isPm && !militaryTime );
     
     refresh();    
}

void Clock::displayDate(){

     // month and day
     month.setPos(25,14);
     month.displayMonth( clockTime.tm_mon + 1 );
     day1.display( clockTime.tm_mday/10 );
     day2.display( clockTime.tm_mday%10 );
     
     int year = clockTime.tm_year;
     
     year1.display( year/10  - (year/100)*10 );
     year2.display( year%10 );     
          
}

void Clock::pm(bool on) 
{    
     attron(COLOR_PAIR(on));
     mvprintw(11, 69, "  ");
     attroff(COLOR_PAIR(on));
     mvprintw(11,72,"pm mode");
} 

void Clock::colon(bool on)
{ 
     attron(COLOR_PAIR(on)); 
     mvprintw(5,27,"  ");
     mvprintw(9,27,"  ");
     attroff(COLOR_PAIR(on));
}

void Clock::colon2(bool on)
{
     attron(COLOR_PAIR(on)); 
        mvprintw(5,48,"  ");
        mvprintw(9,48,"  ");
     attroff(COLOR_PAIR(on));
}


void Clock::checkAlarm()
{

     if (alarmOn && (clockTime.tm_min == snooze.tm_min) && (clockTime.tm_hour == snooze.tm_hour)){
         engine->play2D("K-On_-_Dont_Say_Lazy.mp3", true);           
         isPlaying = 1;
     }
         
}

void Clock::clockMode()
{    
    attron(COLOR_PAIR(0));
      for (int i = 0; i<5; i++)
          mvprintw(6+i,3,"   ");
    attroff(COLOR_PAIR(0));
    attron(COLOR_PAIR(1));
    if (mode == CLOCK || mode == TIME_SET)
    {
      mvprintw(6,3,"   ");
      for(int i = 0; i<3; i++)
      mvprintw(7+i,4," ");         
    }      
    if ( mode == ALARM || mode == ALARM_SET)
    {
      
       mvprintw(6,4," ");
       mvprintw(7,3," ");
       mvprintw(7,5," ");
       mvprintw(8,3,"   ");
       mvprintw(9,3," ");
       mvprintw(9,5," ");
         
    }     
    attroff(COLOR_PAIR(1));      
           
}
