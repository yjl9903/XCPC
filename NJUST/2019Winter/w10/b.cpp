#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int a, b, c, m;
vector<int> va, vb;

int main() {
    scanf("%d%d%d%d", &a, &b, &c, &m);
    for (int i = 1; i <= m; i++) {
        int x; char s[10];
        scanf("%d%s", &x, s);
        if (s[0] == 'U') va.push_back(x);
        else vb.push_back(x);
    }
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    vector<PII> v;
    int cnt = 0, totx = 0, toty = 0; ll sum = 0;
    for (int i = 0; i < va.size(); i++) {
        if (totx < a) {
            totx++; sum += va[i];
        } else v.push_back({va[i], 0});
    }
    for (int i = 0; i < vb.size(); i++) {
        if (toty < b) {
            toty++; sum += vb[i];
        } else v.push_back({vb[i], 1});
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second == 0) {
            if (totx < a) totx++, sum += v[i].first;
            else if (cnt < c) cnt++, sum += v[i].first;
        } else {
            if (toty < b) toty++, sum += v[i].first;
            else if (cnt < c) cnt++, sum += v[i].first;
        }
    }
    cout << cnt + totx + toty << ' ' << sum << endl;
    return 0;
}