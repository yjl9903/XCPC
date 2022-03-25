#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int a[maxn], x, y;

int check(){
    for (int i = x + 39; i <= y + 39; i++){
        int t = a[i];
        for (int j = 2; j * j <= t; j++) if (t % j == 0) return false;
    }
    return true;
}

int main(){
    for (int i = -39; i <= 50; i++){
        a[i + 39] = i * i + i + 41;
    }
    int kase = 0;
    while (cin >> x >> y){
        if (!x && !y) break;
        if (check()) cout << "OK";
        else cout << "Sorry";
        cout << endl;
    }
    return 0;
}