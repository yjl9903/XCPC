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

int a, b, k;

int main() {
    cin >> a >> b >> k;
    for (int i = min(a, b); i >= 1; i--) {
        if (a % i == 0 && b % i == 0) {
            k--;
            if (k == 0) return cout << i << endl, 0;
        }
    }
    return 0;
}