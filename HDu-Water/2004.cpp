#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;

int main(){
    while (cin >> n){
        char res;
        if (n <= 100 && n >= 0){
            n /= 10;
            switch(n){
            case 10: 
            case 9:
                res = 'A'; break;
            case 8:
                res = 'B'; break;
            case 7:
                res = 'C'; break;
            case 6:
                res = 'D'; break;
            default:
                res = 'E'; break;
            }
            cout << res << endl;
        }
        else cout << "Score is error!\n";
        

    }
    return 0;
}