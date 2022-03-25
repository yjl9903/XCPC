#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s;
    if (n % 2) return puts("No"), 0;
    vector<int> stk;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') stk.push_back(1);
        else if (!stk.empty()) stk.pop_back();
        else {
            c++;
        }
    }
    if (c == 0 && (int)stk.size() == 0) puts("Yes");
    else if (c == 1 && (int)stk.size() == 1) puts("Yes");
    else puts("No");
    return 0;
}