#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

ll t, n, a[maxn];
vector<ll> v;

int main(){
    scanf("%I64d%I64d", &n, &t);
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i), a[i] += a[i - 1], v.push_back(a[i]);
    sort(v.begin(), v.end()); 
    auto it = unique(v.begin(), v.end()); 
    v.resize(distance(v.begin(), it));

    ll ans = 0;
    for (int i = n; i > 0; i--){
        
    }
    printf("%lld\n", ans);
    return 0;
}