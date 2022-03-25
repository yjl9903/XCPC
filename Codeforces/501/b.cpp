#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, vis[2][maxn] = {0};
char s[maxn], t[maxn];
vector<int> v;

int main(){
    scanf("%d%s%s", &n, s, t);
    for (int i = 0; i < n; i++) vis[0][s[i] - 'a']++, vis[1][t[i] - 'a']++;
    for (int i = 0; i < 26; i++){
        if (vis[0][i] != vis[1][i]) {
            puts("-1"); return 0;
        }
    }
    for (int i = 0; i < n; i++){
        if (s[i] != t[i]){
            int p = i + 1;
            for (; p < n; p++){
                if (s[p] == t[i]) break;
            }
            for (; p > i; p--){
                swap(s[p], s[p - 1]);
                v.push_back(p);
            }
        }
    }
    // printf("\n%s\n", s);
    printf("%d\n", v.size());
    for (int i = 0; i < v.size(); i++){
        if (i) putchar(' ');
        printf("%d", v[i]);
    }
    return 0;
}