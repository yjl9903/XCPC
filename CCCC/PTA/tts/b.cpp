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
const int maxn = 10000 + 5;

struct node {
    int x, y1, y2;
    bool operator< (const node& b) const {
        return x < b.x;
    }
} a[maxn];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i].x, &a[i].y1, &a[i].y2);
        if (a[i].y1 > a[i].y2) swap(a[i].y1, a[i].y2);
    }
    sort(a + 1, a + 1 + n);
    for (int l = a[1].y1; l <= a[1].y2; l++) {
        for (int r = a[n].y1; r <= a[n].y2; r++) {
            
        }
    }
    return 0;
}