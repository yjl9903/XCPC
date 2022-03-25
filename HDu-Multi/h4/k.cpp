#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500 + 5;

char s[maxn];

bool check(){
    int len = strlen(s);
    if (s[0] == '+' || s[0] == '*') return false;
    if (s[len - 1] == '+' || s[len - 1] == '*') return false;
    for (int i = 0; i < len; i++){
        if (s[i] == '+' || s[i] == '*'){
            if (s[i + 1] == '+' || s[i + 1] == '*')
                return false;
        }
    }
    if (s[0] == '0' && s[1] >= '0' && s[1] <= '9') return false;
    for (int i = 0; i < len; i++) {
        if ((s[i] == '+' || s[i] == '*') && s[i + 1] == '0'){
            if (s[i + 2] >= '0' && s[i + 2] <= '9') return false;
        }
    }
    return true;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        int len = strlen(s);
        for (int i = 0; i < len; i++){
            if (s[i] == '0' && s[i + 1] == '?'){
                if (i == 0) s[++i] = '+';
                else if (s[i - 1] == '+' || s[i - 1] == '*') s[++i] = '+';
            }
            else if (s[i] == '?') s[i] = '1';
        }
        // for (int i = 0; i < len; i++) if (s[i] == '?') s[i] = '1';
        if (check()) puts(s);
        else puts("IMPOSSIBLE");    
    }
    return 0;
}