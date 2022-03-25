#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn = 1000 + 5;

PII a[maxn];
int n, vis[maxn];

int main(){
    int T; cin >> T;
    while (T--){
        memset(vis, 0, sizeof vis);
        cin >> n;
        for (int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
            a[i].first *= 2;
            a[i].second *= 2;
        }
        sort(a, a + n);
        int mid = (a[0].first + a[n - 1].first) / 2, flag = 1;
        for (int i = 0; i < n; i++){
            if (!vis[i] && a[i].first == mid)
                vis[i] = 1;
            else if (!vis[i]){
                PII t = make_pair(2 * mid - a[i].first, a[i].second);
                int x = lower_bound(a, a + n, t) - a;
                while (vis[x] && a[x].first == t.first && a[x].second == t.second)
                    x++;
                if (a[x].first != t.first || a[x].second != t.second){
                    flag = 0; break;
                }
                vis[x] = 1;
            }
        }
        cout << (flag ? "YES" : "NO") << endl;
    }
    return 0;
}