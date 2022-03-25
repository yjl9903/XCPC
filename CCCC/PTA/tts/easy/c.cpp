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

int a, b;

int main() {
    cin >> a >> b;
    int ans = a * b;
    string s;
    while (ans) {
        // putchar(ans % 10 + '0');
        s += ans % 10 + '0';
        ans /= 10;
    }
    if (s == "0") puts("0");
    else {
        int flag = 0;
        for (int i = 0; i < s.length(); i++) if (flag || s[i] != '0') {
            flag = 1;
            putchar(s[i]);
        }
    }
    return 0;
}