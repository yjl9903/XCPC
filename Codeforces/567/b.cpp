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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
char s[maxn], t[maxn], p[maxn];

string add(string s, string t) {
    string r;
    int mn = min(s.length(), t.length()), g = 0;
    for (int i = 0; i < mn; i++) {
        int tot = (s[i] - '0') + (t[i] - '0') + g;
        r += tot % 10 + '0'; g = tot / 10;
    }
    for (int i = mn; i < (int)s.length(); i++) {
        int tot = (s[i] - '0') + g;
        r += tot % 10 + '0'; g = tot / 10;
    }
    for (int i = mn; i < (int)t.length(); i++) {
        int tot = (t[i] - '0') + g;
        r += tot % 10 + '0'; g = tot / 10;
    }
    if (g) r += "1";
    return r;
}

int main() {
    scanf("%d%s", &n, s);
    reverse(s, s + n);
    int mid = n / 2, last = 0;
    for (int i = 0; i < mid; i++) {
        if (s[i] != '0') last = i;
    }
    string a(s); a.resize(last + 1);
    string b(s + last + 1);
    // cout << a << endl << b << endl;
    string r = add(a, b);
    // cout << r1 << endl;
    for (int i = mid; i < n; i++) {
        if (s[i] = '0') {
            last = i; break;
        }
    }
    string a2(s); a.resize(last + 1);
    string b2(s + last + 1);
    string r2 = add(a2, b2);
    reverse(r.begin(), r.end());
    reverse(r2.begin(), r2.end());
    if ((int)r.length() < (int)r2.length()) cout << r;
    else if ((int)r.length() > (int)r2.length()) cout << r2;
    else cout << min(r, r2);
    return 0;
}