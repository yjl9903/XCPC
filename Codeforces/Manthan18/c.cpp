#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

char a[maxn], b[maxn];
int n, vis[maxn];
vector<int> s[2];

int main(){
    scanf("%d%s%s", &n, a, b);
    for (int i = 0; i < n; i++){
        if (a[i] != b[i]) /* s[a[i] - '0'].push_back(i); */
            vis[i] = a[i] - '0' + 1;
    }
    int ans = 0, tot = 0;
    for (int i = 1; i < n; i++){
        if (vis[i] != 0 && vis[i - 1] != 0 && vis[i] != vis[i - 1]){
            ans++; vis[i] = vis[i - 1] = 0;
        }
    }
    for (int i = 0; i < n; i++) if (vis[i]) ans++;
    printf("%d", ans);
    return 0;
}