#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <sstream>
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
const int maxn = 100000 + 5;

int n, q, rt, mx;
map<int,PII> ch;
map<int,int> dep, fa;

void insert(int x) {
    int tot = rt;
    ch[x] = {mx, mx};
    while (1) {
        if (x < tot) {
            if (ch[tot].first != mx) tot = ch[tot].first;
            else {
                ch[tot].first = x; return ;
            }
        } else {
            if (ch[tot].second != mx) tot = ch[tot].second;
            else {
                ch[tot].second = x; return ;
            }
        }
    }
}
void dfs(int u) {
    // cout << u << endl;
    if (ch[u].first != mx) {
        int v = ch[u].first;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs(v);
    }
    if (ch[u].second != mx) {
        int v = ch[u].second;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs(v);
    }
}

char s[maxn];
set<int> st;
int a[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) scanf("%d", a + i), st.insert(a[i]);
    mx = *st.rbegin() + 1;
    for (int i = 1, x; i <= n; i++) {
        x = a[i];
        if (i == 1) {
            rt = x; ch[x] = {mx, mx};
        } else {
            insert(x);
        }
    }
    dep[rt] = 0; dfs(rt);
    scanf("%d", &q); getchar();
    string root = "root", sib = "siblings", level = "level", par = "parent", left = "left", right = "right";
    while (q--) {
        // scanf("%s", s);
        cin.getline(s, 10000);
        stringstream ss(s);
        int a, b = mx; ss >> a;
        string tmp;
        int qrt = 0, qs = 0, qp = 0, ql = 0, qr = 0, qsame = 0;
        while (ss >> tmp) {
            if (tmp[0] >= '0' && tmp[0] <= '9') {
                b = 0;
                for (char& s: tmp) b = b * 10 + (s - '0');
            } else {
                if (tmp == root) qrt = 1;
                if (tmp == sib) qs = 1;
                if (tmp == level) qsame = 1;
                if (tmp == par) qp = 1;
                if (tmp == left) ql = 1;
                if (tmp == right) qr = 1;
            }
        }

        if (!st.count(a)) {
            puts("No"); continue;
        }
        if (b != mx && !st.count(b)) {
            puts("No"); continue;
        }

        int c = 0, flag = -1;
        if (qrt) {
            if (a == rt) flag = 1;
            else flag = 0;
        }
        if (qs) {
            int p = fa[a];
            int s1 = ch[p].first, s2 = ch[p].second;
            // dbg(p, s1, s2, a, b);
            if (a == s1 && b == s2) flag = 1;
            else if (a == s2 && b == s1) flag = 1;
            else flag = 0;
        }
        if (qp) {
            if (fa[b] == a) flag = 1;
            else flag = 0;
        }
        if (ql) {
            // dbg(b, ch[b].first, a);
            if (ch[b].first == a) flag = 1;
            else flag = 0;
        }
        if (qr) {
            if (ch[b].second == a) flag = 1;
            else flag = 0;
        }
        if (qsame) {
            if (dep[a] == dep[b]) flag = 1;
            else flag = 0;
        } 
        // cout << a << ' ' << b << endl;
        if (flag) puts("Yes");
        else puts("No");
    }
    return 0;
}