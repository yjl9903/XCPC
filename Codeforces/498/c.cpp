#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n;
ll d[maxn];
ll s1[maxn], s2[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin >> n; for (int i = 1; i <= n; cin >> d[i++]);
    if (n == 2){
        int res = 0;
        if (d[1] == d[2]) res = d[1];
        cout << res; return 0;
    }
    for (int i = 1; i < n; i++){
        s1[i] = d[i] + s1[i - 1];
    }
    for (int i = n; i > 0; i--){
        s2[i] = d[i] + s2[i + 1];
    }
    ll res = 0, j = n;
    for (int i = 1; i < n - 1; i++){
        for (/* int j = n */; j > i; j--){
            if (s2[j] == s1[i]){
                res = s2[j]; break;
            }
            else if (s2[j] > s1[i]) break;
        }
    }
    cout << res;
    return 0;
}