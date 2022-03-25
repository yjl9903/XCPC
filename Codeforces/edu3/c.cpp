#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

char s[maxn]; int n, cnt[30];

void print(){
    int flag = -1;
    for (int i = 0; i < 26; i++){
        if (cnt[i] & 1) flag = i;
        int x = cnt[i] / 2;
        while(x--) putchar(i + 'a');
    }
    if (flag != -1) putchar(flag + 'a');
    for (int i = 25; i >= 0; i--){
        int x = cnt[i] / 2;
        while(x--) putchar(i + 'a');
    }
}

int main(){
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
    vector<int> v;
    for (int i = 0; i < 26; i++){
        if (cnt[i] & 1) v.push_back(i);
    }
    // if (v.size() <= 1) return print(), 0;
    for (int i = 0; i < v.size() / 2; i++){
        cnt[v[i]]++;
        cnt[v[v.size() - 1 - i]]--;
    }
    print();
    return 0;
}