#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n;
vector<vector<ll> > v[2];
map<ll,int> mp;

int main(){
    scanf("%d", &n);
    for (int i = 1, t, s; i <= n; i++){
        scanf("%d%d", &t, &s);
        vector<ll> a; ll x;
        while (s--){
            scanf("%lld", &x);
            a.push_back(x);
        }
        v[t - 1].push_back(a);
    }
    if (v[0].size() == 0){
        set<ll> s;
        for (auto& t : v[1]) for (ll& x : t) s.insert(x);
        printf("%lld\n", ll(1e18) - ll(s.size()));
    }
    else {
        int sz = v[0].size();
        for (auto& t : v[0]) for (ll& x : t){
            mp[x]++;
        }
        set<ll> s;
        for (auto& x : mp){
            if (x.second == sz){
                s.insert(x.first);
            }
        }
        for (auto& t : v[1]) for (ll& x : t){
            s.erase(x);
        }
        printf("%d\n", s.size());
    }
    return 0;
}