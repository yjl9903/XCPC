#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

char s[maxn];

int main(){
    while (~scanf("%s", s)){
        int len = strlen(s);
        char m = 'a';
        for (int i = 0; i < len; i++){
            // char x = s[i];
            // if (x >= 'A' && x <= 'Z') x = x - 'A' + 'a';
            m = max(m, s[i]);
        }
        for (int i = 0; i < len; i++){
            // char x = s[i];
            // if (x >= 'A' && x <= 'Z') x = x - 'A' + 'a';
            if (s[i] != m){
                printf("%c", s[i]); continue;
            }
            printf("%c(max)", s[i]);
        }
        printf("\n");
    }
    return 0;
}