#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
using namespace std;
typedef long long ll;
typedef pair<ll,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, k;
ll a[maxn], b[maxn], c[maxn];

vector<int> bag[maxn]; int tot = 1;
void insert(ll i, int id) {
    if (i > k) return ;
    bag[i].push_back(id);
}
int pop() {
    while (tot <= k && bag[tot].empty()) tot++;
    if (tot > k) return -1;
    int id = bag[tot].back(); bag[tot].pop_back();
    return id;
}
int top() {
    while (tot <= k && bag[tot].empty()) tot++;
    if (tot > k) return -1;
    return bag[tot].back();
}

int check(ll x) {
    for (int i = 1; i <= k; i++) bag[i].clear(); tot = 1;
    for (int i = 1; i <= n; i++) {
        c[i] = a[i]; 
        insert(a[i] / b[i] + 1, i);
    }
    for (int i = 1; i <= k; i++) {
        int id = pop();
        if (id == -1) return 1;
        c[id] += x; 
        insert(c[id] / b[id] + 1, id);
        if (!bag[i].empty()) return 0;
    }
    int id = pop(); if (id == -1) return 1;
    if (c[id] / b[id] + 1 <= k) return 0;
    return 1;
}

int main() {
    scanf("%d%d", &n, &k); k--;
    for (int i = 1; i <= n; i++) scanf("%I64d", a + i);
    for (int i = 1; i <= n; i++) scanf("%I64d", b + i);
    ll l = 0, r = 5e12, ans = -1;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (check(m)) ans = m, r = m - 1;
        else l = m + 1;
    }
    cout << ans << endl;
    return 0;
}