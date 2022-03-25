#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int maxn = 100000 + 5;

char s[maxn];
int n, m, a[maxn];

int main() {
  vector<int> vec;
  scanf("%d%d%d", &a[1], &a[2], &n);
  vec.push_back(a[1]);
  vec.push_back(a[2]);
  for (int i = 0; i < n; i++) {
    int x = vec[i] * vec[i + 1];
    if (x < 10) {
      vec.push_back(x);
    } else {
      vec.push_back(x / 10);
      vec.push_back(x % 10);
    }
  }
  for (int i = 0; i < n; i++) {
    printf("%d%c", vec[i], " \n"[i + 1 == n]);
  }
  return 0;
}