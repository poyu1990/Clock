#include <iostream>
#include <cstdlib>
#include "initialize.h"

#ifndef K
#define K

class DIGIT;

typedef void (DIGIT::*FPTR[8])(bool);
typedef void (*fptr)();

class DIGIT
{
   public:
      DIGIT();
      ~DIGIT();
      
      void display(int num);
      void displayMonth(int month);
      void clear();
      void setPos(int xPos, int yPos);
            
   private:
           
     FPTR ptr; 
     void lookup(int num, bool displaySegment[8]);
     void seg0(bool on);
     void seg1(bool on);
     void seg2(bool on);
     void seg3(bool on);
     void seg4(bool on);
     void seg5(bool on);
     void seg6(bool on);
     void seg7(bool on);
     void seg8(bool on);
     void seg9(bool on);
     void seg10(bool on);
     void seg11(bool on);
     void seg12(bool on);
     void seg13(bool on);
      
     int x,y;
};

#endif
