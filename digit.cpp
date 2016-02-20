#include "digit.h"

DIGIT::DIGIT()
{
  ptr[0] = &DIGIT::seg0;
  ptr[1] = &DIGIT::seg1;
  ptr[2] = &DIGIT::seg2;
  ptr[3] = &DIGIT::seg3;
  ptr[4] = &DIGIT::seg4;
  ptr[5] = &DIGIT::seg5;
  ptr[6] = &DIGIT::seg6;
  ptr[7] = &DIGIT::seg7;
  
  x = 1; 
  y = 1;
}                       

DIGIT::~DIGIT()
{

}

void DIGIT::setPos(int xPos, int yPos){

     x = xPos;
     y = yPos;
          
}

void DIGIT::lookup(int num, bool displaySegments[])
{
  static const bool segment[10][8] =
            { {true,true,true, true, true, true, false, false},
              {false,true,true, false, false, false, false, false},
              {true,true,false, true, true, false, true, true},
              {true,true,true, true, false, false, true, true},
              {false,true,true, false, false, true, true, true},
              {true,false,true, true, false, true, true, true},
              {false,false,true, true, true, true, true, true},
              {true,true,true, false, false, false, false, false},
              {true,true,true, true, true, true, true, true},
              {true,true,true, false, false, true, true, true}};
  for(int i=0; i<8; i++)
    displaySegments[i] = segment[num][i];
}
 
void DIGIT::display(int num)
{ 
  if( num<0 || num>9 )
      return;
     
  bool display[8];
  lookup(num, display);
  for(int i=0; i<8; i++)
      (this->*ptr[i])(display[i]);
}

void DIGIT::clear(){

   for(int i=0; i<8; i++)
      (this->*ptr[i])( false ); 
     
}

void DIGIT::seg0(bool on)
{
   attron(COLOR_PAIR(on));

   mvprintw(y,x+2,"       ");   
   
   attroff(COLOR_PAIR(on));

}

void DIGIT::seg1(bool on)
{
     attron(COLOR_PAIR(on));

     for (int i = 0; i < 3; i++) 
         mvprintw(y+1+i, x+8, " ");  
          
     attroff(COLOR_PAIR(on)); 

}

void DIGIT::seg2(bool on)
{
    attron(COLOR_PAIR(on));
   
    for (int i = 0; i < 3; i++) 
        mvprintw(y+5+i, x+8, " ");
           
    attroff(COLOR_PAIR(on));   

}

void DIGIT::seg3(bool on)
{
   attron(COLOR_PAIR(on));

   mvprintw(y+8,x+2,"       "); 
   
   attroff(COLOR_PAIR(on));
}


void DIGIT::seg4(bool on)
{
    attron(COLOR_PAIR(on));
  
    for (int i = 0; i < 3; i++) 
        mvprintw(y+5+i, x+2, " "); 
        
    attroff(COLOR_PAIR(on)); 
}

void DIGIT::seg5(bool on)
{
     attron(COLOR_PAIR(on));

     for (int i = 0; i < 3; i++) 
         mvprintw(y+1+i, x+2, " "); 

     attroff(COLOR_PAIR(on)); 
}
void DIGIT::seg6(bool on)
{
   attron(COLOR_PAIR(on));
   
   mvprintw(y+4,x+2,"    "); 
    
   attroff(COLOR_PAIR(on));
}

void DIGIT::seg7(bool on)
{
    attron(COLOR_PAIR(on));
    
    mvprintw(y+4,x+6,"   ");
    
    attroff(COLOR_PAIR(on)); 
     
}

void DIGIT::seg8(bool on)
{
    attron(COLOR_PAIR(on));
    
    mvprintw(y+1, x+3," ");
    mvprintw(y+2, x+4," ");
    mvprintw(y+3, x+5," ");
    
    attroff(COLOR_PAIR(on)); 
     
} 
void DIGIT::seg9(bool on)
{
    attron(COLOR_PAIR(on));
    
    mvprintw(y+1, x+5," ");
    mvprintw(y+2, x+5," ");
    mvprintw(y+3, x+5," ");
    mvprintw(y+4, x+5," "); 
    
    attroff(COLOR_PAIR(on)); 
     
}
void DIGIT::seg10(bool on)
{
    attron(COLOR_PAIR(on));
    
    mvprintw(y+3, x+5," ");
    mvprintw(y+2, x+6," ");
    mvprintw(y+1, x+7," ");
    
    attroff(COLOR_PAIR(on)); 
     
}

