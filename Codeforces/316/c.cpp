#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;

int n, m; char s[maxn];

int main(){
    scanf("%d%d%s", &n, &m, s + 1);
    int l = 1, r = 0, ans = 0;
    for (int i = 1; i <= n + 1; i++){
        if (s[i] == '.'){
            r++;
        } 
        else {
            if (r > l) ans += r - l;
            l = i + 1; r = i;
        }
    }
    // cout << ans << endl;
    while (m--){
        int p; char ch[2]; scanf("%d%s", &p, ch);
        if (s[p] == '.' && ch[0] == '.');
        else if (s[p] != '.' && ch[0] != '.');
        else if (s[p] == '.'){
            s[p] = ch[0];
            if (s[p - 1] != '.' && s[p + 1] != '.');
            else if (s[p - 1] == '.' && s[p + 1] == '.') ans -= 2;
            else ans--;
        }
        else {
            s[p] = ch[0];
            if (s[p - 1] == '.' && s[p + 1] == '.') ans += 2;
            else if (s[p - 1] != '.' && s[p + 1] != '.');
            else ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}