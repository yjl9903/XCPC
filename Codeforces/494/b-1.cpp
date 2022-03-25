#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int a, b, x;
char res[maxn];

int main(){
    ms(res, '\0');
    cin >> a >> b >> x;
    int s[2] = {0}, t = 1;
    char ch[2] = {'0', '1'};
    if (a < b) swap(ch[0], ch[1]), swap(a, b);
    
    int i = 2;
    res[0] = ch[0], res[1] = ch[1];
    for (; i < a + b - 1; i += 2){
        if (t >= x - 1) break;
        res[i] = ch[0]; res[i + 1] = ch[1]; s[0]++, s[1]++;
        t += 2;
    }
    // cout << t << endl;
    if (t == x - 1){
        cout << res;
        for (int i = s[1]; i < b - 1; i++) cout << ch[1];
        for (int i = s[0]; i < a - 1; i++) cout << ch[0];
    }
    else {
        for (int i = s[0]; i < a - 1; i++) cout << ch[0];
        cout << res;
        for (int i = s[1]; i < b - 1; i++) cout << ch[1];
    }
    return 0;
}