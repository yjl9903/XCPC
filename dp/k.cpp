#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

vector<string> v1, v2, ans;
string s;
int dp[maxn][maxn];

int main(){
    ios::sync_with_stdio(false);
    while (cin >> s){
        v1.clear(); v2.clear(); ans.clear();
        v1.push_back(s); 
        while (1){
            cin >> s;
            if (s == "#") break;
            v1.push_back(s); 
        }
        while (1){
            cin >> s;
            if (s == "#") break;
            v2.push_back(s);
        }
        ms(dp, 0); 
        for (int i = 0; i < v1.size(); i++){
            for (int j = 0; j < v2.size(); j++){
                if (v1[i] == v2[j]){
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                }
                else {
                    dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
                }
            }
        }
        int len = dp[v1.size()][v2.size()];
        for (int i = v1.size() - 1; i >= 0; i--){
            for (int j = v2.size() - 1; j >= 0; j--){
                if (v1[i] == v2[j] && dp[i + 1][j + 1] == len){
                    ans.push_back(v1[i]); len--;
                }
            }
        }
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++){
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}