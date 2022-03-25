#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100 + 5;

char s[maxn][maxn];
int n;

int get(string tag, string s) {
    string x = s;
    x += s;
    // cout << x << ' ';
    // cout << x.find(tag) << endl;
    return x.find(tag);
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", s[i]);
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        int sum = 0, flag = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int t = get(s[i], s[j]);
            // cout << t << endl;
            if (t == -1) {
                flag = 0; break;
            }
            sum += t;
        }
        if (flag) ans = min(sum, ans);
        // puts("");
    }
    if (ans == (int)1e9) puts("-1");
    else cout << ans << endl;
    return 0;
}