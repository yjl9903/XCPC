#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, k, cnt[40];

void out() {
    puts("YES");
    for (int i = 0, j = 1; i < 31; i++, j += j) {
        while (cnt[i]--) printf("%d ", j);
    }
}

int main(){
    cin >> n >> k;
    if (n < k) return puts("NO"), 0;
    if (n == 1) return puts("YES\n1"), 0;
    int sum = 0, last = 0;
    for (int i = 0, j = 1; i < 31; i++, j += j) {
        if (j & n) cnt[i]++, sum++, last = i;
    }
    if (k < sum) return puts("NO"), 0;
    for (int i = last; i > 0; i--) {
        if (sum == k) return out(), 0;
        if (sum + cnt[i] >= k) {
            cnt[i] -= k - sum;
            cnt[i - 1] += 2 * (k - sum);
            out(); return 0;
        }
        sum += cnt[i];
        cnt[i - 1] += 2 * cnt[i];
        cnt[i] = 0;
    }
    puts("NO");
    return 0;
}