#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

char s[maxn], z;
int n;

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n >> z >> s;
        int ans = 0;
        for (int i = 0; i < n; i++){
            if (s[i] != z){
                int flag = abs(int(z) - s[i]);
                ans = (n - i) * 2;
                if (flag < 10) ans--;
                break;
            }
        }
        if (ans <= 0) cout << 1 << '\n';
        else cout << ans << '\n';
    }
    return 0;
}