#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#include <set>
#include <map>
#include <random>
#include <ctime>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = (1 << 14) - 1;

int query(vector<int> v) {
    cout << "?";
    assert((int)v.size() == 100);
    for (int x: v) cout << " " << x;
    cout << endl;
    int x; cin >> x;
    if (x == -1) exit(0);
    return x;
}

int main() {
    vector<int> v1, v2;
    for (int i = 1; i <= 100; i++) v1.push_back(i);
    for (int i = 1; i <= 100; i++) v2.push_back(i << 7);
    int r1 = query(v1);
    int r2 = query(v2);
    map<int,int> mp;
    for (int x: v1) mp[x ^ r1]++;
    for (int x: v2) mp[x ^ r2]++;
    for (auto x: mp) {
        if (x.second == 2) {
            // dbg(x.first);
            cout << "! " << x.first << endl;
            return 0;
        }
    }
    assert(0);
    return 0;
}