#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <set>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n, m, d, ans[maxn];
PII a[maxn];

int main(){
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 0; i < n; i++) scanf("%d", &a[i].first), a[i].second = i;
    sort(a, a + n);
    int day = 1;
    for (int i = 0; i < n; i++){
        if (ans[a[i].second]) continue;
        ans[a[i].second] = day;
        int last = a[i].first;
        for (int j = i + 1; j < n; j++){
            if (ans[a[j].second]) continue;
            if (a[j].first - last > d){
                ans[a[j].second] = day;
                last = a[j].first;
            }
        }
        day++;
    }
    printf("%d\n", day - 1);
    for (int i = 0; i < n; i++) printf("%d ", ans[i]);
    return 0;
}