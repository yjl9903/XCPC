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

int h1, m1, h2, m2;

int main() {
    scanf("%d:%d", &h1, &m1);
    scanf("%d:%d", &h2, &m2);
    int s1 = h1 * 60 + m1;
    int s2 = h2 * 60 + m2;
    int m = s1 + (s2 - s1) / 2;
    // cout << m / 60 << ':' << m % 60 << endl;
    printf("%02d:%02d\n", m / 60, m % 60);
    return 0;
}