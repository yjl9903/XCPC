#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000 + 5;

int n;
pair<PII, int> p[3 * maxn];   

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 0; i < 3 * n; i++) scanf("%d%d", &p[i].first.first, &p[i].first.second), p[i].second = i + 1;
        sort(p, p + 3 * n);
        for (int i = 0; i < 3 * n; i += 3) printf("%d %d %d\n", p[i].second, p[i + 1].second, p[i + 2].second);
    }
    return 0;
}