#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n;
string st;
char tmp[10], tmp2[10];
vector<string> v;
map<string,int> dat;
map<string,string> nxt;

int main() {
    scanf("%s%d", tmp, &n);
    st = tmp;
    for (int i = 0, x; i < n; i++) {
        scanf("%s%d%s", tmp, &x, tmp2);
        dat[tmp] = x;
        nxt[tmp] = string(tmp2);
    }
    string tot = st, ed = "-1";
    while (tot != ed) {
        v.push_back(tot);
        tot = nxt[tot];
    }
    int sz = (int)v.size();
    vector<string> ans1, ans2;
    set<int> st;
    for (int i = 0; i < sz; i++) {
        if (st.count(abs(dat[v[i]]))) {
            ans2.push_back(v[i]);
        } else {
            ans1.push_back(v[i]);
            st.insert(abs(dat[v[i]]));
        }
    }
    for (int i = 0; i < (int)ans1.size(); i++) {
        printf("%s %d ", ans1[i].c_str(), dat[ans1[i]]);
        if (i + 1 == (int)ans1.size()) printf("-1");
        else printf("%s", ans1[i + 1].c_str());
        puts("");
    }
    for (int i = 0; i < (int)ans2.size(); i++) {
        printf("%s %d ", ans2[i].c_str(), dat[ans2[i]]);
        if (i + 1 == (int)ans2.size()) printf("-1");
        else printf("%s", ans2[i + 1].c_str());
        puts("");
    }
    return 0;
}