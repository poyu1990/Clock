// swap multimaps
#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

int main ()
{
  multimap<char,int> foo;
  multimap<char,int> bar;
  multimap<char,int>::iterator it;

  foo.insert(pair<char,int>('x',100));
  foo.insert(pair<char,int>('y',200));

  bar.insert(pair<char,int>('a',11));
  bar.insert(pair<char,int>('b',22));
  bar.insert(pair<char,int>('a',55));

  foo.swap(bar);

  cout << "foo contains:\n";
  for ( it=foo.begin() ; it != foo.end(); it++ )
    cout << (*it).first << " => " << (*it).second << endl;

  cout << "bar contains:\n";
  for ( it=bar.begin() ; it != bar.end(); it++ )
    cout << (*it).first << " => " << (*it).second << endl;
  system("pause");

  return 0;
}
