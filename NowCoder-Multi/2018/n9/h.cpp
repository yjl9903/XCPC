#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int maxk = 40 + 5;
const int mod = 1000000007;

int n, m, k, tree[maxn][maxk];

int lowbit(int x){return x & -x;}
int query(int i, int j){
    int ans = 0;
    while (j > 0){
        ans = (ans + tree[i][j]) % mod;
        j += lowbit(j);
    }
    return ans;
}
void update(int j, int x){
    tree[1][j] += x;
    int i = 2;
    while (i <= k + 1){
        // tree[i][j] = (tree[i][j] + query(i - 1, j)) % mod;
        int c = j;
        while (j > 0){
            tree[i][j] = (tree[i][j] + query(i - 1, j)) % mod;
            j += lowbit(j);
        }
        i++;
    }
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    int cmd, x, y;
    while (m--){
        scanf("%d", &cmd);
        if (cmd == 0){
            scanf("%d%d", &x, &y);

        }
        else if (cmd == 1){
            scanf("%d", &x);

        }
    }
    return 0;
}