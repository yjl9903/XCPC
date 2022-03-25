#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

set<char> f;
char s[maxn];

int main(){
    f.insert('a'); f.insert('i'); f.insert('u'); f.insert('e'); f.insert('o');
    cin >> s;
    int len = strlen(s);
    for (int i = 0; i < len; i++){
        if (f.count(s[i]) || s[i] == 'n') continue;
        if (!f.count(s[i + 1]) || i + 1 >= len){
            cout << "NO"; return 0;
        }
    }
    cout << "YES";
    return 0;
}