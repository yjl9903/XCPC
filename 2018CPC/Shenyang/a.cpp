#include <iostream>
using namespace std;

#ifdef XLor
  #define dbg(args...) do { cout << "debug: " << #args << " - > "; err(args); } while (0)
#else
  #define dbg(...)
#endif
void err() { cout << endl; }
template < typename T, typename...Args >
void err(T a, Args...args){ cout << a << ' '; err(args...); }

int main(){
    int x = 1, y = 2, c = 3;
    for (int i = 0; i < 2; i++) x++;
    dbg(x, y, c);
    return 0;
}