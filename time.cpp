#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    time_t rawTime;
    struct tm *currentTime;
    int temp, nowMin = 0 , nowSec = 0;
    while(true)
    {
        time(&rawTime);
        currentTime = localtime(&rawTime);
        if(currentTime->tm_min != nowMin)
        {
           cout<<endl<<endl<<"Minute changed!"<<endl<<endl;
           nowMin = currentTime->tm_min;
        }
        if( (temp = currentTime->tm_sec) != nowSec)
        {
           if(temp %2)
             cout<<" tick ";
           else
             cout<<" tock ";
           nowSec = currentTime->tm_sec;
        }
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}
