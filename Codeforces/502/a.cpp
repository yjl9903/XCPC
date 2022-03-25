#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int n;
PII a[maxn];
bool cmp(PII a, PII b){
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        int x, b, c, d; scanf("%d%d%d%d", &x, &b, &c, &d);
        a[i] = make_pair(x + b + c + d, i);
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++) if (a[i].second == 1){
        printf("%d", i); return 0;
    }
    return 0;
}