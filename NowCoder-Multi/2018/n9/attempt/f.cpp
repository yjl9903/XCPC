#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n;
char s[4][maxn], opt[maxn];

int nxt[4][maxn], len[4], st[maxn][4] = {0};
void getnxt(int t){
    int len = strlen(s[t]), i = 0, j = -1; nxt[t][0] = -1;
    while (i < len && j < len){
        if (j == -1 || s[i] == s[j]) i++, j++, nxt[t][i] = j;
        else j = nxt[t][j];
    }
}   

int main(){
    scanf("%d", &n);
    int m = 1 << 30;
    for (int i = 0; i < n; i++) scanf("%s", s[i]), getnxt(i), len[i] = strlen(s[i]), m = min(len[i], m);
    scanf("%s", opt);
    printf("%d\n", m);
    int tp = 0; 
    for (int i = 0; opt[i] != '\0'; i++){
        if (opt[i] == '-'){
            tp--; int res = 1 << 30;
            for (int j = 0; j < n; j++){
                res = min(res, len[j] - st[j][tp]);
            }
            printf("%d\n", res);
        }
        else {
            int res = 1 << 30;
            for (int j = 0; j < n; j++){
                if (opt[i] == s[j][st[j][tp]]){
                    st[j][tp + 1] = st[j][tp] + 1;
                }
                else st[j][tp + 1] = nxt[j][st[j][tp]];
                res = min(res, len[j] - 1 - st[j][tp + 1]);
            }
            tp++;
            printf("%d\n", res);
        }
    }
    return 0;
}