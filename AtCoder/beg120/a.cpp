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

int a, b, c;

int main() {
    cin >> a >> b >> c;
    if (a * c <= b) cout << c << endl;
    else cout << b / a << endl;
    return 0;
}