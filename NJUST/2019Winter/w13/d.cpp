#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <queue>
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
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 10000 + 5;

vector<PII> edge[maxn];
map<int,int> mp[maxn], mp2[maxn];
int n, m, st, ed, k, kx[maxn], ky[maxn];

int dis[maxn], vis[maxn];
struct node{
    int to, d;
    bool operator< (const node& b)const{
        return d > b.d;
    }
};

int main() {
    scanf("%d%d%d", &n, &m, &k); 
    ed = k + 1;
    for (int i = 1; i <= k; i++) {
        scanf("%d%d", kx + i, ky + i);
        mp[kx[i]][ky[i]] = i;
        mp2[ky[i]][kx[i]] = i;
        if (kx[i] == n && ky[i] == m) ed = i;
        if (kx[i] == 1 && ky[i] == 1) st = i;
    }
    for (int i = 1; i <= n; i++) {
        if (mp[i].empty()) continue;
        vector<PII> v;
        for (auto& x: mp[i]) v.push_back(x);
        int flag = 0;
        if (i == n && ed == k + 1) {
            v.push_back({m, k + 1});
            flag = 1;
        }
        // dbg(i, v.size());
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                int w = 1;
                if (flag && v[j].first == m) w = 1;
                else if (v[i].first + 1 == v[j].first) w = 0;
                edge[v[i].second].push_back({v[j].second, w});
                edge[v[j].second].push_back({v[i].second, w});
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        if (mp2[i].empty()) continue;
        vector<PII> v;
        for (auto& x: mp2[i]) v.push_back(x);
        int flag = 0;
        if (i == m && ed == k + 1) {
            v.push_back({n, k + 1});
            flag = 1;
        }
        // dbg(i, v.size());
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                int w = 1;
                if (flag && v[j].first == n) w = 1;
                else if (v[i].first + 1 == v[j].first) w = 0;
                edge[v[i].second].push_back({v[j].second, w});
                edge[v[j].second].push_back({v[i].second, w});
            }
        }
    }
    // for (int i = 1; i <= k + 1; i++) {
    //     cout << i << ": ";
    //     for (PII& x: edge[i]) cout << "(" << x.first << ',' << x.second << ") ";
    //     cout << endl;
    // }

    for (int i = 1; i <= k + 1; i++) dis[i] = mod; dis[st] = 0;
    priority_queue<node> pq; pq.push({st, 0});
    while (!pq.empty()) {
        node u = pq.top(); pq.pop();
        if (vis[u.to]) continue;
        vis[u.to] = 1;
        for (auto& x: edge[u.to]) {
            int v = x.first;
            if (dis[v] > dis[u.to] + x.second) {
                dis[v] = dis[u.to] + x.second;
                pq.push({v, dis[v]});
            }
        }
    }
    if (dis[ed] == mod) puts("-1");
    else printf("%d\n", dis[ed]);
    return 0;
}