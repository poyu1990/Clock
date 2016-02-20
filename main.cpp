#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
  multimap<char,int> mymultimap;
  multimap<char,int>::iterator it;

  mymultimap.insert (pair<char,int>('b',20));
  mymultimap.insert (pair<char,int>('b',150));
  mymultimap.insert (pair<char,int>('a',10));

  // show content:
  for ( it=mymultimap.begin() ; it != mymultimap.end(); it++ )
    cout << (*it).first << " => " << (*it).second << endl;
  system("pause");
   return EXIT_SUCCESS;
}
