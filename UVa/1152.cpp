#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

vector<int> v[4], x, y;
int n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        v[0].clear(); v[1].clear(); v[2].clear(); v[3].clear();
        scanf("%d", &n);
        for (int i = 0; i < n; i++){
            int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
            v[0].push_back(a); v[1].push_back(b);
            v[2].push_back(c); v[3].push_back(d);
        }
        y.clear(); 
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) y.push_back(-v[2][i] - v[3][j]);
        sort(y.begin(), y.end());
        int sum = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            int t = v[0][i] + v[1][j];
            int k = lower_bound(y.begin(), y.end(), t) - y.begin();
            int p = upper_bound(y.begin(), y.end(), t) - y.begin();
            sum += p - k;
        }
        printf("%d\n", sum);
        if (T) printf("\n");
    }
    return 0;
}