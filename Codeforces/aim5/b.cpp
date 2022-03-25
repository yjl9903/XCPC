#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, a, b;

int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) putchar('1');
    puts("");
    for (int i = 1; i < n; i++) putchar('8');
    putchar('9');
    return 0;
}