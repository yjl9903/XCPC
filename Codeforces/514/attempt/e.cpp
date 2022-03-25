#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<ll,int> PII;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, l, w[maxn], ans;
ll s;

int cnt[maxn]; ll sum[maxn];
void dfs(int u) {
    int c = 0; vector<PII> vec;
    for (int& v: edge[u]) {
        dfs(v);
        dbg(v, cnt[v], sum[v]);
        if (cnt[v] >= l || sum[v] + w[u] > s) continue;
        vec.push_back({sum[v], cnt[v]});
    }
    sort(vec.begin(), vec.end());
    ans += (int)vec.size();
    // cout << (int)vec.size() << endl;
    if (vec.empty() || vec.front().first + w[u] > s) {
        ans++;
        cnt[u] = 1; sum[u] = w[u]; return ;
    }
    ans--;
    cnt[u] = vec.front().second + 1;
    sum[u] = vec.front().first + w[u];
    if (vec.size() > 1) {
        if (vec[1].first + sum[u] <= s && vec[1].second + cnt[u] <= l) {
            ans--;
            cnt[u] = l + 1;
        }
    }
}

int main() {
    scanf("%d%d%I64d", &n, &l, &s); for (int i = 1; i <= n; i++) scanf("%d", w + i);
    for (int i = 2, x; i <= n; i++) scanf("%d", &x), edge[x].push_back(i);
    for (int i = 1; i <= n; i++) if (w[i] > s) return puts("-1"), 0;
    dfs(1);
    cout << ans << endl;
    return 0;
}