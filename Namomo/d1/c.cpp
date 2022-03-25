#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int, int>;
const int maxn = 100000 + 5;
const int maxm = 10 * maxn;

const int seed = 135;
ull p1, p2;
ull xp1[maxm], xp2[maxm];

void init() {
  const vector<int> prs{(int)1e9 + 7, (int)1e9 + 9, 998244353, 998244853,
                        19260817,     19681001,     91815541,  122420729,
                        917120411,    68740301,     515880193, 996244353,
                        1222827239,   1610612741};
  mt19937 rnd(time(nullptr));
  p1 = prs[rnd() % prs.size()];
  p2 = prs[rnd() % prs.size()];
  while (p1 == p2) {
    p2 = prs[rnd() % prs.size()];
  }
  xp1[0] = xp2[0] = 1;
  for (int i = 1; i < maxm; i++) {
    xp1[i] = xp1[i - 1] * seed % p1;
    xp2[i] = xp2[i - 1] * seed % p2;
  }
}

int n, m;
bool ans1[maxn], ans2[maxn];
char buf[maxm];
map<ull, vector<PII>> qry;

struct Trie {
  int tot, ptr, ch[maxm][26], match[maxm], dep[maxm], link[maxm];
  ull val1[maxm], val2[maxm];

  int node(int u = -1) {
    tot++;
    match[tot] = link[tot] = 0;
    memset(ch[tot], 0, sizeof ch[tot]);
    if (u >= 0)
      dep[tot] = dep[u] + 1;
    else
      dep[tot] = 0;
    return tot;
  }
  int insert(const char s[], int id) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int c = s[i] - 'a';
      if (!ch[u][c]) {
        ch[u][c] = node(u);
      }
      u = ch[u][c];
    }
    match[u] = id;
    return u;
  }
  Trie() {
    val1[0] = val2[0] = 0;
    tot = ptr = 0;
    node();
  }

  ull query(int l, int r, int p, ull val[], ull xp[]) {
    ull left = val[l - 1];
    ull right = val[r];
    return (right - left * xp[r - l + 1] % p + p) % p;
  }

  void dfs(int u) {
    if (match[u]) {
      int x = link[u];
      while (x) {
        ull x1 = query(dep[x] + 1, dep[u], p1, val1, xp1);
        ull x2 = query(dep[x] + 1, dep[u], p2, val2, xp2);
        qry[x1 << 32 | x2].push_back({match[x], match[u]});
        // cout << "qry: " << (x1 << 32 | x2) << endl;
        x = link[x];
      }
    }
    for (int c = 0; c < 26; c++) {
      if (ch[u][c]) {
        int v = ch[u][c];
        link[v] = match[u] ? u : link[u];
        val1[ptr + 1] = (val1[ptr] * seed + (c + 'a')) % p1;
        val2[ptr + 1] = (val2[ptr] * seed + (c + 'a')) % p2;
        ptr++;
        dfs(v);
        ptr--;
      }
    }
  }
} tr;

ull hsh[maxm];
ull query(int l, int r) {
  const unsigned int mask = ~(0u);
  ull left1 = hsh[l - 1] >> 32, right1 = hsh[r] >> 32;
  ull left2 = hsh[l - 1] & mask, right2 = hsh[r] & mask;
  ull x1 = (right1 - left1 * xp1[r - l + 1] % p1 + p1) % p1;
  ull x2 = (right2 - left2 * xp2[r - l + 1] % p2 + p2) % p2;
  return x1 << 32 | x2;
}

int main() {
  init();
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", buf);
    tr.insert(buf, i);
  }
  tr.dfs(1);
  vector<string> allS;
  map<ull, int> mp;
  for (int i = 1; i <= m; i++) {
    scanf("%s", buf);
    allS.push_back(buf);
    ull x1 = 0, x2 = 0;
    for (int j = 0; buf[j]; j++) {
      x1 = (x1 * seed + buf[j]) % p1;
      x2 = (x2 * seed + buf[j]) % p2;
    }
    mp[x1 << 32 | x2] = i;
    // cout << (x1 << 32 | x2) << " -> " << mp[(x1 << 32 | x2)] << endl;
  }
  for (int i = 1; i <= m; i++) {
    string& str = allS[i - 1];
    ull x1 = 0, x2 = 0;
    for (int j = 0; j < str.length(); j++) {
      x1 = (x1 * seed + str[j]) % p1;
      x2 = (x2 * seed + str[j]) % p2;
      hsh[j + 1] = x1 << 32 | x2;
    }
    // cout << "l1:" << i << endl;
    for (int j = 0; j < str.length(); j++) {
      // cout << j << " -> " << hsh[j + 1] << endl;
      if (qry.count(hsh[j + 1])) {
        ull suf = query(j + 2, str.length());
        if (mp.count(suf)) {
          ans2[i] = true;
          ans2[mp[suf]] = true;
          for (PII& x : qry[hsh[j + 1]]) {
            ans1[x.first] = true;
            ans1[x.second] = true;
          }
        }
      }
    }
  }
  int r1 = 0, r2 = 0;
  for (int i = 1; i <= n; i++) {
    if (!ans1[i]) r1++;
  }
  for (int i = 1; i <= m; i++) {
    if (!ans2[i]) r2++;
  }
  printf("%d %d\n", r1, r2);
  return 0;
}
