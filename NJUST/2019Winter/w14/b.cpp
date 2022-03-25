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

int n;

int main() {
    cin >> n;
    if (n <= 5) puts("-1");
    else {
        puts("1 2");
        puts("2 3");
        puts("2 4");
        for (int i = 5; i <= n; i++) printf("1 %d\n", i);
    }
    for (int i = 2; i <= n; i++) printf("1 %d\n", i);
    return 0;
}