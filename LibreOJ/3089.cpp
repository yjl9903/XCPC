#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <cassert>
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
const int maxn = 1501 + 5;
const double eps = 1e-6;

bool eq(double a, double b) {
    return fabs(a - b) < eps;
}

int n, m, pos[maxn];
char s[maxn], tmp[maxn];
double v[maxn];

namespace acam {
    static const int maxp = 3002 + 5;
    int sz, ch[maxp][10], fail[maxp];
    int match[maxp];
    double val[maxp];
    int node() {
        ms(ch[++sz], 0); fail[sz] = 0; val[sz] = 0;
        return sz;
    }
    void clear() {
        sz = 0; node();
        for (int i = 0; i < 10; i++) ch[0][i] = 1;
    }
    int insert(char* s, int i) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            int v = s[i] - '0';
            if (!ch[u][v]) ch[u][v] = node();
            u = ch[u][v];
        }
        return u;
    }
    vector<int> edge[maxp];
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 10; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
        for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    }
    void dfs(int u) {
        for (int v: edge[u]) {
            val[v] += val[u];
            dfs(v);
        }
    }
    void update(double mid) {
        for (int i = 0; i <= sz; i++) val[i] = 0;
        for (int i = 1; i <= m; i++) {
            int u = pos[i];
            val[u] = v[i] - mid;
        }
        dfs(1);
    }
}
using acam::sz;
using acam::ch;
using acam::val;

bool check(double mid) {
    acam::update(mid);
    vector<double> dp(sz + 1, -inf), tmp;
    dp[1] = 0.0;
    for (int i = 1; i <= n; i++) {
        tmp.assign(sz + 1, -inf);
        auto move = [&](int c) {
            for (int u = 1; u <= sz; u++) {
                int v = ch[u][c];
                tmp[v] = max(tmp[v], dp[u] + val[v]);
            }
        };
        if (s[i] == '.') {
            for (int i = 0; i < 10; i++) move(i);
        } else {
            move(s[i] - '0');
        }
        swap(tmp, dp);
    }
    double mx = -inf;
    for (int i = 1; i <= sz; i++) mx = max(mx, dp[i]);
    return mx < eps;
}

vector<double> f[maxn];
string get(double mid) {
    acam::update(mid);
    vector<double> dp(sz + 1, -inf);
    f[0] = vector<double>(sz + 1, -inf);
    f[0][1] = dp[1] = 0.0;
    for (int i = 1; i <= n; i++) {
        vector<double> tmp(sz + 1, -inf);
        auto move = [&](int c) {
            for (int u = 1; u <= sz; u++) {
                int v = ch[u][c];
                tmp[v] = max(tmp[v], dp[u] + val[v]);
            }
        };
        if (s[i] == '.') {
            for (int i = 0; i < 10; i++) move(i);
        } else {
            move(s[i] - '0');
        }
        f[i] = tmp;
        for (int j = 1; j <= sz; j++) dp[j] = tmp[j];
    }
    string ans;
    int last = sz;
    for (int i = 1; i < sz; i++) if (dp[i] > dp[last]) last = i;
    for (int i = n - 1; i >= 0; i--) {
        int flag = 0;
        for (int u = 1; u <= sz && !flag; u++) {
            int l = 0, r = 10;
            if (s[i + 1] != '.') l = s[i + 1] - '0', r = l + 1;
            for (int c = l; c < r; c++) {
                if (ch[u][c] != last) continue;
                if (eq(f[i][u] + val[last], f[i + 1][last])) {
                    flag = 1;
                    last = u;
                    ans += '0' + c;
                    break;
                }
            }
        }
        assert(flag);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    acam::clear();
    scanf("%d%d%s", &n, &m, s + 1);
    for (int i = 1, vv; i <= m; i++) {
        scanf("%s%d", tmp, &vv);
        v[i] = log(vv);
        pos[i] = acam::insert(tmp, i);
    }
    acam::build();
    double l = 0, r = 1e9;
    while (r - l > eps) {
        double m = (l + r) / 2;
        if (check(m)) r = m;
        else l = m;
    }
    // printf("%.4lf\n", l);
    printf("%s", get(l).c_str());
    return 0;
}