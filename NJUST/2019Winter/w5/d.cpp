#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 500000 + 5;

int n, cnt[200];
char s[maxn], ans[maxn];
vector<int> v;

int main(){
    scanf("%d%s", &n, s);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    int ji = 0;
    for (int i = '0'; i <= 'z'; i++) if (cnt[i] % 2) ji++, cnt[i]--, v.push_back(i);
    if (ji == 0) {
        puts("1");
        int c = 0;
        for (int i = '0'; i <= 'z'; i++) if (cnt[i]) {
            int k = cnt[i] / 2;
            while (k--) ans[c++] = i;
        }
        for (int i = 'z'; i >= '0'; i--) if (cnt[i]) {
            int k = cnt[i] / 2;
            while (k--) ans[c++] = i;
        }
        cout << ans << endl;
    } else {
        for (int k = ji; k <= n; k += 2) {
            if ((n - k) % (2 * k)) continue;
            printf("%d\n", k);
            for (int i = '0'; i <= 'z'; i++) if (cnt[i]) {
                while ((int)v.size() < k && cnt[i] >= 2) {
                    v.push_back(i);
                    v.push_back(i);
                    cnt[i] -= 2;
                }
            }   
            int l = (n - k) / 2 / k;
            for (int& ch: v) {
                int c = 0;
                for (int i = '0'; i <= 'z'; i++) if (cnt[i]) {
                    while (cnt[i] >= 2 && c < l) {
                        ans[c++] = i; cnt[i] -= 2;
                    }
                }
                printf("%s%c", ans, ch);
                for (int i = l - 1; i >= 0; i--) putchar(ans[i]);
                putchar(' ');
            }
            break;
        }
    }
    return 0;
}