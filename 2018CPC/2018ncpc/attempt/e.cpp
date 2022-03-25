#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, d, a[10], b[10];

int main(){
    srand(233333);
    scanf("%d%d%d", &n, &m, &d); int s = 0;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), s += a[i];
    for (int i = 1; i <= m; i++) scanf("%d", b + i), s += b[i];
    if (d >= s) return puts("1.000000"), 0;
    int T = 1e7, cnt = 0;
    for (int i = 0; i < T; i++){
        vector<int> x, y;
        for (int i = 1; i <= n; i++) x.push_back(a[i]);
        for (int i = 1; i <= m; i++) y.push_back(b[i]);
        for (int i = 0; i < d; i++){
            int s = x.size() + y.size();
            int k = rand() % s;
            if (k < x.size()){
                x[k]--; 
                if (x[k] == 0) x[k] = x.back(), x.pop_back();
            }
            else {
                k -= x.size();
                y[k]--; 
                if (y[k] == 0) y[k] = y.back(), y.pop_back();
            }
        }
        if (y.size() == 0) cnt++;
    }
    printf("%.6lf\n", double(cnt) / double(T));
    return 0;
}