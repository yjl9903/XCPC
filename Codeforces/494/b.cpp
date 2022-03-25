#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int a, b, x;
char res[maxn];

int main(){
    ms(res, '\0');
    cin >> a >> b >> x;
    int s[2] = {0}, t = a + b - 1;
    char ch[2] = {'0', '1'};
    if (a < b) swap(ch[0], ch[1]), swap(a, b);
    
    for (int i = 0; i < a + b; i++){
        res[i] = ch[i % 2]; s[i % 2]++;
    }
    for (int i = 1; i < a + b; i += 2){
        if (s[1] > b) {
            res[i] = ch[0], s[1]--, s[0]++;
            t -= 2;
        }
    }
    if (t == x){
        cout << res; return 0;
    }
    int k = (res[a + b - 1] == ch[1] ? a + b - 1 : a + b - 2);
    if (t < x) swap(res[1], res[k]);
    while (t > x){
        // cout << t << endl;
        // cout << res << endl;
        int c = k - 1; while (res[c] == ch[0] && c >= 0) c--;
        // cout << c << ' ' << k << endl;
        swap(res[c], res[--k]);
        t -= 2;
    }
    cout << res;
    return 0;
}