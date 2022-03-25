#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n;

int main() {
    scanf("%d", &n);
    map<int,int> mp;
    int id, h, m; char op[5];
    int cnt = 0, ans = 0;
    while (n) {
        scanf("%d %s %d:%d", &id, op, &h, &m);
        if (id == 0) {
            if (cnt == 0) puts("0 0");
            else printf("%d %d\n", cnt, int((double)ans / (double)cnt + 0.5));
            cnt = 0; ans = 0;
            mp.clear();
            n--;
        } else {
            if (op[0] == 'S') {
                mp[id] = h * 60 + m;
            } else {
                if (mp.count(id)) {
                    cnt++; 
                    ans += h * 60 + m - mp[id];
                    mp.erase(id);
                }
            }
        }
    }
    return 0;
}