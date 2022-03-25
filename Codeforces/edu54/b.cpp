#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

const int maxp = 1000000 + 5;
int vis[maxp], prime[maxp], tot;
void init(){
    ms(vis, 0);
    for (int i = 2; i < maxp; i++){
        if (!vis[i]) prime[tot++] = i;
        for (int j = 0; j < tot && prime[j] * i < maxp; j++){
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

ll n, ans = 0;

int main(){
    cin >> n; init();
    if (n % 2 == 0) return cout << n / 2 << endl, 0;
    for (int i = 1; i < tot; i++){
        if (n % prime[i] == 0){
            cout << 1 + (n - prime[i]) / 2 << endl; return 0;
        }
    }
    cout << 1 << endl;
    return 0;
}