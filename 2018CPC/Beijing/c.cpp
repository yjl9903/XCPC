#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

// vector<int> deck[4];
int deck[4][15];
char ch[3];

int f(char a[]){
    if (a[0] == 'A') return 1;
    if (a[0] == '1') return 10;
    if (a[0] > '1' && a[0] <= '9') return a[0] - '0';
    if (a[0] == 'J') return 11;
    if (a[0] == 'Q') return 12;
    if (a[0] == 'K') return 13;
}
char* g(int x){
    ch[1] = ch[2] = '\0';
    if (x == 1) ch[0] = 'A';
    else if (x == 10) ch[0] = '1', ch[1] = '0';
    else if (x >= 2 && x <= 9) ch[0] = x + '0';
    else if (x == 11) ch[0] = 'J';
    else if (x == 12) ch[0] = 'Q';
    else if (x == 13) ch[0] = 'K';
    return ch;
}

int get(int k){
    if (deck[k][10]) return 10;
    for (int i = 2; i <= 9; i++) if (deck[k][i]) return i;
    if (deck[k][1]) return 1;
    if (deck[k][11]) return 11;
    if (deck[k][13]) return 13;
    if (deck[k][12]) return 12;
    return 0;
}

int main(){
    while (~scanf("%s", ch)){
        // for (int i = 0; i < 4; i++) deck[i].clear();
        // deck[0].push_back(f(ch));
        ms(deck, 0); deck[0][f(ch)]++;
        for (int i = 1; i < 13; i++) scanf("%s", ch), deck[0][f(ch)]++;
        for (int i = 1; i < 4; i++) for (int j = 0; j < 13; j++) scanf("%s", ch), deck[i][f(ch)]++;
        int tot = 0, winner = -1, rk = 1;
        while (winner == -1){
            int card = 0, num = 0, card2 = 0;
            if (tot == 0){
                num = 1;
                if (deck[0][rk]) deck[0][rk]--, card = rk;
                else card = get(0), deck[0][card]--;
            }
            if (tot == 1){
                if (deck[1][rk]) num = deck[1][rk], deck[1][rk] = 0, card = rk;
                else card = get(1), num = 1, deck[1][card]--;
            }
            if (tot == 2){
                if (deck[2][rk]) num = deck[2][rk], deck[2][rk] = 0, card = rk;
                else {
                    num = 100;
                    if (deck[2][10] < num) num = deck[2][10], card = 10;
                    for (int i = 2; i <= 9; i++) if (deck[2][i] < num) num = deck[2][i], card = i;
                    if (deck[2][1] < num) num = deck[2][1], card = 1;
                    if (deck[2][11] < num) num = deck[2][11], card = 11;
                    if (deck[2][13] < num) num = deck[2][13], card = 13;
                    if (deck[2][12] < num) num = deck[2][12], card = 12; 
                    deck[2][card] = 0;
                }
            }
            if (tot == 3){
                if (deck[3][rk] == 3 || deck[3][rk] == 4) num = deck[3][rk], deck[3][rk] = 0, card = rk;
                else {
                    if (deck[3][rk]) num = deck[3][rk], deck[3][rk] = 0, card = rk;
                    card2 = get(3); if (card2) deck[3][card2]--;
                }
            }
            // dbg(card, num);
            for (int i = 1; i < 4; i++){
                int pl = (tot + i) % 4, flag = -1;
                if (pl == 0){
                    if (tot == 3 && !deck[0][rk + 1 > 13 ? rk - 12 : rk + 1]) flag = 0;
                    if (num + (card2 ? 1 : 0) + deck[0][rk] > 4) flag = 0;
                }
                if (pl == 1){
                    if (tot == 0 && !deck[1][rk + 1 > 13 ? rk - 12 : rk + 1]) flag = 1;
                }
                if (pl == 2){
                    if (deck[2][rk] >= 4) flag = 2;
                }
                if (pl == 3){
                    int c = 0; for (int i = 1; i <= 13; i++) c += deck[tot][i];
                    if (c == 0) flag = 3;
                }
                if (flag != -1){
                    if (card2 == 0){
                        if (card == rk) deck[flag][rk] += num;
                        else deck[tot][card] += num;
                    }
                    else {
                        if (card){
                            deck[tot][card2]++; deck[tot][card] += num;
                        }
                        else {
                            if (card2 == rk) deck[flag][rk]++;
                            else deck[tot][card2]++;
                        }
                    }
                    break;
                }
            }
            if (get(tot) == 0) winner = tot;

            printf("tot: %d\nrk: %d\n", tot, rk);
            for (int i = 0; i < 4; i++){
                if (i == winner) puts("WINNER");
                else {
                    int c = 0;
                    for (int k = 1; k <= 13; k++){
                        g(k); 
                        for (int j = 0; j < deck[i][k]; j++){
                            if (c++) putchar(' ');
                            printf("%s", ch);
                        }
                    }
                    puts("");
                }
            }
            puts("");

            tot = (tot + 1) % 4; 
            rk++; if (rk > 13) rk -= 13;
        }

        for (int i = 0; i < 4; i++){
            if (i == winner) puts("WINNER");
            else {
                int c = 0;
                for (int k = 1; k <= 13; k++){
                    g(k); 
                    for (int j = 0; j < deck[i][k]; j++){
                        if (c++) putchar(' ');
                        printf("%s", ch);
                    }
                }
                puts("");
            }
        }
    }
    return 0;
}