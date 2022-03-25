#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;

char f[26][5] = {".-", "-...", "-.-.", "-..",
    ".", "..-.", "--.", "....", 
    "..", ".---", "-.-", ".-..",
    "--", "-.", "---", ".--.", 
    "--.-", ".-.", "...", "-", 
    "..-", "...-", ".--", "-..-",
    "-.--", "--.."
};

char ss[maxn], tmp[maxn], st[maxn];
int n, dp[maxn];
map<string, int> mp;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", ss); int len = strlen(ss);
        scanf("%d", &n);
        mp.clear();
        for (int i = 0; i < n; i++){
            scanf("%s", tmp);
            string s;
            for (int j = 0; tmp[j] != '\0'; j++){
                s += f[tmp[j] - 'A'];
            }
            mp[s]++;
        }
        ms(dp, 0); dp[0] = 1;
        for (int i = 1; i <= len; i++){
            for (int j = i - 1; j >= i - 81 && j >= 0; j--){
                if (dp[j] == 0) continue;
                for (int k = j; k < i; k++) st[k - j] = ss[k];
                st[i - j] = 0;
                dp[i] += dp[j] * mp[st];
            }
        }
        printf("%d\n", dp[len]);
    }
    return 0;
}