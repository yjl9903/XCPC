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

ll a, b, c;

int main() {
    cin >> a >> b >> c;
    if (a + b < c) c = a + b + 1;
    cout << b + c << endl;
    return 0;
}