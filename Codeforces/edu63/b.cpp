#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n; char s[maxn];

int main() {
    cin >> n >> s;
    int t = n - 11, c = 0;
    string v;
    for (int i = 0; i < n; i++) {
        if (c < t / 2 && s[i] == '8') {
            c++;
        } else v.push_back(s[i]);
    }
    // cout << v << endl;
    for (int i = 0; i <= t / 2 + t % 2; i++) {
        if (v[i] == '8') return puts("YES"), 0;
    }
    puts("NO");
    // for (int i = 0; i < t; i++) {
    //     if (s[i] == '8') {
    //         c++;
    //     }
    // }
    // if (c >= t / 2 + t % 2) puts("YES");
    // else puts("NO");
    return 0;
}