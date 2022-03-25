#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

char x[maxn];

int main(){
    int T; cin >> T; cin.ignore();
    while (T--){
        stack<char> s;
        //cin.ignore();
        cin.getline(x, maxn);
        int len = strlen(x), flag = 1;
        for (int i = 0; i < len; i++){
            if (x[i] == '(' || x[i] == '[')
                s.push(x[i]);
            else if (x[i] == ')'){
                if (!s.empty() && s.top() == '('){
                    s.pop();
                }
                else{
                    flag = 0; break;
                }
            }
            else if (x[i] == ']'){
                if (!s.empty() && s.top() == '['){
                    s.pop();
                }
                else {
                    flag = 0; break;
                }
            }
        }
        if (flag && s.empty()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}