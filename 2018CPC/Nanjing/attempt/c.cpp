#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

vector<int> deck;
vector<int> hand[maxn];
int n, m, tot;

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        deck.clear(); tot = 0;
        scanf("%d%d", &n, &m);
        for (int i = 0, x; i < m; i++) scanf("%d", &x), deck.push_back(x);
        for (int i = 0; i < n; i++) {
            hand[i].clear();
            for (int j = 1; j <= 5; j++){
                if (tot < deck.size()){
                    hand[i].push_back(deck[tot++]);
                }
            }
        }
        int winner = -1, pass = n - 1, player = 0, card = -1;
        while (winner == -1){
            if (pass == n - 1){
                int m = 20, pos = -1;
                for (int i = 0; i < hand[player].size(); i++){
                    int t = hand[player][i];
                    if (hand[player][i] <= 2) t += 13;
                    if (t < m) m = t, pos = i;
                }
                swap(hand[player][pos], hand[player].back());
                hand[player].pop_back();
                if (m > 13) m -= 13;
                card = m;
                pass = 0;
            }
            else {
                if (card == 2){
                    pass++;
                }
                else {
                    int flag = 1;
                    int tag = card + 1; 
                    if (card == 13) tag = 1;
                    for (int i = 0; i < hand[player].size(); i++){
                        if (hand[player][i] == tag){
                            flag = 0;
                            swap(hand[player][i], hand[player].back());
                            hand[player].pop_back();
                            break;
                        }
                    }
                    if (flag){
                        // pass++;
                        for (int i = 0; i < hand[player].size(); i++){
                            if (hand[player][i] == 2){
                                flag = 0;
                                swap(hand[player][i], hand[player].back());
                                hand[player].pop_back();
                                break;
                            }
                        }
                        if (flag) pass++;
                        else {
                            pass = 0;
                            card = 2;
                        }
                    }
                    else {
                        pass = 0;
                        card = tag;
                    }
                }
                if (pass == n - 1){
                    for (int i = 1; i <= n; i++){
                        if (tot < deck.size()){
                            hand[(i + player) % n].push_back(deck[tot++]);
                        }
                    }
                }
            }
            if (hand[player].empty()){
                winner = player;
                break;
            }
            player = (player + 1) % n;
        }
        printf("Case #%d:\n", ++kase);
        for (int i = 0; i < n; i++){
            if (i == winner) puts("Winner");
            else {
                int s = 0;
                for (int j = 0; j < hand[i].size(); j++)
                    s += hand[i][j];
                printf("%d\n", s);
            }
        }
    }
    return 0;
}