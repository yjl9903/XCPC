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
const int maxn = 100000 + 5;

string s;
bool check(string s) { 
    for (int i = 0; i < s.length(); i++) if (s[i] != s[s.length() - 1 - i]) return 0;
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> s;
    int n = s.length(), flag = 1;
    for (int i = 1; i < n / 2; i++) if (s[i] != s[i - 1]) {
        flag = 0; break;
    }
    if (flag) return puts("Impossible"), 0;
    for (int i = 1; i < n - 1; i++) {
        string t = s.substr(i) + s.substr(0, i);
        if (s == t) continue;
        if (check(t)) return puts("1"), 0;
    }
    puts("2");
    return 0;
}