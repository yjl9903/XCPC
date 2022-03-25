#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn];

int main(){
    int T; cin >> T;
    while (T--){
        cin >> s;
        s[5] = '6';
        cout << s + 5 << endl;
    }
    return 0;
}