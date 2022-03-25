#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ext/rope>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;
const int maxn = 1000 + 5;

rope<int> r;
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) r.push_back(i);
    while (m--){
        int x, y; scanf("%d%d", &x, &y);
        r = r.substr(x - 1, y) + r.substr(0, x - 1) + r.substr(x + y - 1, n - x - y + 1);
    }
    for (int i = 0; i < n - 1; i++) printf("%d ", r[i]);
    printf("%d", r[n - 1]);
    return 0;
}