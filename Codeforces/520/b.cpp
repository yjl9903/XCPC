#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    cin >> n; map<int,int> mp;
    if (n == 1) return puts("1 0"), 0;
    for (int i = 2; i * i <= n; i++){
        if (n % i) continue;
        int cnt = 0;
        while (n % i == 0){
            cnt++; n /= i;
        }
        mp[i] = cnt;
    }
    if (n > 1) mp[n] = 1;

    int ans = 1, mx = 0, cnt = 0;
    for (auto& x : mp) {
        ans *= x.first;
        if (mx != x.second) cnt++;
        mx = max(mx, x.second);
    }
    int a = 0, flag = 0;
    for (int i = 0; i <= 30; i++){
        int t = 1 << i;
        if (t > mx) {
            a = i + 1; 
            break;
        }
        if (t == mx){
            a = i + 1;
            if (cnt == 1) a--; 
            break;
        }
    }
    cout << ans << ' ' << a << endl;
    return 0;
}