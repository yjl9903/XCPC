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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n; char s[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int ans = 0, n = strlen(s), a = 0, b = 0, c = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'A') a++;
            else if (s[i] == 'B') b++;
            else c++;
            if (a == 10 && b == 10) {
                if (c >= 2) {
                    ans++; a = b = c = 0;
                } else if (c == 1) {
                    if (i == n - 1) break;
                    i++; ans++; a = b = c = 0;
                } else {
                    int j = i + 1;
                    while (j < n) {
                        if (s[j] == 'A') a++;
                        else if (s[j] == 'B') b++;
                        else c++;
                        if (a + c - b == 2 || b + c - a == 2) {
                            ans++; a = b = c = 0; break;
                        }
                        j++;
                    }
                    i = j;
                }
            } else if (a + c == 11 || b + c == 11) {
                ans++; a = b = c = 0;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}