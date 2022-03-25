#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn];
bool check(char x){
    if (x >= 'a' && x <= 'z') return 1;
    if (x >= 'A' && x <= 'Z') return 1;
    return false;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        int len = strlen(s), i = 0;
        if (s[0] == '/' || s[0] == '\\'){
            puts("It's a path in Unix-like systems!");
            for (int i = 0; i < len; i++){
                if (s[i] == '\\') s[i] = '/';
            }
            printf("%s\n", s);
            continue;
        }
        while (i < len && check(s[i])) i++;
        i++; 
        if ((s[i] == '/' || s[i] == '\\') && (s[i + 1] == '/' || s[i + 1] == '\\')){
            puts("It's a URL!");
            for (int i = 0; i < len; i++){
                if (s[i] == '\\') s[i] = '/';
            }
            printf("%s\n", s);
        }
        else {
            puts("It's a path in Windows system!");
            for (int i = 0; i < len; i++) if (s[i] == '/') s[i] = '\\';
            printf("%s\n", s);
        }
    }
    return 0;
}