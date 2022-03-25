#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

int n, a[maxn], ans = 1;

void dfs(int p, int k, int c){
    if (p == n || k == 1) return;
    if (gcd(k, a[p]) != 1) ans = max(ans, c + 1), dfs(p + 1, gcd(k, a[p]), c + 1);
    dfs(p + 1, k, c);
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    bool flag = 1;
    for (int i = 1; i < n; i++){
        if (a[i] != a[i - 1]){flag = 0; break;}
    }
    if (flag) {puts("-1"); return 0;}
    // sort(a, a + n);
    int s = a[0];
    for (int i = 1; i < n; i++) s = gcd(s, a[i]);
    for (int i = 0; i < n; i++) a[i] /= s;

    for (int i = 0; i < n; i++) dfs(i + 1, a[i], 1);
    printf("%d", n - ans);

    return 0;
}