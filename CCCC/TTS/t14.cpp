#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int maxn = 100000 + 5;

int n, m, h[maxn], fail[maxn];
vector<int> a[128];
vector<int> match[maxn];

bool ok = false;
set<int> st;
vector<int> stk;
void dfs(int u) {
  for (int x: match[u]) {
    if (st.count(x)) continue;
    st.insert(x);
    stk.push_back(x);
    int nxt = u + (int)a[x].size() - 1;
    if (nxt == n) {
      ok = true;
      return ;
    } else {
      dfs(nxt);
      if (ok) return ;
    }
    st.erase(x);
    stk.pop_back();
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", h + i);
  }
  scanf("%d", &m);
  int sum = 0;
  for (int i = 1; i <= m; i++) {
    int k;
    scanf("%d", &k);
    sum += k;
    assert(k >= 2);
    vector<int> vec;
    for (int j = 0; j < k; j++) {
      int x;
      scanf("%d", &x);
      vec.push_back(x);
    }
    a[i] = vec;
    fail[1] = 0;
    for (int j = 2; j <= k; j++) {
      int cur = fail[j - 1];
      while (cur && vec[cur] != vec[j - 1]) cur = fail[cur];
      if (vec[cur] == vec[j - 1]) cur++;
      fail[j] = cur;
    }
    int id = i;
    for (int i = 1, cur = 0; i <= n; i++) {
      while (cur && h[i] != vec[cur]) {
        cur = fail[cur];
      }
      if (h[i] == vec[cur]) cur++;
      if (cur == k) {
        match[i - k + 1].push_back(id);
        cur = fail[cur];
      }
    }
  }
  assert(n == sum - m + 1);
  // for (int i = 1; i <= n; i++) {
  //   // cout << i << ": ";
  //   // for (int x: match[i]) cout << x << " ";
  //   // cout << endl;
  //   if (!match[i].empty()) {
  //     cnt++;
  //     printf("%d%c", match[i][0], " \n"[cnt == m]);
  //   }
  // }
  dfs(1);
  assert(ok);
  assert(st.size() == m);
  int cnt = 0;
  for (auto& x: stk) {
    cnt++;
    printf("%d%c", x, " \n"[cnt == m]);
  }
  return 0;
}