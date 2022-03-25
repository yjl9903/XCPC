#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n;
char s[maxn], t[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(s, 0);
        scanf("%d%s", &n, s);
        int len = strlen(s);
        for (int i = 2; i <= n; i++){
            scanf("%s", t); int k = 0;
            for (int j = 0; j < len; j++){
                if (s[j] == t[k]) k++;
                if (t[k] == '\0') break;
            }
            for (int j = k; t[j] != '\0'; j++){
                s[len++] = t[j];
            }
        }
        printf("%s\n", s);
    }
    return 0;
}