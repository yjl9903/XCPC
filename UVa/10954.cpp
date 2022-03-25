#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 5000 + 5;

int n, a[maxn];

int main(){
    while (~scanf("%d", &n) && n){
        priority_queue<int, vector<int>, greater<int> > pq;
        for (int i = 0; i < n; i++) scanf("%d", &a[i]), pq.push(a[i]);
        int ans = 0;
        while (pq.size() > 1){
            int x = pq.top(); pq.pop();
            int y = pq.top(); pq.pop();
            ans += x + y;
            pq.push(x + y);
        }
        printf("%d\n", ans);
    }
    return 0;
}