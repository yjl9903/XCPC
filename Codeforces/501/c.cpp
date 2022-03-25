#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n, m;
PII s[maxn];

bool cmp(PII a, PII b){
    if (a.first - a.second != b.first - b.second) return a.first - a.second > b.first - b.second;
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d%d", &s[i].first, &s[i].second);
    sort(s, s + n, cmp);
    ll sum = 0;
    for (int i = 0; i < n; i++) sum += 1ll * s[i].first;
    if (sum <= 1ll * m){
        puts("0"); return 0;
    }
    for (int i = 0; i < n; i++){
        sum -= 1ll * (s[i].first - s[i].second);
        if (sum <= 1ll * m) {
            printf("%d\n", i + 1);
            return 0;
        }
    }
    puts("-1");
    return 0;
}