#include <cstdio>
#include <cstring>
#include <queue>
#define void inline void
using namespace std;
const int maxn = 1000000 + 5;

struct ACautomation{
    int ch[maxn][26], fail[maxn], cnt[maxn], cnt;
    void init(){ cnt = 0; ms(cnt, 0); ms(ch, 0); ms(fail, 0); }
    ACautomation(){init();}
    void insert(char *s){
        int len = strlen(s), now = 0;
        for (int i = 0; i < len; i++){
            if (ch[now][s[i] - 'a'] == 0) ch[now][s[i] - 'a'] = ++cnt;
            now = ch[now][s[i] - 'a'];
        }   
        cnt[now]++;
    }
    void getFail(){
        queue<int> q;
        for (int i = 0; i < 26; i++){
            if (ch[0][i]){
                fail[ch[0][i]] = 0;
                q.push(ch[0][i]);
            }
        }
        while (!q.empty()){
            int t = q.top(); q.pop();
            for (int i = 0; i < 26; i++){
                if (ch[t][i]){
                    fail[ch[t][i]] = ch[fail[t]][i];
                    q.push(ch[t][i]);
                }
                else ch[t][i] = ch[fail[t]][i];
            }
        }
    }
    int query(char* s){
        int len = strlen(s), now = 0, ans = 0;
        for (int i = 0; i < len; i++){
            now = ch[now][s[i] - 'a'];
            
        }
        return ans;
    }
}f;

int main(){
    
    return 0;
}