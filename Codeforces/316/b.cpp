#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m;

int main(){
    cin >> n >> m;
    if (n == 1) return puts("1"), 0;
    if (n - m > m - 1) printf("%d\n", m + 1);
    else printf("%d\n", m - 1);
    return 0;
}