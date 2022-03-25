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

char s[maxn];

int main() {
    cin >> s;
    int c = 0, n = strlen(s);
    for (int i = 0; i < n; i++) if (s[i] == 'a') c++;
    cout << max(0, min(2 * c - 1, n));
    return 0;
}