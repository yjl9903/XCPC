#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
const int maxn = 100000 + 5;

int n, T, s[maxn], t[maxn];

int main() {
    scanf("%d%d", &n, &T);
    int mn = 1e9, p;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", s + i, t + i);
    }
    mn = 1e9;
    for (int i = 1; i <= n; i++) {
        if (s[i] > T) {
            if (s[i] < mn) mn = s[i], p = i;
            continue;
        }
        int x = (T - s[i]) / t[i];
        if ((T - s[i]) % t[i]) x++;
        int tot = x * t[i] + s[i];
        if (tot < mn) mn = tot, p = i;
    }
    cout << p;
    return 0;
}