#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int a[maxn], b[maxn], nxt[maxn], n, m;

void getnxt(int str[]){
    int len = n, k = -1, i = 0; nxt[0] = -1;
    while (i < len - 1){
        if (k == -1 || str[i] == str[k]) k++, i++, nxt[i] = k;
        else k = nxt[k];
    }
    // for (int i = 0; i < len; i++) cout << nxt[i] << ' '; cout << endl;
}
int kmp(int str[], int ptr[]){
    int i = 0, j = 0, slen = n, plen = m;
    getnxt(ptr);
    while (i < slen && j < plen){
        if (j == -1 || str[i] == ptr[j]) i++, j++;
        else j = nxt[j];
    }
    if (j == plen) return i - j;
    else return -1;
}

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n >> m;
        for (int i = 0; i < n; cin >> a[i++]);
        for (int i = 0; i < m; cin >> b[i++]);
        int res = kmp(a, b);
        cout << (res == -1 ? -1 : res + 1) << endl;
    }
    return 0;
}