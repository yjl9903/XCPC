#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

string s;

int main(){
    int T, kase = 0; cin >> T; cin.ignore();
    while (T--){
        getline(cin, s);
        stringstream ss(s);
        int isp = 0, isu = 0, isi = 0;
        double P = 0, U = 0, I = 0;
        while (ss >> s){
            if (s.length() < 3) continue;
            if (s[1] != '=') continue;
            double x = 0, y = 1; int i = 2, j = s.length() - 1;
            while (s[j] != 'A' && s[j] != 'V' && s[j] != 'W') j--;
            if (s[j - 1] == 'm'){
                y = 0.001; j--;
            }
            else if (s[j - 1] == 'k'){
                y = 1000; j--;
            }
            else if (s[j - 1] == 'M'){
                y = 1000000; j--;
            }
            string n = s.substr(i, j - i);
            char* tmp = (char*)n.c_str();
            sscanf(tmp, "%lf", &x);
            if (s[0] == 'P') isp = 1, P = x * y;
            if (s[0] == 'U') isu = 1, U = x * y;
            if (s[0] == 'I') isi = 1, I = x * y;
        }
        printf("Problem #%d\n", ++kase);
        if (isp && isu){
            printf("I=%.2lfA\n", P / U);
        }
        else if (isp && isi){
            // printf("%.2lf %.2lf\n", p, i);
            printf("U=%.2lfV\n", P / I);
        }
        else if (isu && isi){
            // printf("%.2lf %.2lf\n", u, i);
            printf("P=%.2lfW\n", U * I);
        }
        puts("");
    }
    return 0;
}