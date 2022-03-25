#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int n, k;
set<int> st;
vector<vector<int>> ans;

int main() {
    cin >> n >> k;
    for (int i = 1; i < maxn; i++) st.insert(i);
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> v;
        for (int x: st) {
            int flag = 1;
            for (int i = 0; i < v.size(); i++) if (gcd(v[i], x) != 1) {
                flag = 0; break;
            }
            if (flag) v.push_back(x);
            if ((int)v.size() == 4) break; 
        }
        for (int& x: v) st.erase(x);
        mx = max(mx, v.back());
        ans.push_back(v);
    }
    cout << mx * k << endl;
    for (int i = 0; i < n; i++) {
        for (int& x: ans[i]) printf("%d ", x * k);
        puts("");
    }
    return 0;
}