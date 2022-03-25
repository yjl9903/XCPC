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

int n, lk[] = {4, 7, 47, 74, 447, 474, 477, 747, 774 };

int main() {
    cin >> n;
    for (int i = 0; i < 9; i++) if (n % lk[i] == 0) return puts("YES"), 0;
    puts("NO");
    return 0;
}