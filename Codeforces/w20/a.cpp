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

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
int n;

int main() {
    cin >> n;
    for (int i = n / 2; i >= 1; i--) {
        int a = i, b = n - i;
        if (gcd(a, b) == 1) {
            cout << a << ' ' << b << endl; return 0;
        }
    }
    return 0;
}