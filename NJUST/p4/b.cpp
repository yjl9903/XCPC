#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <stack>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;
const int maxl = 1000 + 5;

string cmd;
vector<int> v1;
vector<double> v2;
map<string,int> m1;
map<string,double> m2;

bool check(char ch){
    if (ch >= '0' && ch <= '9') return true;
    if (ch >= 'a' && ch <= 'z') return true;
    if (ch >= 'A' && ch <= 'Z') return true;
    return false;
}
bool rank(char t, char p){ // t > p : 1, t < p : -1, t == p : 0 
    if (p == '+' || p == '-1'){
        if (t == '(')
            return -1;
        return 1;
    }
    if (p == '*' || p == '/'){
        if (t == '*' || t == '/' || t == ')')
            return -1;
        return 1;
    }
    if (p == '(') return -1;
    return 0;
}

int cal1(string s){
    stack<int> num; stack<char> symbol; symbol.push('(');
    int i = 0, flag = 1; // 1前一个是数字， 0前一个是符号
    while (i < s.length()){
        if (s[i] == '+'){
            if (symbol.top() == '*'){
                int x = num.top(); num.pop();
                int y = num.top(); num.pop();
                num.push(x * y);
            }
            else if (symbol.top() == '/'){
                int x = num.top(); num.pop();
                int y = num.top(); num.pop();
                num.push(y / x);
            }
        }
        else if (s[i] == '-'){

        }
        else if (s[i] == '*'){

        }
        else if (s[i] == '/'){

        }
        else if (s[i] == '('){
            symbol.push('(');
        }
        else if (s[i] == ')'){
            
        }
        else if (s[i] >= '0' && s[i] <= '9'){
            int sum = 0;
            while (s[i] >= '0' && s[i] <= '9') sum = sum * 10 + s[i] - '0';
            num.push(sum);
            flag = 1;
        }
        else{
            int start = i;
            while (check(s[i])) i++;
            string st = s.substr(start, i - start);
            if (m1.count(st)) num.push(v1[m1[st]]);
            else if (m2.count(st)) num.push(v2[m2[st]]);
            flag = 1;
        }

        while (s[i] == ' ') i++;
    }
}
double cal2(string s){
    stack<double> num; stack<char> symbol;

}

int main(){
    int T; cin >> T; cin.ignore();
    while (T--){
        getline(cin, cmd);
        // cout << cmd << endl;
        int flag = 0, k = 0;
        while (cmd[k] == ' ') k++;
        if (cmd[k] >= '0' && cmd[k] <= '9') continue;
        if (cmd[k] == 'i' && cmd[k + 1] == 'n' && cmd[k + 2] == 't' && cmd[k + 3] == ' '){
            int start = k + 4, end = k + 4;
            for (; start < cmd.length() - 1;){
                if (cmd[start] == ' ' || cmd[start] == ';' || cmd[start] == ','){
                    start++; continue;
                }
                end = start;
                while (cmd[end] != ' ' && cmd[end] != ',' && cmd[end] != ';') end++;
                // cout << start << ' ' << end << endl;
                string s = cmd.substr(start, end - start);
                cout << s << endl;
                m1[s] = v1.size();
                v1.push_back(0);
                start = end + 1;
            }
            continue;
        }
        if (cmd[k] == 'd' && cmd[k + 1] == 'o' && cmd[k + 2] == 'u' && cmd[k + 3] == 'b' && cmd[k + 4] == 'l' && cmd[k + 5] == 'e' && cmd[k + 6] == ' '){
            int start = k + 7, end = 7;
            for (; start < cmd.length() - 1;){
                if (cmd[start] == ' ' || cmd[start] == ';' || cmd[start] == ','){
                    start++; continue;
                }
                end = start;
                while (cmd[end] != ' ' && cmd[end] != ',' && cmd[end] != ';') end++;
                string s = cmd.substr(start, end - start);
                cout << s << endl;
                m2[s] = v2.size();
                v2.push_back(0.0);
                start = end + 1;
            }
            continue;
        }
        if (cmd[k] == 'p' && cmd[k + 1] == 'r' && cmd[k + 2] == 'i' && cmd[k + 3] == 'n' && cmd[k + 4] == 't' && cmd[k + 5] == '('){
            int start = k + 6;
            while (cmd[start] == ' ') start++;
            int end = start;
            while (cmd[end] != ' ' && cmd[end] != ')') end++;
            string s = cmd.substr(start, end - start);
            cout << s << endl;
            if (m1.count(s)){
                cout << v1[m1[s]] << endl;
            }
            else if (m2.count(s)){
                // cout << v2[m2[s]] << endl;
                printf("%.6f\n", v2[m2[s]]);
            }
            continue;
        }
        vector<string> tmp;
        int start = k, end = k;
        while (start < cmd.length() - 1){
            end = start;
            while (cmd[end] != '=' && cmd[end] != ';') end++;

            string s = cmd.substr(start, end - start);
            cout << s << endl;
            tmp.push_back(s);

            start = end + 1;
            while (cmd[start] == ' ') start++;
        }
        if (tmp.size() == 1) continue;

    }
    return 0;
}