void DIGIT::seg11(bool on)
{
    attron(COLOR_PAIR(on));
    
    mvprintw(y+5, x+5," ");
    mvprintw(y+6, x+4," ");
    mvprintw(y+7, x+3," ");
    
    attroff(COLOR_PAIR(on)); 
     
}

void DIGIT::seg12(bool on)
{
    attron(COLOR_PAIR(on));
    
    mvprintw(y+5, x+5," ");
    mvprintw(y+6, x+5," ");
    mvprintw(y+7, x+5," ");
    
    attroff(COLOR_PAIR(on)); 
     
}

void DIGIT::seg13(bool on)
{
    attron(COLOR_PAIR(on));
    
    mvprintw(y+5, x+5," ");
    mvprintw(y+6, x+6," ");
    mvprintw(y+7, x+7," ");
    
    attroff(COLOR_PAIR(on)); 
     
}

void DIGIT::displayMonth(int month)
{
     bool display[8]; 
     switch (month)
     {
            case 1:      seg0(true); 
                         seg1(true);
                         seg2(true);
                         seg3(true);
                         x += 9;
                         seg0(true);
                         seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true); 
                         x += 9;
                         seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg8(true);
                         seg13(true);
                         break; 
                 
            case 2:      seg0(true);
                         seg4(true);
                         seg5(true);
                         seg6(true); 
                         x += 9;
                         seg0(true);
                         seg3(true); 
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         x += 9; 
                         for(int i=0; i<8; i++)
                             (this->*ptr[i])(true);
                         break; 
                             
            case 3:      seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg8(true);
                         seg9(true);
                         x += 9;
                         seg0(true);
                         seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true); 
                         x += 9;
                         seg0(true);
                         seg1(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true);
                         seg13(true);
                         break;   
                          
            case 4:      seg0(true);
                         seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true); 
                         x += 9;
                         seg0(true);
                         seg1(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true);
                         seg13(true);
                         x += 9;
                         seg0(true);
                         seg1(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true);
                         seg13(true);
                         break; 
                         
            case 5:      seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg8(true);
                         seg9(true);
                         x += 9;
                         seg0(true);
                         seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true); 
                         x += 9;
                         seg8(true);
                         seg10(true);
                         seg12(true);
                         break; 
                          
            case 6:      seg0(true); 
                         seg1(true);
                         seg2(true);
                         seg3(true);
                         x += 9;
                         seg1(true);
                         seg2(true);
                         seg3(true);
                         seg4(true);
                         seg5(true);
                         x += 9;
                         seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg8(true);
                         seg13(true);
                         break;
                         
            case 7:      seg0(true); 
                         seg1(true);
                         seg2(true);
                         seg3(true);
                         x += 9;
                         seg1(true);
                         seg2(true);
                         seg3(true);
                         seg4(true);
                         seg5(true);
                         x += 9;
                         seg1(true);
                         seg2(true);
                         break;
                          
            case 8:      seg0(true);
                         seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true);
                         x += 9;
                         seg1(true);
                         seg2(true);
                         seg3(true);
                         seg4(true);
                         seg5(true);
                         x += 9;
                         seg0(true); 
                         seg3(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         break;
                          
            case 9:      lookup(5, display);
                         for(int i=0; i<8; i++)
                             (this->*ptr[i])(display[i]);
                         x += 9;
                         seg0(true);
                         seg3(true); 
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         x += 9;
                         seg0(true);
                         seg1(true);
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         seg7(true);
                         seg13(true);
                         break;
                          
            case 10:     lookup(0, display);
                         for(int i=0; i<8; i++)
                             (this->*ptr[i])(display[i]);
                         x += 9;
                         seg0(true);
                         seg3(true);
                         seg4(true);
                         seg5(true);
                         x += 9;
                         seg0(true);
                         seg9(true);
                         seg12(true);
                         break; 
                          
            case 11:     seg1(true);
                         seg2(true);
                         seg4(true);
                         seg5(true);
                         seg8(true);
                         seg13(true);
                         x += 9;
                         lookup(0, display);
                         for(int i=0; i<8; i++)
                             (this->*ptr[i])(display[i]);
                         x += 9;
                         seg1(true);
                         seg2(true);
                         seg8(true);
                         seg13(true);
                         break; 
                         
            case 12:     lookup(0, display);
                         for(int i=0; i<8; i++)
                             (this->*ptr[i])(display[i]);
                         x += 9;
                         seg0(true);
                         seg3(true); 
                         seg4(true);
                         seg5(true);
                         seg6(true);
                         x += 9; 
                         seg0(true);
                         seg3(true);
                         seg4(true);
                         seg5(true);
                         break; 
                       
            }                     

}
     
