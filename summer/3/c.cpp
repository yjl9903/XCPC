#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<ll,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, m, l;
ll f[maxn];

int main() {
	int T, kase = 0; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &l, &n, &m);
		priority_queue<PII,vector<PII>, greater<PII> > pq;
		for (int i = 1, x; i <= n; i++) {
			scanf("%d", &x); pq.push({x, x});
		}
		for (int i = 1; i <= l; i++) {
			PII tp = pq.top(); pq.pop();
			f[i] = tp.first;
			pq.push({ tp.first + tp.second, tp.second });
		}
		while (!pq.empty()) pq.pop();
		for (int i = 1, x; i <= m; i++) {
			scanf("%d", &x); pq.push({x, x});
		}
		for (int i = l; i >= 1; i--) {
			PII tp = pq.top(); pq.pop();
			f[i] += tp.first;
			pq.push({ tp.first + tp.second, tp.second });
		}
		ll ans = 0;
		for (int i = 1; i <= l; i++) ans = max(f[i], ans);
		printf("Case #%d: %lld\n", ++kase, ans);
	}
	return 0;
}