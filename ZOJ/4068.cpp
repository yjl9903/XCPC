#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n, sy, l[maxn], r[maxn], cnt[maxn];
map<int,int> mp, mp2[maxn];
PII a[maxn];
int dis(PII a, PII b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(l, 0); ms(r, 0); ms(cnt, 0);
        scanf("%d%d", &n, &sy);
        for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second), cnt[a[i].first]++;
        sort(a, a + n);
        int inf = a[n - 1].first + 1;

        for (int i = 0; i < inf; i++) mp2[i].clear();
        for (int i = 0; i < n; i++) mp2[a[i].first][abs(a[i].second - sy)]++;
        PII h = make_pair(inf, sy); mp.clear();
        for (int i = 0; i < n; i++){
            if (mp[dis(a[i], h)] == 0){
                mp[dis(a[i], h)]++;
                mp2[a[i].first][abs(a[i].second - sy)]--;
                l[a[i].first]++;
            }
            else {
                if (mp2[a[i].first][abs(a[i].second - sy)] == 2){
                    mp2[a[i].first][abs(a[i].second - sy)]--;
                }
                else {
                    mp[dis(a[i], h)] = 0;
                    l[a[i].first]--;
                }
            }
        }
        for (int i = 1; i <= inf; i++) l[i] += l[i - 1];

        for (int i = 0; i < inf; i++) mp2[i].clear();
        for (int i = 0; i < n; i++) mp2[a[i].first][abs(a[i].second - sy)]++;
        mp.clear(); h = make_pair(-inf, sy);
        for (int i = n - 1; i >= 0; i--){
            if (mp[dis(a[i], h)] == 0){
                mp[dis(a[i], h)]++;
                mp2[a[i].first][abs(a[i].second - sy)]--;
                r[a[i].first]++;
            }
            else {
                if (mp2[a[i].first][abs(a[i].second - sy)] == 2){
                    mp2[a[i].first][abs(a[i].second - sy)]--;
                }
                else {
                    mp[dis(a[i], h)] = 0;
                    r[a[i].first]--;                
                }
            }
        }
        for (int i = inf - 1; i >= 0; i--) r[i] += r[i + 1];

        int ans1 = r[1], ans2 = r[1];
        for (int i = 1; i <= inf; i++){
            ans1 = min(l[i - 1] + r[i + 1] + cnt[i], ans1);
            ans2 = max(l[i - 1] + r[i + 1] + cnt[i], ans2);
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}