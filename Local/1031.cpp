#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn];

int get(char ch){
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '(') return 0;
    return -1;
}
int cmp(char x, char y){
    return get(x) <= get(y);
}

double cal(){
    stack<double> num; stack<char> ope;
    int len = strlen(s); double ans = 0;
    for (int i = 0; i < len; i++){
        if (s[i] >= '0' && s[i] <= '9') {
            // num.push(double(s[i] - '0'));
            double x; int j = i;
            char tmp[100];
            while ((s[j] <= '9' && s[j] >= '0') || s[j] == '.') tmp[j - i] = s[j], j++;
            s[j - i] = 0;
            sscanf(tmp, "%lf", &x);
            num.push(x);
            i = j - 1;
        }
        else{
            if (s[i] == '(') {
                ope.push(s[i]); continue;
            }
            int flag = 0;
            while (!ope.empty() && cmp(s[i], ope.top())){
                char ch = ope.top(); 
                if (s[i] == ')'){
                    if (flag) break;
                    if (ch == '(') flag = 1;
                }
                ope.pop();
                if (ch == '*'){
                    double x = num.top(); num.pop();
                    double y = num.top(); num.pop();
                    num.push(x * y);
                }
                if (ch == '/'){
                    double x = num.top(); num.pop();
                    double y = num.top(); num.pop();
                    num.push(y / x);
                }
                if (ch == '+'){
                    double x = num.top(); num.pop();
                    double y = num.top(); num.pop();
                    num.push(x + y);
                }
                if (ch == '-'){
                    double x = num.top(); num.pop();
                    double y = num.top(); num.pop();
                    num.push(y - x);
                }
            }
            if (s[i] != ')') ope.push(s[i]);
        }
    }
    return ans = num.top();
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s + 1);
        int len = strlen(s + 1); s[0] = '(', s[len + 1] = ')'; s[len + 2] = '\0';
        printf("%.2lf\n", cal());
    }
    return 0;
}