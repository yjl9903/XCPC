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

int n, a[maxn];

int main() {
    int ans = 0;
    cin >> n; 
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int x = a[3];
    sort(a + 1, a + 1 + n);
    cout << 2 + (a[1] ^ x) << endl;
    return 0;
}