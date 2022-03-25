#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, x, y, tx, ty; char s[maxn], n1, n2;

/*
8
DRDUDDLL
6 0
*/

int cal(int cnt1, int cnt2){
    // cout << cnt1 << ' ' << cnt2 << endl;
    // int cnt1 = abs(tx - x) / 2, cnt2 = abs(ty - y) / 2;
    int s1 = 0, s2 = 0, l = 0, r = 0, ans = 1 << 30;
    for (int i = 0; i < n; i++){
        if (s[i] == n1) s1++;
        if (s[i] == n2) s2++;
        // cout << s1 << ' ' << s2 << endl;
        while (s1 >= cnt1 && s2 >= cnt2){
            if (s[l] == n1) s1--;
            if (s[l] == n2) s2--;
            if (s1 < cnt1){
                s1++; break;
            }
            else if (s2 < cnt2){
                s2++; break;
            }
            l++;
        }
        if (s1 >= cnt1 && s2 >= cnt2) ans = min(ans, i - l + 1);
    }
    return ans;
}

int main(){
    scanf("%d%s%d%d", &n, s, &x, &y);
    if (n < x + y || (n - x - y) % 2) return puts("-1"), 0;
    
    int cnt[4] = {0, 0, 0, 0};
    for (int i = 0; i < n; i++){
        if (s[i] == 'R') tx++, cnt[0]++;
        if (s[i] == 'L') tx--, cnt[1]++;
        if (s[i] == 'U') ty++, cnt[2]++;
        if (s[i] == 'D') ty--, cnt[3]++;
    }
    if (tx == x && ty == y) return puts("0"), 0;

    if (tx > x) n1 = 'R';
    else n1 = 'L';
    if (ty > y) n2 = 'U';
    else n2 = 'D';

    int ans = 1 << 30;
    if (abs(tx - x) % 2 || abs(ty - y) % 2) {
        int a1 = cal(abs(tx - x) / 2 + 1, abs(ty - y) / 2);
        int a2 = cal(abs(tx - x) / 2, abs(ty - y) / 2 + 1);
        ans = min(a1, a2);
    }
    else ans = cal(abs(tx - x) / 2, abs(ty - y) / 2);

    printf("%d", ans);
    return 0;
}