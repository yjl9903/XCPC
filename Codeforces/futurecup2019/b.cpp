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

char s[maxn];

int main() {
    cin >> s + 1;
    int n = strlen(s + 1);
    int c = 0, tot = 0;
    for (int i = 1; i <= n; i++) if (s[i] == 'a') c++;
    if (c == n) return puts(s + 1), 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'a') tot++;
        if (tot == c && i - tot == n - i) {
            string p, t(s + i + 1);
            for (int j = 1; j <= i; j++) if (s[j] != 'a')p.push_back(s[j]);
            // cout << p << endl << t << endl;
            if (p == t) return s[i + 1] = 0, puts(s + 1), 0;
            else return puts(":("), 0;
        }   
    }
    puts(":(");
    return 0;
}