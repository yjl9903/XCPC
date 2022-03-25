#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, x, y, dx[maxn], dy[maxn]; char s[maxn];

int check(int l){
    for (int i = 1; i + l - 1 <= n; i++){
        int ax = dx[i - 1] + dx[n] - dx[i + l - 1];
        int ay = dy[i - 1] + dy[n] - dy[i + l - 1];
        int t = l - abs(x - ax) - abs(y - ay);
        if (t >= 0 && t % 2 == 0) return 1;
    }
    return 0;
}

int main(){
    scanf("%d%s%d%d", &n, s + 1, &x, &y);
    if (n < x + y || (n - x - y) % 2) return puts("-1"), 0;
    
    for (int i = 1; i <= n; i++){
        if (s[i] == 'R') dx[i]++;
        if (s[i] == 'L') dx[i]--;
        if (s[i] == 'U') dy[i]++;
        if (s[i] == 'D') dy[i]--;
        dx[i] += dx[i - 1]; dy[i] += dy[i - 1];        
    }
    if (dx[n] == x && dy[n] == y) return puts("0"), 0;

    int l = 1, r = n, ans = -1;
    while (l <= r){
        int m = l + r >> 1;
        if (check(m)) r = m - 1, ans = m;
        else l = m + 1;
    }
    printf("%d\n", ans);
    return 0;
}