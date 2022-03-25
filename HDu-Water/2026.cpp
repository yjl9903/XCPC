#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

char s[maxn];

bool check(char x){
    if (x >= '0' && x <= '9') return 1;
    if (x >= 'a' && x <= 'z') return 1;
    if (x >= 'A' && x <= 'Z') return 1;
    return 0;
}

int main(){
    while (cin.getline(s, 102)){
        int len = strlen(s);
        int i = 0;
        while (s[i] == ' ') i++;
        if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
        while (i < len){
            while (i < len && check(s[i])) i++;
            while (i < len && s[i] == ' ') i++;
            if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
        }
        cout << s << endl;
    }
    return 0;
}