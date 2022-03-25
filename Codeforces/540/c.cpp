#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 10000 + 5;

int n, a[maxn], ans[30][30];
map<int,int> mp, mp2, mp3;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n * n; i++) scanf("%d", a + i), mp[a[i]]++;
    vector<int> v;
    for (auto& x: mp) {
        if (x.second % 4 == 0) continue;
        if (x.second % 4 >= 2) {
            dbg(x.first, x.second);
            mp2[x.first] = 2;
            x.second -= 2;
        }
        if (x.second % 4 == 1) {
            dbg(x.first, x.second);
            v.push_back(x.first);
            x.second--;
        }
    }
    if ((int)v.size() > 1) return puts("NO"), 0;
    if ((int)v.size() == 1) {
        if (n % 2 == 0) return puts("NO"), 0;
        dbg(v.front());
        ans[n / 2 + 1][n / 2 + 1] = v.front();
    }
    if (!mp2.empty()) {
        if (n % 2 == 0) return puts("NO"), 0;
        int x = n / 2 + 1, y = 1, flag = 1;
        int yb = n / 2 + 1;
        dbg((int)mp2.size());
        if ((int)mp2.size() > n / 2 * 2) return puts("NO"), 0;
        for (auto& t: mp2) {
            if (flag) {
                ans[x][y] = ans[x][n + 1 - y] = t.first;
                y++;
                if (y == yb) {
                    flag = 0; x = 1; y = n / 2 + 1;
                }
            } else {
                ans[x][y] = ans[n + 1 - x][y] = t.first;
                x++;
            }
        }
    }
    int x = 1, y = 1, flag = 0;
    for (auto& t: mp) {
        int cnt = t.second;
        if (flag) {
            mp3[t.first] = t.second; continue;
        }
        while (cnt) {
            // dbg(x, y);
            ans[x][y] = ans[n + 1 - x][y] = ans[n + 1 - x][n + 1 - y] = ans[x][n + 1 - y] = t.first;
            y++; if (y == n / 2 + 1) y = 1, x++;
            cnt -= 4;
            if (x == n / 2 + 1) {
                mp3[t.first] = cnt; flag = 1; break;
            }
        }
    }
    if (n % 2 == 1) {
        for (int i = 1; i <= n / 2; i++) if (ans[i][n / 2 + 1] == 0) {
            while (!mp3.empty() && mp3.begin()->second == 0) {
                mp3.erase(mp3.begin());
            }
            ans[i][n / 2 + 1] = ans[n + 1 - i][n / 2 + 1] = mp3.begin()->first;
            mp3.begin()->second -= 2;
        }
        for (int i = 1; i <= n / 2; i++) if (ans[n / 2 + 1][i] == 0) {
            while (!mp3.empty() && mp3.begin()->second == 0) {
                mp3.erase(mp3.begin());
            }
            ans[n / 2 + 1][i] = ans[n / 2 + 1][n + 1 - i] = mp3.begin()->first;
            mp3.begin()->second -= 2;
        }
    }
    puts("YES");
    for (int i = 1; i <= n; i++, puts("")) for (int j = 1; j <= n; j++) printf("%d ", ans[i][j]);
    return 0;
}