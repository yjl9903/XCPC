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
        int len = strlen(s), flag = 1;
        for (int i = 0; 2 * i <= len; i++){
            if (s[i] != s[len - 1 - i]){
                flag = 0; break;
            }
        }
        if (flag) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}