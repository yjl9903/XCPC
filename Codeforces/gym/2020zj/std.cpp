#include <bits/stdc++.h>
using namespace std;
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
typedef long long LL;
const int N = 500 + 10;
const double inf = 1e12;
const double eps = 1e-7;
int T, n, m;
 
struct P {
	LL x, y;
	void read() {
		scanf("%lld%lld",&x,&y);
	}
} p[N], s[N], t[N];
 
 
pair<double,double> solve(int i,int j) {
	P A=p[i], B=s[j], C=t[j];
	P L = (P){-inf, 0};
	P R = (P){+inf, 0};
	//printf("A = %lld,%lld, B = %lld,%lld C = %lld,%lld\n", A.x,A.y,B.x,B.y,C.x,C.y);
	LL dy1 = A.y - B.y;
 
	vector<double> vec;
	if (dy1 > 0) {
		double posx1 = A.x + 1.0 * (B.x - A.x) * A.y / dy1;
		vec.push_back(posx1);
		//printf("! posx1 = %.5f\n", posx1);
	}
 
	LL dy2 = A.y - C.y;
	if (dy2 > 0) {
		double posx2 = A.x + 1.0 * (C.x - A.x) * A.y / dy2;
		vec.push_back(posx2);
	}
	if (vec.size() == 2) {
		sort(vec.begin(), vec.end());
		return make_pair(vec[0], vec[1]);
	}
 
	if (vec.size() == 0) {
		return make_pair(0, 0);
	}
	double ratio = 1.0 * (A.y - B.y) / (C.y - B.y);
	double X = B.x + (C.x - B.x) * ratio;
	if (X < A.x) {
		return make_pair(-inf, vec[0]);
	} 
	if (abs(X - A.x) < eps) {
		//if (abs(X - B.x) < eps || abs(X - C.x) < eps) return make_pair(0,0);
		return make_pair(-inf, inf);
	}
	return make_pair(vec[0], inf);
}
 
vector< pair<double, pair<int,int> > > events;
set<int> st;
int main() {
	scanf("%d", &T);
	while (T --) {
		events.clear(); st.clear();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			p[i].read();
		}
		for(int i=1;i<=m;i++){
			s[i].read(); t[i].read();
		}
		for(int i=1;i<=n;i++){
			vector< pair<double,double> > segs;
			for(int j=1;j<=m;j++){
				segs.push_back(solve(i, j));
				// printf("i = %d, j = %d (%.5f, %.5f)\n", i, j, segs.back().first, segs.back().second);
			}
      for (auto x: segs) {
        // dbg(x.first, x.second);
      }
			sort(segs.begin(), segs.end());
			for (int x = 0, y = 0; x < segs.size(); x = y) {
				double r = segs[x].second;
				while (y < segs.size()) {
					//printf("y = %d, seg = [%.5f, %.5f]\n", y, segs[y].first, segs[y].second);
					if (segs[y].first <= r) {
						r = max(r, segs[y].second);
					} else {
						break;
					}
					y ++;
				}
				// printf("[%.5f, %.5f)\n", segs[x].first, r);
				events.push_back(make_pair( segs[x].first, make_pair(i, +1) ));
				events.push_back(make_pair( r, make_pair(i, -1) ));
			}
		}
 
		sort(events.begin(), events.end());
		double prev = -inf, ans = 0;
		for (auto p: events) {
			// printf("events: %.5f %d %d\n", p.first, p.second.first, p.second.second);
			int sz = st.size();
			// printf("size = %d\n", sz);
			if (p.second.second == -1) {
				st.erase(p.second.first);
			} else {
				st.insert(p.second.first);
			}
			if (sz == n) {
        dbg(prev, p.first);
				ans += p.first - prev;
			}
			prev = p.first;
		}
		//printf("ans = \n");
		if (ans > 1e9 + eps) printf("-1\n");
		else printf("%.8f\n", ans);
	}
}