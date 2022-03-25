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
const int maxn = 1000 + 5;

int n;

int main() {
    cin >> n;
    int m = (n + 1) / 2 + (n + 1) % 2;
    cout << m << '\n';
    int c = 1;
    for (int i = 1; c <= n && i <= m; c++, i++) {
        printf("%d %d\n", 1, i);
    }
    for (int i = 2; c <= n && i <= m; c++, i++) {
        printf("%d %d\n", i, m);
    }
    return 0;
}