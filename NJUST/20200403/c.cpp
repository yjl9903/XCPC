#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int ans;
set<vector<int> > st;

void dfs(const vector<int>& cnt) {
  if (st.count(cnt)) return ;
  int sum = 0;
  for (int i = 0; i < 13; i++) {
    sum += (i + 1) * cnt[i];
    // cout << cnt[i] << ' ';
  }
  // cout << ", sum: " << sum << endl;
  ans = min(ans, sum);
  st.insert(cnt);
  auto now = cnt;
  for (int i = 0; i < 13; i++) {
    for (int j = 3; j <= cnt[i]; j++) {
      now[i] -= j;
      dfs(now);
      now[i] += j;
    }
  }
  for (int i = 0; i < 13; i++) {
    for (int j = i + 2; j < 13; j++) {
      bool flag = true;
      for (int k = i; k <= j && flag; k++) {
        // flag &= cnt[k];
        if (!cnt[k]) {
          flag = false;
        }
      }
      if (flag) {
        for (int k = i; k <= j; k++) {
          now[k]--;
        }
        dfs(now);
        for (int k = i; k <= j; k++) {
          now[k]++;
        }
      }
    }
  }
}

int main() {
  vector<int> cnt(13, 0);
  for (int i = 0, x; i < 7; i++) {
    scanf("%d", &x);
    ans += x;
    cnt[x - 1]++;
  }
  dfs(cnt);
  printf("%d\n", ans);
  return 0;
}