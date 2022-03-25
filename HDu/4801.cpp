#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int a[maxn], n, res;

int cal(int x[]){
    int sum = 6;
    if (a[0] != a[1] || a[1] != a[2] || a[2] != a[3]) sum--;
    if (a[16] != a[17] || a[17] != a[18] || a[18] != a[19]) sum--;
    if (a[20] != a[21] || a[21] != a[22] || a[22] != a[23]) sum--;
    if (a[4] != a[5] || a[5] != a[10] || a[10] != a[11]) sum--;
    if (a[6] != a[7] || a[7] != a[12] || a[12] != a[13]) sum--;
    if (a[8] != a[9] || a[9] != a[14] || a[14] != a[15]) sum--;
    return sum;
}

int dfs(int d, int t){
    int tmp[maxn]; memcpy(tmp, a, sizeof a);
    res = max(res, cal(tmp));
    // cout << cal(tmp) << endl;
    // for (int i = 0; i < 24; cout << tmp[i++] << ' '); cout << endl;
    if (res == 6) return 1;
    if (d == n) return 0;

    a[12] = tmp[10], a[13] = tmp[11], a[14] = tmp[12], a[15] = tmp[13], a[21] = tmp[14], a[20] = tmp[15], a[10] = tmp[21], a[11] = tmp[20];
    a[16] = tmp[18], a[17] = tmp[16], a[19] = tmp[17], a[18] = tmp[19];
    if (t != 2) dfs(d + 1, 1);
    memcpy(a, tmp, sizeof a);
    a[10] = tmp[12], a[11] = tmp[13], a[12] = tmp[14], a[13] = tmp[15], a[14] = tmp[21], a[15] = tmp[20], a[21] = tmp[10], a[20] = tmp[11];
    a[16] = tmp[17], a[17] = tmp[19], a[19] = tmp[18], a[18] = tmp[16];
    if (t != 1) dfs(d + 1, 2); 
    memcpy(a, tmp, sizeof a); 
    a[6] = tmp[0], a[12] = tmp[2], a[16] = tmp[6], a[18] = tmp[12], a[20] = tmp[16], a[22] = tmp[18], a[0] = tmp[20], a[2] = tmp[22];
    a[5] = tmp[4], a[11] = tmp[5], a[10] = tmp[11], a[4] = tmp[10];
    if (t != 4) dfs(d + 1, 3);
    memcpy(a, tmp, sizeof a);
    a[0] = tmp[6], a[2] = tmp[12], a[6] = tmp[16], a[12] = tmp[18], a[16] = tmp[20], a[18] = tmp[22], a[20] = tmp[0], a[22] = tmp[2];
    a[4] = tmp[5], a[5] = tmp[11], a[11] = tmp[10], a[10] = tmp[4];
    if (t != 3) dfs(d + 1, 4);
    memcpy(a, tmp, sizeof a);
    a[6] = tmp[7], a[7] = tmp[13], a[13] = tmp[12], a[12] = tmp[6];
    a[2] = tmp[8], a[3] = tmp[14], a[8] = tmp[17], a[14] = tmp[16], a[17] = tmp[11], a[16] = tmp[5], a[11] = tmp[2], a[5] = tmp[3];
    if (t != 6) dfs(d + 1, 5);
    memcpy(a, tmp, sizeof a);
    a[7] = tmp[6], a[13] = tmp[7], a[12] = tmp[13], a[6] = tmp[12];
    a[2] = tmp[11], a[3] = tmp[5], a[8] = tmp[2], a[14] = tmp[3], a[17] = tmp[8], a[16] = tmp[14], a[5] = tmp[16], a[11] = tmp[17];
    if (t != 5) dfs(d + 1, 6);
    return 0;
}

int main(){
    while (cin >> n){
        for (int i = 0; i < 24; cin >> a[i++]);
        // cout << cal(a) << endl;
        res = 0;
        dfs(0, -1);
        cout << res << endl;
    }
    return 0;
}