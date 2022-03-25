#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n, k, s[maxn], cnt[maxn];
vector<PII> v;

int check(int m){
    int r = 0;
    for (int i = 0; i < maxn; i++) r += cnt[i] / m;
    return r >= k;
}

int main(){
    scanf("%d%d", &n, &k); for (int i = 1; i <= n; i++) scanf("%d", s + i), cnt[s[i]]++;
    int l = 1, r = 2e5, ans = 0;
    while (l <= r){
        int m = l + r >> 1;
        if (check(m)) ans = m, l = m + 1;
        else r = m - 1;
    }
    vector<int> v;
    for (int i = 1; i < maxn; i++){
        if (cnt[i] < ans) continue;
        while (cnt[i] >= ans){
            v.push_back(i); cnt[i] -= ans;
        }
    }
    for (int i = 0; i < min(k, (int)v.size()); i++) printf("%d ", v[i]);
    return 0;
}