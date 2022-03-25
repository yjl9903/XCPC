#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;
const int maxm = 300000 + 5;

struct Event {
    int pos, tp, id;
    bool operator<(const Event& b) const {
        return pos < b.pos;
    }
};

vector<int> lsh;
int n;
PII a[maxm];

// vector<PII> evs[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
        lsh.push_back(2 * a[i].first);
        lsh.push_back(a[i].first + a[i].second);
        lsh.push_back(2 * a[i].second);
        // a[i].first *= 2; a[i].second *= 2;
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    int nn = (int)lsh.size();
    vector<Event> evs;
    for (int i = 1; i <= n; i++) {
        int l = lower_bound(lsh.begin(), lsh.end(), 2 * a[i].first) - lsh.begin() + 1;
        int m = lower_bound(lsh.begin(), lsh.end(), a[i].first + a[i].second) - lsh.begin() + 1;
        int r = lower_bound(lsh.begin(), lsh.end(), 2 * a[i].second) - lsh.begin() + 1;
        // evs[l].push_back({ 1, i });
        // evs[m + 1].push_back({ 2, i });
        // evs[r + 1].push_back({ 3, i });
        evs.push_back({ l, 1, i });
        evs.push_back({ m + 1, 2, i });
        evs.push_back({ r + 1, 3, i});
    }
    sort(evs.begin(), evs.end());
    ll sumd = 0, sumu = 0, ans = 0; 
    int szu = 0, szd = 0, j = 0, sz = (int)evs.size();
    for (int i = 1; i <= nn; i++) {
        while (j < sz && evs[j].pos == i) {
            int ev = evs[j].tp, id = evs[j].id;
            if (ev == 1) {
                szd++;
                sumd += 2ll * a[id].first;
            } else if (ev == 2) {
                szd--; szu++;
                sumd -= 2ll * a[id].first;
                sumu += 2ll * a[id].second;
            } else if (ev == 3) {
                szu--;
                sumu -= 2ll * a[id].second;
            }            
            j++;
        }
        ll tot = sumu - 1ll * szu * lsh[i - 1] + 1ll * szd * lsh[i - 1] - sumd;
        ans = max(ans, tot);
    }
    cout << ans;
    return 0;
}