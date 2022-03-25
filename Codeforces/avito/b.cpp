#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn], cnt[maxn], ans[maxn], used[maxn], col[maxn];

int main(){
    scanf("%d", &n); 
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i), a[i] = n - a[i];
        cnt[a[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) continue;
        if (cnt[i] % i) return puts("Impossible"), 0;

    }
    puts("Possible");
    set<int> s; for (int i = 1; i <= n; i++) s.insert(i);
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        if (col[x]) {
            ans[i] = col[x];
        } else {
            ans[i] = col[x] = *s.begin();
            s.erase(s.begin());
        }
        used[x]++;
        // cout << used[x] << endl;
        if (used[x] % x == 0) {
            if (used[x] == cnt[x]) continue;
            col[x] = *s.begin();
            s.erase(s.begin());
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}