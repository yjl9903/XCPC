#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;

int f[10];

void init(){
    f[0] = 1;
    for (int i = 1; i < 10; i++)
        f[i] = f[i - 1] * i;
}

int cantor(int x[], int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        int temp = 0;
        for (int j = i + 1; j < n; j++)
            if (x[i] > x[j])
                temp++;
        sum += f[n - 1 - i] * temp;
    }
    return sum;
}

int cantor(int t, int x[], int n){
    int vis[10] = {0};
    for (int i = n - 1; i >= 0; i--){
        int k = t / f[i]; t = t % f[i];
        int j = 1, s = 0;
        while (s < k || vis[j]){
            if (!vis[j]) s++;
            j++;
        }
        vis[j] = 1; x[n - 1 - i] = j;
    }
    return 0;
}

int main(){
    init();
    int s[10], n, t;
    // Cantor展开
    // while (cin >> n){
    //     if (n > 10) break;
    //     for (int i = 0; i < n; cin >> s[i++]);
    //     cout << cantor(s, n) << endl;
    // }

    //逆Cantor展开
    while (cin >> t >> n){
        if (n > 10) break;
        cantor(t, s, n);
        for (int i = 0; i < n; i++)
            cout << s[i] << ' ';
        cout << endl;
    }
    return 0;
}