#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int maxn = 100000 + 5;

int n, m;

struct Node {
  int cnt;
  vector<int> vec;

  bool operator < (const Node& rhs) const {
    if (cnt != rhs.cnt) {
      return cnt > rhs.cnt;
    } else {
      return vec < rhs.vec;
    }
  }
};

int main() {
  scanf("%d%d", &n, &m);
  map<vector<int>, int> mp;
  for (int i = 1; i <= n; i++) {
    vector<int> vec; 
    for (int j = 1; j <= m; j++) {
      int x;
      scanf("%d", &x);
      vec.push_back(x);
    }
    mp[vec]++;
  }
  vector<Node> all;
  for (auto& x: mp) {
    all.push_back({ x.second, x.first });
  }
  sort(all.begin(), all.end());
  printf("%d\n", all.size());
  for (auto& x: all) {
    printf("%d", x.cnt);
    for (int j = 0; j < m; j++) {
      printf(" %d", x.vec[j]);
    }
    puts("");
  }
  return 0;
}