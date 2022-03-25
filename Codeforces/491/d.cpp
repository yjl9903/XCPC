#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

char s[2][maxn];

int main(){
    cin >> s[0] >> s[1];
    int len = strlen(s[0]), i = 0, res = 0;
    while (i < len){
        // cout << i << endl;
        int flag = 1;
        for (int j = 0; j < 3 && i + j < len; j++){
            if (s[0][i + j] != '0' || s[1][i + j] != '0')
                flag = 0;
        }
        if (i + 2 < len && flag){
            res += 2;
            i += 3;
            continue;
        }
        int t = 0;
        for (int j = 0; j < 2 && i + j < len; j++){
            if (s[0][i + j] == '0')
                t++;
            if (s[1][i + j] == '0')
                t++;
        }
        if (t >= 3){
            res += 1;
            i += 2;
            continue;
        }
        i++;
    }
    cout << res;
    return 0;
}