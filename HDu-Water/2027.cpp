#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

char s[maxn], f[6] = "aeiou";

int main(){
    int T; cin >> T; cin.ignore();
    while (T--){
        cin.getline(s, 102);
        int len = strlen(s), num[5] = {0};
        for (int i = 0; i < len; i++){
            for (int j = 0; j < 5; j++){
                if (s[i] == f[j] || s[i] == f[j] - 'a' + 'A') num[j]++;
            }
        }
        for (int i = 0; i < 5; i++){
            cout << f[i] << ':' << num[i] << endl;
        }
        if (T) cout << endl;
    }
    return 0;
}