#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 4294967295;
const int maxn = 100000 + 5;

int n;
ll x;
char s[20];

int main() {
    scanf("%d", &n);
    ll tot = 1;
    vector<ll> v; v.push_back(1);
    for (int i = 1, a; i <= n; i++) {
        scanf("%s", s);
        if (s[0] == 'f') {
            scanf("%d", &a);
            if (v.back() == -1) v.push_back(-1);
            else if (1ll * v.back() * a > inf) v.push_back(-1);
            else v.push_back(1ll * v.back() * a);
            tot *= 1ll * a;
        } else if (s[0] == 'a') {
            if (v.back() == -1) return puts("OVERFLOW!!!"), 0;
            x += v.back();
            if (x > inf) return puts("OVERFLOW!!!"), 0;
        } else if (s[0] == 'e') {
            v.pop_back();
        }
    }
    cout << x << endl;
    return 0;
}