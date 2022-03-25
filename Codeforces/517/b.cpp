#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn], b[maxn], t[maxn];

int dfs(int i){
    if (i == n) return 1;
    for (int k = 0; k < 4; k++){
        if ((k | t[i - 1]) == a[i - 1] && (k & t[i - 1]) == b[i - 1]){
            t[i] = k;
            if (dfs(i + 1)) return 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i + 1 < n; i++) scanf("%d", a + i);
    for (int i = 0; i + 1 < n; i++) scanf("%d", b + i);

    for (int s = 0; s < 4; s++){
        t[0] = s;
        if (dfs(1)){
            puts("YES");
            for (int i = 0; i < n; i++) printf("%d ", t[i]);
            return 0;
        }
    }
    
    puts("NO");
    return 0;
}