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
const int mod = 998244353;
const int maxn = 100000 + 5;

int n; PII a[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d",&a[i].first, &a[i].second);
    sort(a, a + n, [](PII a, PII b) { return a.second != b.second ? a.second < b.second : a.first < b.first; });
    int i = 0, ans = 0;
    while (i < n) {
        ans++;
        int j = i;
        while (j < n && a[j].first < a[i].second) {
            j++;
        }
        i = j;
    }
    cout << ans << endl;
    return 0;
}