#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int change(vector<int> v){
    sort(v.begin(), v.end());
    int ans = 0;
    for (int x : v) ans = ans * 10 + x;
    return ans;
}
vector<int> change(int x){
    vector<int> ans;
    while (x){
        if (x % 10) ans.push_back(x % 10);
        x /= 10;
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int n, m, d;
vector<int> a, b;
map<PII,double> mp;

int main(){
    scanf("%d%d%d", &n, &m, &d); int s = 0;
    for (int i = 1, x; i <= n; i++) scanf("%d", &x), a.push_back(x), s += x;
    for (int i = 1, x; i <= m; i++) scanf("%d", &x), b.push_back(x), s += x;
    if (d >= s) return puts("1.00000000"), 0;
    mp[make_pair(change(a), change(b))] = 1.0;
    for (int i = 0; i < d; i++){
        map<PII,double> mp2;
        for (auto& t : mp){
            vector<int> x = change(t.first.first), y = change(t.first.second);
            double cnt = (int)x.size() + (int)y.size();
            for (int i = 0; i < x.size(); i++){
                // if (i > 0 && x[i] == x[i - 1]) continue;
                x[i]--;
                mp2[make_pair(change(x), change(y))] += t.second / cnt;
                x[i]++;
            }
            for (int i = 0; i < y.size(); i++){
                // if (i > 0 && y[i] == y[i - 1]) continue;
                y[i]--;
                mp2[make_pair(change(x), change(y))] += t.second / cnt;
                y[i]++;
            }
        }
        mp = mp2;
    }
    double ans = 0;
    for (auto& t : mp){
        if (t.first.second == 0) ans += t.second;
    }
    printf("%.8lf\n", ans);
    return 0;
}