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

int main() {
    cin >> n;
    vector<int> v1, v2;
    for (int i = 1; i <= n; i = n / (n / i) + 1) v1.push_back(n / i);
    v2.push_back(n);
    for (int i = 2; i <= n; i++) {
        if (n / i != n / (i - 1)) v2.push_back(n / i);
    }
    cout << (int)v1.size() << endl;
    cout << (int)v2.size() << endl;
    if (v1 == v2) puts("OK");
    else puts("???");
    return 0;
}