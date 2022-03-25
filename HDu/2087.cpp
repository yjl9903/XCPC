#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn], p[maxn];
int slen, plen, nxt[maxn];

void getnxt(){
    int k = -1, i = 0; nxt[0] = -1;
    while (i < plen - 1){
        if (k == -1 || p[k] == p[i]) k++, i++, nxt[i] = k;
        else k = nxt[k];
    }
    // for (int i = 0; i < plen - 1; i++) cout << nxt[i] << ' '; cout << endl;
}
int kmp(){
    getnxt();
    int i = 0, j = 0, res = 0;
    while (i < slen && j < plen){
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = nxt[j];

        if (j == plen){
            res++; j = 0;
        }
    }
    return res;
}

int main(){
    while (cin >> s >> p){
        if (s[0] == '#') break;
        slen = strlen(s); plen = strlen(p);
        cout << kmp() << endl;
    }
    return 0;
}