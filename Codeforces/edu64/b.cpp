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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

char s[maxn];
int cnt[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        ms(cnt, 0);
        int n = strlen(s);
        for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
        string ans;
        for (int i = 0; i < 26; i += 2) {
            int x = cnt[i];
            while (x--) ans += i + 'a';
        }
        for (int i = 1; i < 26; i += 2) {
            int x = cnt[i];
            while (x--) ans += i + 'a';
        }
        int flag = 0;
        for (int i = 1; i < n; i++) if (abs(ans[i] - ans[i - 1]) == 1) {
            flag = 1; break;
        }
        if (flag) {
            ans = "";
            for (int i = 1; i < 26; i += 2) {
                int x = cnt[i];
                while (x--) ans += i + 'a';
            }
            for (int i = 0; i < 26; i += 2) {
                int x = cnt[i];
                while (x--) ans += i + 'a';
            }
            int flag = 0;
            for (int i = 1; i < n; i++) if (abs(ans[i] - ans[i - 1]) == 1) {
                flag = 1; break;
            }
            if (flag) puts("No answer");
            else puts(ans.c_str());
        } else puts(ans.c_str());
    }
    return 0;
}