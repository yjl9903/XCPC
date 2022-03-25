#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pLL;
const ll mod = 1e9 + 7;
const int maxn = 1e6 + 20;

int n, k, ans, sum;
char s[maxn];
bool vis[maxn];
int v[maxn], L[maxn], R[maxn];

struct data {
  int l, r, val;
} a[maxn];

struct node {
  int num, val;
  bool operator<(const node &x) const { return x.val < val; }
};
priority_queue<node> q;

void del(int x) {
  a[a[x].r].l = a[x].l;
  a[a[x].l].r = a[x].r;
}

int main() {
  scanf("%d %d", &n, &k);
  scanf("%s", s + 1);
  for (int i = 1; i <= n - 1; i++) {
    a[i].val = (s[i] != 'a') + (s[i + 1] != 'c');
    a[i].l = i - 1, a[i].r = i + 1;
    L[i] = R[i] = i;
    q.push(node{i, a[i].val});
  }

  a[0].val = a[n].val = 100000000;
  for (int i = 1; i <= n / 2; i++) {
    while (vis[q.top().num]) q.pop();
    node tmp = q.top();
    q.pop();
    sum += tmp.val;

    if (sum <= k)
      ans = i;
    else
      break;

    vis[a[tmp.num].l] = vis[a[tmp.num].r] = 1;
    v[L[tmp.num]] ^= 1, v[R[tmp.num] + 1] ^= 1;

    L[tmp.num] = L[a[tmp.num].l];
    R[tmp.num] = R[a[tmp.num].r];
    a[tmp.num].val = a[a[tmp.num].l].val + a[a[tmp.num].r].val - a[tmp.num].val;
    del(a[tmp.num].l), del(a[tmp.num].r);

    q.push(node{tmp.num, a[tmp.num].val});
  }

  printf("%d\n", ans);
  for (int i = 1; i <= n; i++) {
    // dbg(i, jd[i]);
    v[i] ^= v[i - 1];
    if (v[i]) s[i] = 'a', s[i + 1] = 'c';
  }
  printf("%s", s + 1);
  return 0;
}