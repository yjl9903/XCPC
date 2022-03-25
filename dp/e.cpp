#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

const string f[26] = {
    "4", "|3", "(", "|)",
    "3", "|=", "6", "#",
    "|", "_|", "|<", "|_",
    "|V|", "|\\|", "0", "|0",
    "(,)", "|?", "5", "7",
    "|_|", "V", "VV", "><", 
    "-/", "2"
};
char s[maxn];
int dp[maxn * 3];

int main(){
    while (~scanf("%s", s)){
        if (s[0] == 'e' && s[1] == 'n' && s[2] == 'd') return 0;
        string t;
        for (int i = 0; s[i]; i++) t += f[s[i] - 'A'];
        // cout << t << endl;
        ms(dp, 0); dp[0] = 1; 
        for (int i = 1; i <= t.length(); i++){
            for (int j = i - 1; j >= i - 3 && j >= 0; j--){
                string tmp = t.substr(j, i - j);
                for (int k = 0; k < 26; k++) if (tmp == f[k]) dp[i] += dp[j];
            }
        }
        printf("%d\n", dp[t.length()]);
    }
    return 0;
}