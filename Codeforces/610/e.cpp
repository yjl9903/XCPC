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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
 
int query(string s) {
  cout << s << endl;
  int x; cin >> x;
  if (x == 0 || x == -1) exit(0);
  return x;
}
 
int main() {
  int n1 = query("a");
  int n2 = query("b");
  if (n1 < n2) {
    assert(n1 + 2 == n2);
    string s;
    for (int i = 0; i < n1 + 1; i++) s += 'a';
    query(s);
  } else if (n1 > n2) {
    assert(n2 + 2 == n1);
    string s;
    for (int i = 0; i < n2 + 1; i++) s += 'b';
    query(s);
  }
  int n = n1 + 1;
  string ans;
  for (int i = 0; i < n; i++) ans += 'a';
  int y = query(ans); // b: y
  for (int i = 0; i < n; i++) {
    ans[i] = 'b';
    int r = query(ans);
    if (r < y) {
      y = r;
    } else {
      ans[i] = 'a';
    }
  }
  query(ans);
  return 0;
}