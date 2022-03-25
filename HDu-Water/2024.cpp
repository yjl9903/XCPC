#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

char s[maxn];

bool check(char x){
    if (x >= '0' && x <= '9') return 1;
    if (x >= 'a' && x <= 'z') return 1;
    if (x >= 'A' && x <= 'Z') return 1;
    if (x == '_') return 1;
    return 0;
}


int main(){
    int T; cin >> T; cin.ignore();
    while (T--){
        cin.getline(s, 52);
        if (s[0] >= '0' && s[0] <= '9'){
            cout << "no" << endl; continue;
        }
        int len = strlen(s), flag = 1;
        for (int i = 0; i < len; i++){
            if (!check(s[i])){
                flag = 0; break;
            }
        }
        if (flag) {
            cout << "yes\n";
        }
        else {
            cout << "no\n";
        }
    }
    return 0;
}