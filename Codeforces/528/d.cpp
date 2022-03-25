#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, s, deg[maxn];
vector<int> edge[maxn];

int main(){
    scanf("%d%d", &n, &s);
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), deg[u]++, deg[v]++;
    int c = 0; for (int i = 1; i <= n; i++) if (deg[i] == 1) c++;
    printf("%.8lf\n", 2.0 * double(s) / double(c));
    return 0;
}