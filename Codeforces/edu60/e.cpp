#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 10000 + 5;

char t[maxn];
int n, f[maxn], g[maxn];

int main() {
    scanf("%s", t); n = strlen(t);
    string s, q;
    for (int i = 0; i < n; i++) s += i % 26 + 'a';
    cout << "? " << s << endl;
    cin >> q;
    for (int i = 0; i < n; i++) {
        // f[(q[i] - 'a') % 26] = i;
        f[i] = (q[i] - 'a');
    }
    
    s.clear();
    for (int i = 0; i < n; i++) s += i / 26 % 26 + 'a';
    cout << "? " << s << endl;
    cin >> q;
    for (int i = 0; i < n; i++) {
        f[i] += 26 * (q[i] - 'a');
    }

    s.clear();
    for (int i = 0; i < n; i++) s += i / 26 / 26 % 26 + 'a';
    cout << "? " << s << endl;
    cin >> q;
    for (int i = 0; i < n; i++) {
        f[i] += 676 * (q[i] - 'a');
    }
    for (int i = 0; i < n; i++) g[f[i]] = i;
    printf("! ");
    for (int i = 0; i < n; i++) printf("%c", t[g[i]]);
    return 0;
}