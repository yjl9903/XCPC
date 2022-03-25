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
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct Result {
  int discard;
  vector<int> listen;

  bool operator<(const Result& rhs) const {
    return discard < rhs.discard;
  }
};

char buf[maxn];
int cnt[64];
set< vector<int> > all;

void init() {
  vector<int> cnt(9, 0);
  function<void(int)> dfs = [&](int x) {
    if (x == 5) return ;
    all.insert(cnt);
    for (int i = 1; i <= 7; i++) {
      cnt[i - 1]++;
      cnt[i]++;
      cnt[i + 1]++;
      dfs(x + 1);
      cnt[i - 1]--;
      cnt[i]--;
      cnt[i + 1]--;
    }
    for (int i = 0; i < 9; i++) {
      cnt[i] += 3;
      dfs(x + 1);
      cnt[i] -= 3;
    }
  };
  dfs(0);
}

int id(char x, char y) {
  int v = x - '0';
  if (y == 'w') {
    return v;
  } else if (y == 'b') {
    return v + 9;
  } else if (y == 's') {
    return v + 18;
  } else {
    return v + 27;
  }
}

string tostr(int x) {
  string res;
  if (x <= 9) {
    res += char(x + '0');
    res += 'w';
  } else if (x <= 18) {
    res += char((x - 9) + '0');
    res += 'b';
  } else if (x <= 27) {
    res += char((x - 18) + '0');
    res += 's';
  } else if (x <= 34) {
    res += char((x - 27) + '0');
    res += 'z';
  } else {
    assert(false);
  }
  return res;
}

bool check() {
  vector<int> cur(9, 0);
  auto checkV = [&](int i) {
    if (i == 3) {
      for (int i = 28; i <= 34; i++) {
        if (cnt[i] % 3 != 0) return false;
      }
      return true;
    }
    cur.assign(9, 0);
    int sum = 0;
    for (int j = 1; j <= 9; j++) {
      cur[j - 1] = cnt[i * 9 + j];
      sum += cur[j - 1];
    }
    if (sum == 0) return true;
    return sum % 3 == 0 && all.count(cur);
  };
  auto checkQ = [&](int i) {
    if (i == 3) {
      bool flag = false;
      for (int i = 28; i <= 34; i++) {
        if (cnt[i] % 3 == 1) {
          return false;
        } else if (cnt[i] % 3 == 2) {
          if (flag) return false;
          flag = true;
        }
      }
      return flag;
    }
    int sum = 0;
    for (int j = 1; j <= 9; j++) {
      sum += cnt[i * 9 + j];
    }
    if (sum % 3 != 2) {
      return false;
    } else {
      for (int j = 1; j <= 9; j++) {
        if (cnt[i * 9 + j] >= 2) {
          cnt[i * 9 + j] -= 2;
          bool r = checkV(i);
          cnt[i * 9 + j] += 2;
          if (r) return true;
        }
      }
      return false;
    }
  };
  bool q[] = { checkQ(0), checkQ(1), checkQ(2), checkQ(3) };
  bool v[] = { checkV(0), checkV(1), checkV(2), checkV(3) };
  for (int i = 0; i < 4; i++) {
    bool flag = q[i];
    // dbg(i, q[i], v[i]);
    for (int j = 0; j < 4 && flag; j++) {
      if (i == j) continue;
      flag &= v[j];
    }
    if (flag) return true;
  }
  return false;
}

int main() {
  int T; scanf("%d", &T);
  init();
  while (T--) {
    scanf("%s", buf + 1);
    ms(cnt, 0);
    for (int i = 1; i <= 27; i += 2) {
      cnt[id(buf[i], buf[i + 1])]++;
    }
    if (check()) {
      puts("Tsumo!");
    } else {
      vector<Result> ans;
      set<int> st;
      for (int i = 1; i <= 27; i += 2) {
        int cur = id(buf[i], buf[i + 1]);
        if (st.count(cur)) continue;
        st.insert(cur);
        cnt[cur]--;
        vector<int> vec;
        for (int j = 1; j <= 34; j++) {
          if (cur == j) continue;
          cnt[j]++;
          bool r = check();
          cnt[j]--;
          if (r) vec.push_back(j);
        }
        cnt[cur]++;
        if (!vec.empty()) {
          ans.push_back({ cur, vec });
        }
      }
      sort(ans.begin(), ans.end());
      printf("%d\n", ans.size());
      for (auto& x: ans) {
        printf("%s ", tostr(x.discard).c_str());
        sort(x.listen.begin(), x.listen.end());
        for (int y: x.listen) {
          printf("%s", tostr(y).c_str());
        }
        puts("");
      }
    }
  }
  return 0;
}