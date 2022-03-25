#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200 + 5;

int n, m, vis[maxn];
mt19937 rnd(time(NULL));

int main() {
    cin >> n >> m;
    int T = 100000, ok = 0;
    for (int t = 0; t < T; t++) {
        ms(vis, 0);
        int x = 0, cnt = 0, flag = 0; 
        while (true) {
            if (vis[x] == 0) cnt++;
            vis[x] = 1;
            if (x == m) {
                if (cnt == n) flag = 1;
                break;
            }
            if (rnd() % 2) x = (x + 1) % n;
            else x = (x + n - 1) % n;
        }
        if (flag) ok++;
    }
    cout << double(ok) / double(T);
    return 0;
}