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
    if (ch == 'd') return 3;
    if (ch == '(') return 0;
    return -1;
}
int cmp(char x, char y){
    return get(x) <= get(y);
}

struct node{
    int x, y;
    node operator+(const node& b)const{
        return node{x + b.x, y + b.y};
    }
    node operator-(const node& b)const{
        return node{x - b.y, y - b.x};
    }
    node operator*(const node& b)const{
        int c = min(min(x * b.x, y * b.y), min(x * b.y, y * b.x));
        int d = max(max(x * b.x, y * b.y), max(x * b.y, y * b.x));
        return node{c, d};
    }
};

node cal(){
    stack<node> num; stack<char> ope;
    int len = strlen(s); int ans = 0;
    bool isNum = 0;
    for (int i = 0; i < len; i++){
        // printf("%c\n", s[i]);
        if (s[i] >= '0' && s[i] <= '9'){
            int j = i;
            char tmp[100];
            while (s[j] <= '9' && s[j] >= '0') tmp[j - i] = s[j], j++;
            tmp[j - i] = 0;
            int x; sscanf(tmp, "%d", &x);
            num.push(node{x, x});
            i = j - 1;
            isNum = 1;
        }
        else{
            if (s[i] == '(') {
                isNum = 0;
                ope.push(s[i]); continue;
            }
            // printf("%c\n", s[i]);
            int flag = 0;
            while (!ope.empty() && cmp(s[i], ope.top())){
                char ch = ope.top(); 
                if (s[i] == ')'){
                    if (flag) break;
                    if (ch == '(') flag = 1;
                }
                ope.pop();
                if (ch == '*'){
                    node x = num.top(); num.pop();
                    node y = num.top(); num.pop();
                    num.push(x * y);
                }
                if (ch == '+'){
                    node x = num.top(); num.pop();
                    node y = num.top(); num.pop();
                    num.push(x + y);
                }
                if (ch == '-'){
                    node x = num.top(); num.pop();
                    node y = num.top(); num.pop();
                    num.push(y - x);
                }
                if (ch == 'd'){
                    node a = num.top(); num.pop();
                    node b = num.top(); num.pop();
                    num.push(node{b.x, a.y * b.y});
                }
            }
            if (s[i] != ')') {
                ope.push(s[i]);
            }
        }
    }
    return num.top();
}

int main(){
    // int T; scanf("%d", &T);
    while (~scanf("%s", s + 1)){
        int len = strlen(s + 1); s[0] = '(', s[len + 1] = ')'; s[len + 2] = '\0';
        // printf("%d %d\n", cal(), cal1());
        node ans = cal();
        printf("%d %d\n", ans.x, ans.y);
    }
    return 0;
}