#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;
const int v[20] = {0, 0, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 2};

vector<int> deck;
int n, m, num[maxn][20], sum[maxn], tot;

int solve(){
    int card = -1, player = 0; 
    while (true){
        for (int i = 3; i <= 15; i++){
            if (num[player][i]){
                printf("%d %d\n", i, player);
                card = i;
                num[player][i]--;
                sum[player] -= v[i];
                if (!sum[player]) return player;
                break;
            }
        }
        for (int i = (player + 1) % n; i != player; i = (i + 1) % n){
            if (num[i][card + 1]){
                printf("%d %d\n", card + 1, i);
                card++;
                num[i][card]--; sum[i] -= v[card];
                player = i;
            }
            else if (card != 15 && num[i][15]){
                printf("%d %d\n", 15, i);
                card = 15;
                num[i][15]--; sum[i] -= 2;
                player = i;
            }
            if (!sum[i]) return i;
        }
        for (int i = 0; i < n && tot < m; i++){
            num[(i + player) % n][deck[tot]]++;
            sum[(i + player) % n] += v[deck[tot]];
            tot++; 
        }
    }
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        tot = 0;
        deck.clear(); ms(num, 0); ms(sum, 0);
        scanf("%d%d", &n, &m);
        for (int i = 0, x; i < m; i++) scanf("%d", &x), deck.push_back(x < 3 ? x + 13 : x);
        for (int i = 0; i < n && tot < m; i++){
            for (int j = 0; j < 5 && tot < m; j++){
                num[i][deck[tot]]++;
                sum[i] += v[deck[tot]];
                tot++;
            }
        }
        int win = solve();
        printf("Case #%d:\n", ++kase);
        for (int i = 0; i < n; i++){
            if (i == win) puts("Winner");
            else printf("%d\n", sum[i]);
        }
    }
    return 0;
}