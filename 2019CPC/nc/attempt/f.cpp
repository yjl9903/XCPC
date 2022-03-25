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

int n, ans;

string s;
void dfs(int k) {
    if (k == n) {
        if (s.find("aba") != -1) ans++;
        return ;
    }
    for (int i = 0; i < 26; i++) {
        s.push_back(i + 'a');
        dfs(k + 1);
        s.pop_back();
    }
}

int main() {
    cin >> n;
    dfs(0);
    cout << ans;
    return 0;
}