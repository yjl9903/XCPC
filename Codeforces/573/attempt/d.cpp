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
const int maxn = 400000 + 5;
const int sz = 1000;

int n, bag[maxn], cnt;
PII a[maxn];
vector<int> bel[maxn];

void add(int x) {
    bag[x]++;
    if (bag[x] == 1) cnt++;
}  
void del(int x) {
    bag[x]--;
    if (bag[x] == 0) cnt--;
}

int main() {
    scanf("%d", &n);
    vector<int> lsh, lsh2;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first, &a[i].second);
        lsh.push_back(a[i].first);
        lsh2.push_back(a[i].second);
    }
    sort(lsh.begin(), lsh.end()); lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    sort(lsh2.begin(), lsh2.end()); lsh2.resize(unique(lsh2.begin(), lsh2.end()) - lsh2.begin());
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        a[i].first = lower_bound(lsh.begin(), lsh.end(), a[i].first) - lsh.begin() + 1;
        a[i].second = lower_bound(lsh2.begin(), lsh2.end(), a[i].second) - lsh2.begin() + 1;
        bel[a[i].first].push_back(a[i].second);
        mx = max(mx, a[i].first);
        // add(a[i].second);
    }
    return 0;
}