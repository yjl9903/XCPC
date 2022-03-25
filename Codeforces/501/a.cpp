#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, vis[maxn] = {0};
vector<int> v;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++){
        int x, y; scanf("%d%d", &x, &y);
        for (int j = x; j <= y; j++) vis[j] = 1;
    }
    for (int i = 1; i <= m; i++) if (!vis[i]) v.push_back(i);
    printf("%d\n", v.size());
    for (int i = 0; i < v.size(); i++){
        if (i) putchar(' ');
        printf("%d", v[i]);
    }
    return 0;
}