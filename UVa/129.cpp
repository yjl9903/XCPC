#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

char a[maxn];
int n, L, cnt = 0;

void dfs(int d){
    int flag = 0;
    for (int i = d - 1; i >= d / 2; i--){
        flag = 1;
        for (int j = 0; j < d - i; j++){
            if (a[d - 1 - j] != a[i - 1 - j]){
                flag = 0;
                break;
            }
        }
        if (flag)   break;
    }

    if (!flag){
        cnt++;
        // for (int i = 0; i < d; cout << a[i++] <<  ' ');
        // cout << endl;
        if (cnt == n){
            for (int i = 0; i < d; i++){
                if (i && i % 64 == 0)    cout << endl;
                else if (i && i % 4 == 0)    cout << " ";
                cout << a[i];
            }
            cout << endl << d << endl;
            return;
        }
    }
    else if (flag == 1)
        return;

    for (int i = 0; i < L && cnt < n; i++){
        a[d] = 'A' + i;
        dfs(d + 1);
    }
}

int main(){
    while (cin >> n >> L && n && L){
        cnt = 0;
        for (int i = 0; i < L && cnt < n; i++){
            a[0] = 'A' + i;
            dfs(1);
        }
    }
    return 0;
}