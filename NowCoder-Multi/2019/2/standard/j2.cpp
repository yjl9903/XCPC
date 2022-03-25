#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <assert.h>
using namespace std;
 
const int maxn = 1e6 + 7;
 
long long L[maxn], R[maxn];
long long S[maxn];
long long tol[maxn], tor[maxn];
 
const int maxm = 3e7 + 7;
int o[maxm];
char sig[maxm];
 
const int maxr = 2e7 + 7;
const int offset = 1e7 + 3;
int r[maxr];
void update(int x, int v) {
    x += offset;
    while (x < maxr) {
        r[x] += v;
        x = x + (x & -x);
    }
}
 
int query(int x) {
    int rt = 0;
    x += offset;
    while (x) {
        rt += r[x];
        x -= x & -x;
    }
    return rt;
}
 
int main() {
    int n;
    int cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &L[i], &R[i]);
        cnt += R[i] - L[i] + 1;
    }
    S[1] = R[1] - L[1] + 1;
    for (int i = 2; i <= n; i++)
        S[i] = S[i - 1] + (R[i] - L[i] + 1) - (L[i] - R[i - 1] - 1);
 
    long long mn = 0;
    for (int i = 1; i <= n; i++) {
        mn = min(mn, S[i] - (R[i] - L[i] + 1));
        tor[i] = S[i] - mn;
        if (i != n) tor[i] = min(tor[i], L[i + 1] - R[i] - 1);
    }
 
    S[n] = R[n] - L[n] + 1;
    for (int i = n - 1; i >= 1; i--)
        S[i] = S[i + 1] + (R[i] - L[i] + 1) - (L[i + 1] - R[i] - 1);
 
    mn = 0;
    for (int i = n; i >= 1; i--) {
        mn = min(mn, S[i] - (R[i] - L[i] + 1));
        tol[i] = S[i] - mn;
        if (i != 1) tol[i] = min(tol[i], L[i] - R[i - 1] - 1);
    }
 
    int tail = 0;
    o[tail] = -1000000000;
 
    int last = o[tail];
    for (int i = 1; i <= n; i++) {
        for (int j = max((long long)last + 1, L[i] - tol[i]); j <= R[i] + tor[i]; j++)
            if (j > o[tail] && j >= 0 && j < 1000000000) {
                o[++tail] = j;
                //if (tail % 100 == 0) cout << tail << ' ' << j << endl;
                if (j >= L[i] && j <= R[i]) sig[tail] = 1;
                else sig[tail] = -1;
            }
        last = o[tail];
    }
    assert(tail <= 3 * cnt);
 
    long long ans = 0; 
    for (int x = 1; x <= tail; x++) {
        int y = x + 1;
        while (y <= tail && o[y] == o[y - 1] + 1) y++;
        y--;
 
        int cur = 0 + offset;
        int T = 0;
 
        r[cur]++;
        for (int i = x; i <= y; i++) {
            if (sig[i] == 1) {
                T += r[cur];
                cur++;
            }
            else {
                T -= r[cur - 1];
                cur--;
            }
            r[cur]++;
 
            ans += T;
        }
 
        cur = 0 + offset;
        r[cur]--;
        for (int i = x; i <= y; i++) {
            if (sig[i] == 1) {
                cur++;
            }
            else {
                cur--;
            }
            r[cur]--;
        }
 
        x = y;
    }
    cout << ans << endl;
    return 0;
}