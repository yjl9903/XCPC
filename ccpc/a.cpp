#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <queue>
#include <functional>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int inf = 1 << 30;

struct node{
    int v, t;
    bool operator< (const node& b) const{
        if (v != b.v) return v > b.v;
        return t < b.t;
    }
};
int n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        ll ans = 0; int cnt = 0;
        priority_queue<node> q;
        for (int i = 1, x; i <= n; i++){
            scanf("%d", &x);
            if (q.empty()) q.push({x, 0});
            else {
                int t = q.top().v;
                if (x > t){
                    if (q.top().t == 0) cnt += 2;
                    q.pop();
                    ans += x - t;
                    q.push({x, 0}); q.push({x, 1});
                }
                else q.push({x, 0});
            }
        }
        printf("%lld %d\n", ans, cnt);  
    }
    return 0;
}