#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int ch[maxn * 30][2], val[maxn * 30], tot;
void insert(char* s) {
    int now = 0;
    for (int i = 0; s[i]; i++) {
        if (ch[now][s[i] - '0']) now = ch[now][s[i] - '0'];
        else now = ch[now][s[i] - '0'] = ++tot;
    }
    val[now]++;
}
void insert(int x) {
    char tmp[35];
    for (int i = 30; i >= 0; i--) {
        tmp[30 - i] = ((x >> i) & 1) + '0';
    }
    tmp[31] = 0;
    // cout << tmp << endl;
    insert(tmp);
}
int get(char* s) {
    int x = 0;
    for (int i = 0; i <= 30; i++) {
        if (s[i] == '1') x += (1 << (30 - i));
    }
    // cout << x << endl;
    return x;
}
int query(int x) {
    char tmp[35];
    for (int i = 30; i >= 0; i--) {
        tmp[30 - i] = ((x >> i) & 1) + '0';
    }
    tmp[31] = 0;
    int now = 0, ans = 0;
    for (int i = 0; tmp[i]; i++) {
        if (tmp[i] == '1') {
            if (ch[now][0]) now = ch[now][0];
            else if (ch[now][1]) tmp[i] = '0', now = ch[now][1];
            else return ans; 
        } else {
            if (ch[now][1]) tmp[i] = '1', now = ch[now][1];
            else if (ch[now][0]) now = ch[now][0];
            else return ans;
        }
        if (val[now]) ans = max(ans, get(tmp));
    }
    return ans;
}

int n, a[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        insert(a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, query(a[i]));
    }
    cout << ans << endl;
    return 0;
}