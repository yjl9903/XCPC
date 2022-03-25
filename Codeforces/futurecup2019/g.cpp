#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, a[maxn], vis[maxn * 10], vis2[maxn * 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (!vis[a[i]]) vis[a[i]] = i;
        else if (!vis2[a[i]]) vis2[a[i]] = i;
    }
    ll ans = 1e18; vector<int> vec;
    for (int i = 1; i <= (int)1e7; i++) {
        ll tot = 1; int c = 0;
        vector<int> v;
        for (int j = i; c < 2 && j <= (int)1e7; j += i) {
            if (vis[j]) {
                tot *= j; c++; v.push_back(vis[j]);
            } 
            if (c == 1 && vis2[j]) {
                tot *= j; c++; v.push_back(vis2[j]);
            }
        }
        if (c == 2 && tot / i < ans) {
            ans = tot / i; vec = v;
        }
    }
    sort(vec.begin(), vec.end());
    cout << vec[0] << ' ' << vec[1];
    return 0;
}