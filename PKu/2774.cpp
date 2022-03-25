#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

char s[maxn]; int len;
namespace SA{
    int n, m, a[maxn], x[maxn], y[maxn], c[maxn], sa[maxn], h[maxn];
    void rsort(){
        for (int i = 0; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
    }
    int cmp(int i, int j, int k){return y[i] == y[j] && y[i + k] == y[j + k];}
    void init(){
        m = 130;
        for (int i = 1; i <= n; i++) x[i] = a[i] = s[i - 1], y[i] = i;
        rsort();
        for (int k = 1, p = 1; p < n; k += k, m = p){
            p = 0;
            for (int i = n - k + 1; i <= n; i++) y[++p] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
            rsort(); swap(x, y); x[sa[1]] = p = 1;
            for (int i = 2; i <= n; i++) x[sa[i]] = cmp(sa[i - 1], sa[i], k) ? p : ++p;
        }
        for (int i = 1; i <= n; i++) x[sa[i]] = i;
    }
    void geth(){
        for (int i = 1, k = 0; i <= n; i++){
            if (k) k--;
            int j = sa[x[i] - 1];
            while (a[i + k] == a[j + k] && k < n) k++;
            h[x[i]] = k;
        }
    }
    int cal(){
        init(); geth(); int ans = 0;
        for (int i = 2; i <= n; i++){
            int x = sa[i], y = sa[i - 1];
            if (x <= len && y > len) ans = max(ans, h[i]);
            if (y <= len && x > len) ans = max(ans, h[i]);
        }
        return ans;
    }
}
using namespace SA;

int main(){
    scanf("%s", s); n = len = strlen(s); s[n] = 'a' - 1;
    scanf("%s", s + n + 1); n = strlen(s);
    printf("%d\n", cal());
    return 0;
}