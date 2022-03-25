#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

int isPrime[maxn], vis[maxn], a[maxn], n;

void sieve(){
    int prime[maxn], cnt = 0;
    fill(isPrime, isPrime + maxn, 1);
    isPrime[0] = isPrime[1] = 1;
    for (int i = 2; i < maxn; i++){
        if (isPrime[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && i * prime[j] < maxn; j++){
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)    break;
        }
    }
}

void dfs(int d){
    if (d >= n){
        if (isPrime[a[0] + a[n - 1]]){
            for (int i = 0; i < n; i++){
                if (i) cout << ' ';
                cout << a[i];
            }
            cout << endl;
        }
    }
    else{
        for (int i = 1; i <= n; i++){
            if (!vis[i] && isPrime[a[d - 1] + i]){
                a[d] = i;   vis[i] = 1;
                dfs(d + 1);
                vis[i] = 0;
            }
        }
    }
}

int main(){
    sieve();
    int kase = 0;
    while (cin >> n){
        if (kase)   cout << endl;
        memset(vis, 0, sizeof vis);
        a[0] = 1;   vis[1] = 1;
        cout << "Case " << ++kase << ":\n";
        dfs(1);
    }
    return 0;
}