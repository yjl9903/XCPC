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

int a[maxn + 5];

int main() {
    set<int> st;
    map<int,int> mp;
    mt19937 rnd(time(0));
    for (int i = 0; i <= maxn; i++) a[i] = i;
    shuffle(a, a + maxn + 1, rnd);

    vector<int> v, v2;
    for (int i = 0; i <= 99; i++) v.push_back(a[i]), st.insert(a[i]);
    int r1 = query(v);
    for (int i = 0; i <= 99; i++) v[i] ^= r1, st.insert(v[i]);
    sort(v.begin(), v.end());
    for (int x: v) mp[x]++;
    // for (int x: v) dbg(x);

    int p = 100;
    for (int i = 100; i <= 199; i++, p++) {
        while (st.count(a[p])) p++;
        v2.push_back(a[p]);

    }
    int r2 = query(v2);
    for (int i = 0; i <= 99; i++) v2[i] ^= r2;
    sort(v2.begin(), v2.end());
    for (int x: v2) mp[x]++;
    // for (int x: v2) dbg(x);

    for (auto x: mp) {
        if (x.second == 2) {
            // dbg(x.first);
            cout << "! " << x.first << endl;
            return 0;
        }
    }
    return 0;
}