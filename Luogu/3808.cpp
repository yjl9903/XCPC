#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

struct acAutomation{
    int ch[maxn][26], val[maxn], fail[maxn], cnt;
    void init(){cnt = 0; ms(fail, 0); ms(val, 0); ms(ch, 0);}; 
    acAutomation(){init();}
    void insert(char* s){
        int len = strlen(s), now = 0;
        for (int i = 0; i < len; i++){
            int v = s[i] - 'a';
            if (!ch[now][v]) ch[now][v] = ++cnt;
            now = ch[now][v];
        }
        val[now]++;
    }
    void build(){
        queue<int> q;
        for (int i = 0; i < 26; i++) if (ch[0][i]) fail[ch[0][i]] = 0, q.push(ch[0][i]);
        while (!q.empty()){
            int t = q.front(); q.pop();
            for (int i = 0; i < 26; i++){
                if (ch[t][i]) fail[ch[t][i]] = ch[fail[t]][i], q.push(ch[t][i]);
                else ch[t][i] = ch[fail[t]][i];
            }
        }
    }
    int query(char* s){
        int len = strlen(s), now = 0, ans = 0;
        for (int i = 0; i < len; i++){
            now = ch[now][s[i] - 'a'];
            for (int t = now; t && ~val[t]; t = fail[t]) ans += val[t], val[t] = -1;
        }
        return ans;
    }
}f;

int n;
char s[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%s", s);
        f.insert(s);
    }
    f.build();
    scanf("%s", s);
    printf("%d\n", f.query(s));
    return 0;
}