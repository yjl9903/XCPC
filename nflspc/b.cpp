#include <bits/stdc++.h>
#include <sys/timeb.h>
using namespace std;

vector<bool> solve();
bool ask(int l, int r);

using PII = pair<int,int>;

vector<bool> solve() {
	mt19937 rnd(time(0));
	vector<bool> ans(10000, 0);
	vector<PII> p, p2;
	int B = 2;
	for (int i = 0; i < 10000; i += B) p.push_back({i, i + B - 1});
	shuffle(p.begin(), p.end(), rnd);
	int sum = 0, cnt = 0;
	for (auto& x: p) {
		if (ask(x.first, x.second)) {
			p2.push_back(x);
		}
	}
	for (auto& x: p2) {
		for (int i = x.first; sum < 1000 && i <= x.second; i++) {
			if (ask(i, i)) {
				ans[i] = 1; sum++;
			}
		}
		if (sum == 1000) break;
	}
	// for (int x: ans) printf("%d ", x);
	// cout << endl;
	// cout << cnt << endl;
	return ans;
}

