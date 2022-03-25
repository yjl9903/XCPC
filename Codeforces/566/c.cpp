#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, vis[maxn], c[maxn];
string word[maxn];
map< PII,vector<int> > mp;
map<int,vector<int> > mp2;

int check(char s) {
    if (s == 'a') return 1;
    if (s == 'e') return 2;
    if (s == 'o') return 3;
    if (s == 'i') return 4;
    if (s == 'u') return 5;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> word[i];
        int cnt = 0, last = 0;
        for (auto& ch: word[i]) {
            int x = check(ch);
            if (x) cnt++, last = x;
        }
        c[i] = cnt;
        mp[{cnt, last}].push_back(i);
    }
    vector<PII> v, v2;
    for (auto& x: mp) {
        int sz = (int)x.second.size();
        for (int j = 0; j + 1 < sz; j += 2) {
            v.push_back({x.second[j], x.second[j + 1]});
        }
        if (sz % 2) {
            mp2[x.first.first].push_back(x.second.back());
        }
    }
    for (auto& x: mp2) {
        int sz = (int)x.second.size();
        for (int j = 0; j + 1 < sz; j += 2) {
            v2.push_back({x.second[j], x.second[j + 1]});
        }
    }
    vector< pair<PII,PII> > ans;
    int sz1 = (int)v.size(), sz2 = (int)v2.size();
    for (int i = 0; i < min(sz1, sz2); i++) {
        ans.push_back({ v2[i], v[i] });
    }
    for (int i = min(sz1, sz2); i + 1 < sz1; i += 2) {
        ans.push_back({ v[i], v[i + 1] });
    }
    cout << ans.size() << '\n';
    for (auto& x: ans) {
        cout << word[x.first.first] << ' ' << word[x.second.first] << '\n';
        cout << word[x.first.second] << ' ' << word[x.second.second] << '\n';
    }
    return 0;
}