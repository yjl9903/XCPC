#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

struct node{
    int u, v, w;
    bool operator<(const node& b)const{
        return w < b.w;
    }
};
vector<node> q;

int n, m, k, key[maxn], pre[maxn], cnt[maxn], sp[maxn], ans[maxn];

int find(int x){return pre[x] == x ? x : pre[x] = find(pre[x]);}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) pre[i] = i;
    for (int i = 1; i <= k; i++) scanf("%d", key + i), cnt[key[i]] = 1;
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        q.push_back({u, v, w});
    }
    sort(q.begin(), q.end());
    int res = 0;
    for (node& x: q) {
        int b1 = find(x.u), b2 = find(x.v);
        if (b1 == b2) continue;

        cnt[b2] += cnt[b1];
        pre[b1] = b2;
        if (cnt[b2] == k) {
            res = x.w; break;
        }
    }
    for (int i = 1; i <= k; i++) {
        printf("%d ", res);
    }
    return 0;
}