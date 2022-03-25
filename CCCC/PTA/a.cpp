#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

struct node {
    char s[10];
    int x;
    double y;
    bool operator<(const node& b) const {
        if (x != b.x) return x > b.x;
        return y < b.y;
    }
} a[maxn];

int n;
char s[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", a[i].s);
        set<int> st;
        int k; scanf("%d", &k);
        for (int j = 0, x; j < k; j++) {
            scanf("%d", &x); st.insert(x);
        }
        a[i].x = (int)st.size();
        a[i].y = (double)k / (double)a[i].x;
    }
    sort(a, a + n);

    // for (int i = 0; i < n; i++) {
    //     cout << a[i].s << ' ' << a[i].x << ' ' << a[i].y << endl;
    // }

    if (n >= 1) printf("%s", a[0].s);
    else printf("-");
    if (n >= 2) printf(" %s", a[1].s);
    else printf(" -");
    if (n >= 3) printf(" %s", a[2].s);
    else printf(" -");
    return 0;
}