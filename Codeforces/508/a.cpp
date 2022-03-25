#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];
int n, k, cnt[26];

int main(){
    scanf("%d%d%s", &n, &k, s);
    for (int i = 0; i < n; i++) cnt[s[i] - 'A']++;
    int ans = 2 * maxn;
    for (int i = 0; i < k; i++) ans = min(ans, cnt[i]);
    printf("%d", ans * k);
    return 0;
}