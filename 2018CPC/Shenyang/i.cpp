#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

string f[16] = {
    "0000", "0001", "0010", "0011", 
    "0100", "0101", "0110", "0111", 
    "1000", "1001", "1010", "1011", 
    "1100", "1101", "1110", "1111"
};

char s[maxn];

int trie[5 * maxn][2], tot, m, n;
int val[5 * maxn];
void insert(char *s, int ch){
    int now = 0, len = strlen(s);
    for(int i = 0; i < len; i++){
        int t = s[i] - '0';
        if(!trie[now][t]) trie[now][t] = ++tot;
        now = trie[now][t];
    }
    val[now] = ch;
}
void query(string s){
    string ans;
    int now = 0;
    for (int i = 0; i < s.length(); i++){
        now = trie[now][s[i] - '0'];
        if (val[now] != -1){
            ans.push_back(val[now]);
            now = 0;
        }
        if (ans.length() >= m) {cout << ans << '\n'; return;}
    }
    cout << ans << '\n';
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &m, &n);
        ms(val, -1); ms(trie, 0); tot = 0;
        for (int i = 0; i < n; i++){
            int ch;
            scanf("%d%s", &ch, s);
            insert(s, ch);
        }
        scanf("%s", s);
        int len = strlen(s);
        string str, s2;
        for (int i = 0; i < len; i++) {
            if (s[i] >= 'A' && s[i] <= 'Z') str += f[s[i] - 'A' + 10];
            else if (s[i] >= 'a' && s[i] <= 'z') str += f[s[i] - 'a' + 10];
            else str += f[s[i] - '0'];
        }
        // cout << str << endl;
        for (int i = 0; i < str.length(); i += 9){
            if (i + 8 >= str.length()) break;
            int sum[2] = {0, 0};
            for (int j = i; j < i + 8; j++) sum[str[j] - '0']++;
            char ch;
            if (sum[1] % 2) ch = '0'; else ch = '1';
            if (str[i + 8] == ch) s2 += str.substr(i, 8);
        }
        // cout << s2 << endl;
        // cout << query(s2) << endl;
        query(s2);
    }
    return 0;
}