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

int x;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        cin >> x;
        cout << x / 2 << endl;
    }
    return 0;
}