#include <bits/stdc++.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, x[maxn], y[maxn];

int main() {
  scanf("%d", &n);
  vector<int> p;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", x + i, y + i);
    p.push_back(i);
  }
  long double sum = 0;
  int cnt = 0;
  auto cal = [&](int a, int b) -> long double {
    return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
  };
  do {
    for (int i = 1; i < n; i++) {
      sum += cal(p[i - 1], p[i]);
    }
    cnt++;
  } while (next_permutation(begin(p), end(p)));
  cout << fixed << setprecision(8);
  cout << sum / cnt;
  return 0;
}