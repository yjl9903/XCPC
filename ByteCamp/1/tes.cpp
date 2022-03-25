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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct Tree
{
	#define lc x<<1
	#define rc x<<1|1
	#define mid ((l+r)>>1)
	struct Node
	{
		ll a,b;
	}tree[600005];
	void insert(ll a, ll b, int l, int r, int x) {
    // if (!x) {
    //   x = ++tot; ls[x] = ls[pre]; rs[x] = rs[pre];
    // }
		if (tree[x].a * l + tree[x].b <= a * l + b && tree[x].a * r + tree[x].b <= a * r + b) {
			tree[x].a = a; tree[x].b = b;
			return;
		}
		if (tree[x].a * l + tree[x].b >= a * l + b && tree[x].a * r + tree[x].b >= a * r + b) {
      return ;
    }
    int m = (l + r) / 2;
		if (tree[x].a * m + tree[x].b < a * m + b) {
      swap(tree[x].a, a); swap(tree[x].b, b);
    }
		if (a < tree[x].a) insert(a, b, l, m, lc);
		else insert(a, b, m + 1, r, rc);
	}
	ll query(int p, int l, int r, int x) {
    if (!x) return -inf;
		ll ans = tree[x].a * p + tree[x].b;
		if (l == r) return ans;
    int m = (l + r) / 2;
		if (p <= m) ans= max(ans, query(p, l, m, lc));
		else ans = max(ans, query(p, m + 1, r, rc));
		return ans;
	}
	#undef lc
	#undef rc
	#undef mid
}T;

int main() {
  // T.insert(1, 1, 10, 4, -4);
  // T.insert(1, 1, 10, 5, -10);
  T.insert(4, -4, 1, 10, 1);
  T.insert(5, -10, 1, 10, 1);
  cout << T.query(3, 1, 10, 1) << endl;
  return 0;
}