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
    cin >> n >> s; int cnt = 0, ans = 0;
    for (int i = 0; i < n; i++) if (s[i] == '8') cnt++;
    if (cnt * 11 > n) printf("%d", n / 11);
    else printf("%d", cnt);
    return 0;
}