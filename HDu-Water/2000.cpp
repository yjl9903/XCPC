#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[10];

int main(){
    while (cin >> s){
        sort(s, s + 3);
        cout << s[0] << ' ' << s[1] << ' ' << s[2] << endl;
    }
    return 0;
}