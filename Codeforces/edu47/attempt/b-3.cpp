#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];

int main(){
    cin >> s;
    int len = strlen(s), cnt = 0, flag = 1;
    for (int i = 0; i < len; i++) if (s[i] == '1') cnt++;
    for (int i = 0; i < len; i++){
        if (s[i] == '2' && flag){
            flag = 0;
            for (int i = 0; i < cnt; i++) cout << 1;
            cout << 2;
        }
        else if (s[i] == '2') cout << 2;
        else if (s[i] == '0') cout << 0;
    }
    if (flag) for (int i = 0; i < cnt; i++) cout << 1;
    return 0;
}