#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000 + 5;

char s[maxn];
string res;
int n;

int main(){
    while (cin >> n){
        for (int i = 0; i < n; cin >> s[i++]);
        int l = 0, r = n - 1;
        while (l <= r){
            int flag = 1, i = 0;
            while (l + i <= r - i){
                if (s[l + i] < s[r - i]){
                    flag = 1; break;
                }
                if (s[l + i] > s[r - i]){
                    flag = 0; break;
                }
                i++;    
            }
            if (flag) res.push_back(s[l]), l++;
            else res.push_back(s[r]), r--;
        }
        for (int i = 0; i < res.size(); i++){
            if (i && i % 80 == 0) cout << endl;
            cout << res[i];
        }
        cout << endl;
    }
    
    return 0;
}