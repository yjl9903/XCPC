#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <unordered_map>
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
const int maxn = 1000000 + 5;

struct Node {
    ll name;
    int pre, nxt, val;
} a[maxn];

int q, m, sz;
// char s[30];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &q, &m);
        a[1].pre = 0;
        a[1].nxt = 2;
        a[2].pre = 1;
        a[2].nxt = 0;
        sz = 2;
        int st = 1, ed = 2, op, v, bag = 0;
        ll str;
        map<ll,int> mp;
        while (q--) {
            scanf("%d%lld%d", &op, &str, &v);
            // string str(s);
            if (op == 0) {
                if (mp.count(str)) {
                    int id = mp[str];
                    printf("%d\n", a[id].val);
                    a[a[id].nxt].pre = a[id].pre;
                    a[a[id].pre].nxt = a[id].nxt;
                    a[id].pre = a[ed].pre;
                    a[id].nxt = ed;
                    a[a[ed].pre].nxt = id;
                    a[ed].pre = id;
                } else {
                    printf("%d\n", v);
                    int id = ++sz; bag++;
                    a[id].name = str;
                    mp[str] = id;
                    a[id].val = v;
                    a[id].pre = a[ed].pre;
                    a[id].nxt = ed;
                    a[a[ed].pre].nxt = id;
                    a[ed].pre = id;
                    if (bag > m) {
                        bag--;
                        int id = a[st].nxt;
                        mp.erase(a[id].name);
                        a[st].nxt = a[id].nxt;
                        a[a[id].nxt].pre = st;
                    }
                    // print();
                }
            } else if (op == 1) {
                if (!mp.count(str)) {
                    puts("Invalid"); continue;
                }
                // dbg(str, mp[str]);
                int id = mp[str];
                if (v == 0) {
                    printf("%d\n", a[id].val);
                } else if (v == -1) {
                    if (a[id].pre == st) puts("Invalid");
                    else printf("%d\n", a[a[id].pre].val);
                } else if (v == 1) {
                    if (a[id].nxt == ed) puts("Invalid");
                    else printf("%d\n", a[a[id].nxt].val);
                }
            }
        }
    }
    return 0;
}