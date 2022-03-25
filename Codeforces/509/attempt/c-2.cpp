#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n, m, d, ans[maxn], b[maxn];
PII a[maxn];

int main(){
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 0; i < n; i++) scanf("%d", &a[i].first), a[i].second = i;
    sort(a, a + n);
    int day = 0;
    // for (int i = 0; i < n;){
    //     ans[a[i].second] = 1;
    //     b[1] = a[i].first;
    //     int t = a[i++].first, tot = 2;
    //     while (a[i].first - t <= d && i < n){
    //         // ans[a[i].second] = ++tot;
    //         // int k = tot;
    //         tot = 2;
    //         while (a[i].first - b[tot] <= d && b[tot] != 0) tot++;
    //         ans[a[i].second] = tot; 
    //         b[tot] = a[i].first;
    //         i++; 
    //         day = max(day, tot);
    //     }
    // }
    for (int i = 0; i < n; i++){
        int tot = 0;
        while (b[tot] && a[i].first - d <= b[tot]) tot++;
        b[tot] = a[i].first;
        ans[a[i].second] = tot;
        day = max(day, tot);
    }
    printf("%d\n", day);
    for (int i = 0; i < n; i++) printf("%d ", ans[i]);
    return 0;
}