#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int cnt[2][26], f[26];
char s[maxn], t[maxn];

int main(){
    scanf("%s%s", s, t);
    int slen = strlen(s), tlen = strlen(t);
    for (int i = 0; i < slen; i++) cnt[0][s[i] - 'a']++;
    for (int i = 0; i < tlen; i++) cnt[1][t[i] - 'a']++;
    sort(cnt[0], cnt[0] + 26); sort(cnt[1], cnt[1] + 26);
    
    return 0;
}