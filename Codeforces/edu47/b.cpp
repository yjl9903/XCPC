#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];

int main(){
    ms(s, 0);
    cin >> s;
    int res = 0, i = 0, j = 0, len = strlen(s);
    while (i < len && j < len){
        while (s[j] < '2' && s[j] >= '0') j++;
        // sort(s + i, s + j);
        // while (s[i] == '0') i++;
        while (s[j] > '0') j++;
        sort(s + i, s + j);
        i = j;
    }
    // int res = 0, len = strlen(s);
    // for (int i = 1; i < len; i++){
    //     for (int j = i - 1; j >= 0; j--)
    //         if (s[j] - s[j + 1] == 1) swap(s[j], s[j + 1]);
    // }
    cout << s;
    return 0;
}