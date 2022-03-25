#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <string>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

string hand[20];
map<string,int> mp;

int cnt[5][15];

int dfs(int n) {
    // dbg(n);
    if (n == 0) return 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 9; j++) {
            if (cnt[i][j] >= 3) {
                cnt[i][j] -= 3;
                if (dfs(n - 1)) return 1;
                cnt[i][j] += 3;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= 7; j++) {
            if (cnt[i][j] && cnt[i][j + 1] && cnt[i][j + 2]) {
                // dbg(i, j, cnt[i][j], cnt[i][j + 1], cnt[i][j + 2]);
                cnt[i][j]--; cnt[i][j + 1]--; cnt[i][j + 2]--;
                if (dfs(n - 1)) return 1;
                cnt[i][j]++; cnt[i][j + 1]++; cnt[i][j + 2]++;
            }
        }
    }
    return 0;
}

int get(char c) {
    if (c == 'w') return 0;
    if (c == 's') return 1;
    if (c == 'p') return 2;
    if (c == 'z') return 3;
}
int check() {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 11; j++) cnt[i][j] = 0;
    for (auto& x: mp) {
        cnt[get(x.first[1])][x.first[0] - '0'] += x.second;
    }
    // for (int i = 0; i <= 4; i++) {
    //     for (int j = 1; j <= 9; j++) {
    //         if (i == 3 && j == 8) break;
    //         cout << cnt[i][j] << ' ';
    //     }
    //     puts("");
    // }
    for (auto& x: mp) {
        if (x.second >= 2) {
            cnt[get(x.first[1])][x.first[0] - '0'] -= 2;
            if (dfs(4)) return 1;
            cnt[get(x.first[1])][x.first[0] - '0'] += 2;
        }
    }
    return 0;
}

int main() {
    while (cin >> hand[0]) {
        mp.clear();
        for (int i = 1; i < 13; i++) cin >> hand[i];
        for (int i = 0; i < 13; i++) mp[hand[i]]++;
        for (int i = 1; i <= 9; i++) {
            string x; x += char(i + '0'); x+= "w";
            if (mp[x] == 4) continue;
            mp[x]++; 
            if (check()) cout << x << '\n';
            mp[x]--;
        }
        for (int i = 1; i <= 9; i++) {
            string x; x += char(i + '0'); x+= "s";
            if (mp[x] == 4) continue;
            mp[x]++; 
            if (check()) cout << x << '\n';
            mp[x]--;
        }
        for (int i = 1; i <= 9; i++) {
            string x; x += char(i + '0'); x+= "p";
            if (mp[x] == 4) continue;
            mp[x]++; 
            if (check()) cout << x << '\n';
            mp[x]--;
        }
        for (int i = 1; i <= 7; i++) {
            string x; x += char(i + '0'); x+= "z";
            if (mp[x] == 4) continue;
            mp[x]++; 
            if (check()) cout << x << '\n';
            mp[x]--;
        }
    }
    return 0;
}