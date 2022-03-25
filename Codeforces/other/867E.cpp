#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;

int n, a[maxn];
priority_queue<int, vector<int>, greater<int> > q;

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    ll ans = 0;
    for (int i = 0; i < n; i++){
        if (q.empty()) q.push(a[i]);
        else {
            int t = q.top();
            if (t < a[i]){
                q.pop(); q.push(a[i]); q.push(a[i]);
                ans += a[i] - t;
            }
            else q.push(a[i]);
        }
    }    
    printf("%lld\n", ans);
    return 0;
}