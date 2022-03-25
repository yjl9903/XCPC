#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 1000;

char s[maxn], p[maxn];
int nxt[maxn];

void getnxt(char p[]){
    int len = strlen(p), k = -1, i = 0; nxt[0] = -1;
    while (i < len){
        if (k == -1 || p[k] == p[i]) i++, k++, nxt[i] = k;
        else k = nxt[k];
    }
}
int kmp(char s[], char p[]){
    getnxt(p);
    int slen = strlen(s), plen = strlen(p), i = 0, j = 0;
    while (i < slen && j < plen){
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = nxt[j];
    }
    if (j == plen) return i - j;
    return -1;
}

int main(){
    while (cin >> s >> p){
        cout << kmp(s, p) << endl;
    }
    return 0;
}