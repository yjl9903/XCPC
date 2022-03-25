#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <set>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n, m, d, ans[maxn];
set<PII> s;

int main(){
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 0, x; i < n; i++) scanf("%d", &x), s.emplace(x, i);
    int day = 0;
    while (!s.empty()){
        day++;
        auto it = s.begin();
        while (it != s.end()){
            ans[it->second] = day;
            s.erase(it);
            int x = it->first;
            it = s.lower_bound(make_pair(x + d + 1, 0));
        }
    }
    printf("%d\n", day);
    for (int i = 0; i < n; i++) printf("%d ", ans[i]);
    return 0;
}