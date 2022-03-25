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
typedef pair<double,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
PII a[maxn];
double l, v, pos[maxn];
char op[maxn];
char name[maxn][260];

int main() {
    while (scanf("%d", &n) == 1 && n) {
        scanf("%lf%lf", &l, &v);
        double mx = 0; int id = 0;
        for (int i = 1; i <= n; i++) {
            char s[3];
            scanf("%s%lf%s", s, pos + i, name + i);
            op[i] = s[0];
            if (op[i] == 'p' || op[i] == 'P') {
                if (l - pos[i] > mx) {
                    mx = l - pos[i];
                    id = i;
                }
            } else {
                if (pos[i] > mx) {
                    mx = pos[i];
                    id = i;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (op[i] == 'p' || op[i] == 'P') pos[i] += mx;
            else pos[i] -= mx;
            a[i] = make_pair(pos[i], i);
        }
        mx /= v;
        printf("%13.2f ", int(mx * 100.0) / 100.0);
        sort(a + 1, a + 1 + n);
        for (int i = 1; i <= n; i++) {
            if (a[i].first == 0 || a[i].first == l) {
                printf("%s\n", name[i]);
                break;
            }
        }
    }
    return 0;
}