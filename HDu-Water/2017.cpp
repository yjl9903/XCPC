#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;



int main(){
    string s;
    int T; cin >> T;
    while (T--){
        cin >> s;
        int res = 0;
        for (int i = 0; i < s.length(); i++){
            if (s[i] <= '9' && s[i] >= '0') res++;
        }
        cout << res << endl;
    }
    return 0;
}