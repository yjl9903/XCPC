#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n;
// multiset<int> a, b;
priority_queue<int> a, b;

int main(){
    scanf("%d", &n);
    for (int i = 0, x; i < n; i++) scanf("%d", &x), a.push(x);
    for (int i = 0, x; i < n; i++) scanf("%d", &x), b.push(x);
    ll ans1 = 0, ans2 = 0;
    int tot = 0;

    // for (auto it = a.begin(); it != a.end(); it++) printf("%d\n", *it);
    // for (auto it = b.begin(); it != b.end(); it++) printf("%d\n", *it);

    while (a.size() && b.size()){

        if (tot == 0){
            if (a.top() > b.top()){
                ans1 += a.top();
                a.pop();
            }
            else b.pop();
        }
        else {
            if (a.top() < b.top()){
                ans2 += b.top();
                b.pop();
            }
            else a.pop();
        }
        // printf("%lld %lld\n", ans1, ans2);
        tot ^= 1;
    }
    while (a.size()){
        if (tot == 0){
            ans1 += a.top();
        }
        a.pop();
        // printf("%lld %lld\n", ans1, ans2);
        tot ^= 1;
    }
    while (b.size()){
        if (tot == 1){
            ans2 += b.top();
        }
        b.pop();
        // printf("%lld %lld\n", ans1, ans2);
        tot ^= 1;
    }
    printf("%I64d", ans1 - ans2);
    return 0;
}