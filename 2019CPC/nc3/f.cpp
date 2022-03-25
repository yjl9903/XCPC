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
const int maxn = 1000000 + 5;

int n, q, op, tot = 1;
char s[maxn];

void append(char ch) {

}
int query(int k) {

}

int main() {
  scanf("%d", &q);
  for (n = 1; n <= q; n++) {
    scanf("%d", &op);
    if (op == 1) {
      char ch[5]; scanf("%s", ch);
      append(s[n] = ch[0]);
    } else if (op == 2) {
      int x; scanf("%d", &x);
      printf("%d\n", query(x));
    }
  }
  return 0;
}