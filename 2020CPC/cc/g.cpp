#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int maxn = 500000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int sz = 1, last = 1, cnt[maxn * 2], R[maxn * 2];
int len[maxn * 2], link[maxn * 2], ch[maxn * 2][26];
int insert(int c, int i) {
  int cur = ++sz, p = last;
  len[cur] = len[last] + 1;
  R[cur] = i;
  cnt[cur] = 1;
  for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
  if (!p) link[cur] = 1;
  else {
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) link[cur] = q;
    else {
      int nq = ++sz;
      len[nq] = len[p] + 1;
      link[nq] = link[q];
      R[nq] = R[q];
      link[q] = link[cur] = nq;
      memcpy(ch[nq], ch[q], sizeof ch[q]);
      for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
    }
  }
  return last = cur;
}
int c[maxn * 2], a[maxn * 2];
void rsort() {
  for (int i = 1; i <= sz; i++) c[i] = 0;
  for (int i = 1; i <= sz; i++) c[len[i]]++;
  for (int i = 1; i <= sz; i++) c[i] += c[i - 1];
  for (int i = 1; i <= sz; i++) a[c[len[i]]--] = i;
  for (int i = sz; i; i--) {
    int p = a[i];
    cnt[link[p]] += cnt[p];
  }
}

char s[maxn];
int n, p[30], pre[maxn], suf[maxn], sufM[maxn];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  int sum = 0;
  for (int i = 0; i < 26; i++) {
    scanf("%d", p + i);
    sum += p[i];
  }
  pre[0] = 1;
  for (int i = 1; i <= n; i++) {
    insert(s[i] - 'a', i);
    int cur = mul(inv(p[s[i] - 'a']), sum);
    pre[i] = mul(cur, pre[i - 1]);
  }
  rsort();
  sufM[n + 1] = 1;
  for (int i = n; i >= 1; i--) {
    int cur = mul(inv(p[s[i] - 'a']), sum);
    suf[i] = mul(cur, sufM[i + 1]);
    sufM[i] = suf[i];
    suf[i] = add(suf[i], suf[i + 1]);
  }
  int ans = 0;
  for (int i = 2; i <= sz; i++) {
    int r = R[i];
    int l = r - len[i] + 1;
    int fl = r - len[link[i]];

    int cur = mul(pre[r], inv(pre[fl]));
    int tot = sub(suf[l], suf[fl + 1]);
    tot = mul(tot, inv(sufM[fl + 1]));
    cur = mul(cur, tot);
    ans = add(ans, mul(1ll * cnt[i] * (cnt[i] + 1) / 2 % mod, cur));
  }
  printf("%d\n", ans);
  return 0;
}