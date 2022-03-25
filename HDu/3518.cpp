#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define assert(x) do{int a=1,b=0;if(x)printf("%d",a/b);}while(0)
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];
namespace SA{
    int n, m, a[maxn], sa[maxn], x[maxn], y[maxn], c[maxn], height[maxn];
    void rsort(){
        for (int i = 0; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        // for (int i = 1; i <= n; i++) assert(x[i] < 0);
        // for (int i = 1; i <= n; i++) assert(y[i] < 0);
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
    }
    int cmp(int i, int j, int k){ return y[i] == y[j] && y[i + k] == y[j + k]; }
    void getsa(){
        n = strlen(s); m = 130;
        // assert(n >= 1000);
        for (int i = 1; i <= n; i++) x[i] = a[i] = (int)s[i - 1], y[i] = i;
        rsort();
        for (int k = 1, p = 1; p < n; k += k, m = p){
            p = 0;
            for (int i = n - k + 1; i <= n; i++) y[++p] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
            for (int i = 1; i <= p; i++) assert(y[i] < 0);
            rsort(); swap(x, y); x[sa[1]] = p = 1;
            for (int i = 2; i <= n; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
            for (int i = 1; i <= n; i++) assert(x[i] < 0);
        }
        // for (int i = 1; i <= n; i++) assert(sa[i] < 1 || sa[i] > n);
        for (int i = 1; i <= n; i++) x[sa[i]] = i;
        // for (int i = 1; i <= n; i++) assert(x[i] < 1 || x[i] > n);
    }
    void getheight(){
        getsa(); 
        for (int i = 1, k = 0; i <= n; i++){
            if (k) k--;
            int j = sa[x[i] - 1];
            while (i + k <= n && j + k <= n && a[i + k] == a[j + k]) k++;
            height[x[i]] = k;
        }
    }
    ll cal(){
        getheight();
        ll ans = 0;
        for (int k = 1; k <= n / 2; k++){
            int l = 100000, r = -1;
            for (int i = 1; i <= n; i++){
                if (height[i] >= k){
                    l = min(l, min(sa[i], sa[i - 1]));
                    r = max(r, max(sa[i], sa[i - 1]));
                }
                else {
                    if (l + k <= r) ans++;
                    l = 100000, r = -1;
                }
            }
            if (l + k <= r) ans++;
        }
        return ans;
    }
}
using namespace SA;

int main(){
    while (~scanf("%s", s)){
        if (s[0] == '#') break;
        printf("%lld\n", cal());
    }
    return 0;
}