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
const int maxn = 100000 + 5;

struct node {
    string ad, nxt;
    int data;
} a[maxn];

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
    vector<string> ans;
    for (int i = 0; i <= sz / 2; i++) {
        if (i < sz - i - 1) {
            ans.push_back(v[sz - i - 1]);
            ans.push_back(v[i]);
        } else if (i == sz - i - 1) ans.push_back(v[i]);
    }
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << ' ' << dat[ans[i]] << ' ';
        if (i + 1 < (int)ans.size()) cout << ans[i + 1];
        else cout << -1;
        cout << endl;
    }
    return 0;
}