#include <iostream>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int vis[maxn];
string res[maxn];
int check(string s, int t){
    int cnt = 0;
    for (int i = s.length() - 1; i >= 0; i--){
        cnt = (cnt * 10 + s[i] - '0') % t;
    }
    return cnt;
}
void bfs(){
    int cnt = 0;
    queue<string> q;
    string a("0"), b("1"); q.push(a); q.push(b);
    while (!q.empty()){
        // if (cnt >= 200) return;
        string t = q.front(); q.pop();
        int flag = (t[t.length() - 1] == '1');
        for (int i = 0; i < t.length() && !flag; i++) if (t[i] == '1'){
            flag = 1; break;
        }
        if (flag) {
            for (int i = 1; i <= 200; i++) if (!vis[i]){
                // cout << t << ' ' << i << ' ' << check(t, i) << endl;
                if (check(t, i) == 0){
                    vis[i] = 1; cnt++;
                    string s = t; reverse(s.begin(), s.end());
                    // cout << s << ' ' << i << ' ' << cnt << endl;
                    res[i] = s;
                    if (cnt == 198) return;
                }
            }
        }
        string s1 = t + a, s2 = t + b;
        // cout << s1 << ' ' << s2 << endl;
        q.push(s1); 
        q.push(s2);
    }
}

int main(){
    int n; bfs(); res[198] = string("1111111111111111110"); res[99] = string("111111111111111111");
    // cout << "OK\n";
    while (cin >> n && n){
        cout << res[n] << endl;
    }
    return 0;
}