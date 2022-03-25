#include<iostream>
#include<string>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;
int nextc[1000010][30];
char str1[1000010];
char s[1000010]; 

int main() {
    scanf("%s",s + 1);
    int len = strlen(s + 1);
    for (int i = len; i >= 1; i--) {
        for (int j = 0; j < 26; j++) {
            nextc[i - 1][j] = nextc[i][j]; 
        }
        nextc[i - 1][s[i] - 'a'] = i; 
    }
    int t;
    cin >> t;
    while(t--) {
        scanf("%s",str1);
        int len1 = strlen(str1);
        bool flag = false;
        for (int i = 0, now = 0; i < len1; i++) {
            now = nextc[now][str1[i] - 'a'];
            if (now == 0) {
                flag = true;
                break;
            }
        }
        if (flag) {
            puts("NO");
        } else {
            puts("YES");
        }
    }
    return 0;
}