#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct Ope{
    int l, r, id, lv;
    Ope(int ll = 0, int rr = 0, int ii = 0): l(ll), r(rr), id(ii){lv = 0;}
}ope2[maxn];
vector<Ope> ope, ope3;
set<int> s;
map<int, int> mp;
int n, q, a[maxn], ans[maxn], vis[maxn];

bool cmp(Ope a, Ope b){
    if (a.l == b.l) return a.id < b.id;
    return a.l < b.l;
}
bool cmp2(Ope a, Ope b){
    if (a.r == b.r) return a.id < b.id;
    return a.r > b.r;
}

void cdq(int L, int R){
    if (L >= R) return;
    int m = (L + R) >> 1;
    cdq(L, m);
    for (int i = L; i <= R; i++) ope2[i] = ope[i];
    sort(ope2 + L, ope2 + m + 1, cmp2); sort(ope2 + m + 1, ope2 + R, cmp2);
    int j = L;
    for (int i = m + 1; i <= R; i++){
        while (j <= m && ope2[j].r >= ope2[i].r) j++;
        // lv[ope2[i].id] += j - L + 1;
    }
    cdq(m + 1, R);
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        ope.clear(); ope3.clear(); s.clear(); mp.clear(); ms(ans, 0); ms(vis, 0);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 0; i < q; i++){
            int x, y; scanf("%d%d", &x, &y);
            ope.push_back(Ope(x, y, i));
        }
        sort(ope.begin(), ope.end(), cmp);
        // cdq(0, ope.size() - 1);
        
        // cout << endl;
        // for (int i = 0; i < q; i++) cout << lv[i] << endl;
        // cout << endl;

        // int l = 1, r = n;
        // for (int i = 0; i < ope.size(); i++){
        //     while (l <= ope[i].l) s.insert(a[l]), l++;
        //     // while (r >= ope3[i].r) s.insert(a[r]), r--; 
        //     if (r > ope[i].r){
        //         while (r > ope[i].r) s.insert(a[r]), r--;
        //     }
        //     else if (r < ope[i].r){
        //         while (r < ope[i].r) s.erase(a[r]), r++;
        //     }
        //     s.insert(a[r]);
        //     ans[ope[i].id] = s.size();
        // }
        int l = 1, r = n; mp[a[r]]++;
        for (int i = 0; i < ope.size(); i++){
            while (r < ope[i].r){
                mp[a[r]]--;
                // cout << a[r] << ' ' << mp[a[r]] << endl;
                if (mp[a[r]] == 0) mp.erase(a[r]);
                r++;
            }
            while (l <= ope[i].l) mp[a[l]]++, l++;
            while (r > ope[i].r) r--, mp[a[r]]++;
            ans[ope[i].id] = mp.size();
        }
        for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
    }
    return 0;
}