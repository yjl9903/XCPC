#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int n, k, a[maxn], cnt[maxn], last[maxn], ans[maxn];

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++;
    int s = 1;
    for (int i = 1; i <= 5000; i++) {
        if (cnt[i] > k) return puts("NO");
        last[i] = s;
        s = (s + cnt[i] + k - 1) % k + 1;
    }
    puts("YES");
    int tot = 0; 
    for (int i = 1; i <= n; i++) {
        last[a[i]] = last[a[i]] % k + 1;
        ans[i] = last[a[i]];
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}