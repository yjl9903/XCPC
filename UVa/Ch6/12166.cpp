#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int leaf[maxn], cnt = 0;
map<ll,int> m;
string s;

void dfs(int i, int height){
    if (s[i] == '['){
        int p = 0;
        for (int j = i + 1; j < s.length(); j++){
            if (s[j] == '[')    p++;
            if (s[j] == ']')    p--;
            if (p == 0 && s[j] == ','){
                dfs(i + 1, height + 1);
                dfs(j + 1, height + 1);
                break;
            }
        }
    }
    else if (s[i] >= '0' && s[i] <= '9'){
        ll w = 0;
        while (s[i] >= '0' && s[i] <= '9'){
            w = w * 10 + s[i] - '0';
            i++;
        }
        // cout << '>' << w << endl;
        // leaf[cnt++] = w;
        cnt++;
        m[w << height]++;
    }
}

int main(){
    int T; cin >> T;
    while (T--){
        m.clear();  cnt = 0;
        cin >> s;
        dfs(0, 0);
        int res = 0;
        for (map<ll,int>::iterator i = m.begin(); i != m.end(); i++){
            // cout << '>' << i -> second << endl;
            res = max(res, i -> second);
        }
        cout << cnt - res << endl;
    }
    return 0;
}