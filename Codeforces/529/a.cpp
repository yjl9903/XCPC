#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n; char s[maxn];

int main(){
    cin >> n >> s + 1;
    for (int i = 1, j = 1; i <= n; i += j, j++) {
        putchar(s[i]);
    }
    return 0;
}