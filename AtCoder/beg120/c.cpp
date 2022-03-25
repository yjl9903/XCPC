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
const int maxn = 100000 + 5;

char s[maxn]; int n;

int main() {
    scanf("%s", s); n = strlen(s);
    vector<char> v;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (v.empty()) v.push_back(s[i]);
        else if (v.back() != s[i]) {
            v.pop_back(); ans += 2;
        } else v.push_back(s[i]);
    }
    cout << ans << endl;
    return 0;
}