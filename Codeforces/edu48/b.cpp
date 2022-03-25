#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, q, vis[maxn] = {0}, cnt[maxn][maxn] = {0}, nxt[maxn];
char s[maxn], t[maxn];
vector<int> v;

void getnxt(){
    int len = strlen(t), i = 0, j = -1; nxt[0] = -1;
    while (i < len && j < len){
        if (j == -1 || t[i] == t[j]) i++, j++, nxt[i] = j;
        else j = nxt[j];
    }
}
void kmp(){
    getnxt();
    int slen = strlen(s), tlen = strlen(t), i = 0, j = 0;
    while (i < slen && j < tlen){
        if (j == -1 || s[i] == t[j]) i++, j++;
        else j = nxt[j];
        if (j == tlen){
            v.push_back(i); j = nxt[j];
        }
    }
}

int main(){
    scanf("%d%d%d%s%s", &n, &m, &q, s, t);
    kmp();
    for (int i = 0; i < v.size(); i++){
        vis[v[i] - 1] = 1;
        // printf("%d\n", v[i]);
    }
    for (int i = 0; i < n; i++){
        for (int j = i + m - 1; j < n; j++) {
            // printf("%d %d\n", i, j);
            if (vis[j]) cnt[i][j] = cnt[i][j - 1] + 1;
            else cnt[i][j] = cnt[i][j - 1];
        }
    }
    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++){
    //         printf("%d ", cnt[i][j]);
    //     }
    //     puts("");
    // }
    while (q--){
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", cnt[l - 1][r - 1]);
    }
    return 0;
}