#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 150000  + 5;

int n;
char l[maxn], r[maxn];

int main() {
    scanf("%d%s%s", &n, l + 1, r + 1);
    vector<PII> ans;
    vector<int> r1, r2;
    for (int i = 1; i <= n; i++) {
        if (l[i] == '?') r1.push_back(i);
        if (r[i] == '?') r2.push_back(i);
    }
    for (char ch = 'a'; ch <= 'z'; ch++) {
        vector<int> p1, p2;
        for (int i = 1; i <= n; i++) {
            if (l[i] == ch) p1.push_back(i);
            if (r[i] == ch) p2.push_back(i);
        }
        while (!r1.empty() && (int)p1.size() < (int)p2.size()) {
            int x = r1.back(); r1.pop_back(); p1.push_back(x);
        }
        while (!r2.empty() && (int)p2.size() < (int)p1.size()) {
            int x = r2.back(); r2.pop_back(); p2.push_back(x);
        }
        for (int i = 0; i < min((int)p1.size(), (int)p2.size()); i++) {
            ans.push_back({p1[i], p2[i]});
        }
    }
    for (int i = 0; i < min((int)r1.size(), (int)r2.size()); i++) {
        ans.push_back({r1[i], r2[i]});
    }
    printf("%d\n", (int)ans.size());
    for (auto& x: ans) printf("%d %d\n", x.first, x.second);
    return 0;
}