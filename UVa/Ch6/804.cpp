#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#define ms(a,b) memset(a,b,sizeof a)
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int weight[maxn], NP, NT ,NF;
vector<map<int,int>> from, to;

int main(){
    int kase = 0;
    while (cin >> NP && NP){
        ms(weight, 0);
        from.clear();   to.clear();
        for (int i = 1; i <= NP; cin >> weight[i++]);
        cin >> NT;
        for (int i = 1; i <= NT; i++){
            int x;
            map<int,int> f, t;
            while (cin >> x && x){
                if (x < 0){
                    f[-x]++;
                }
                else{
                    t[x]++;
                }
            }
            from.push_back(f);  to.push_back(t);
        }
        cin >> NF;
        int flag = 1, k = 1;
        for (; k <= NF && flag; k++){
            flag = 0;
            for (int i = 0; i < NT; i++){
                int mark = 1;
                map<int,int> f = from[i], t = to[i];
                for (map<int,int>::iterator j = f.begin(); j != f.end(); j++){
                    // cout << j -> first << ' ' << j -> second << endl;
                    if (weight[j -> first] < j -> second){
                        mark = 0;   break;
                    }
                }
                if (mark){
                    for (map<int,int>::iterator j = f.begin(); j != f.end(); j++){
                        weight[j -> first] -= j -> second;
                    }
                    for (map<int,int>::iterator j = t.begin(); j != t.end(); j++){
                        weight[j -> first] += j -> second;
                    }
                    flag = 1;
                    break;
                }
            }
        }
        cout << "Case " << ++kase << ": ";
        if (flag){
            cout << "still live after " << NF << " transitions" << endl;
        }
        else{
            cout << "dead after " << k - 2 << " transitions" << endl;
        }
        cout << "Places with tokens:";
        for (int i = 1; i <= NP; i++){
            if (weight[i]){
                cout << " " << i << " (" << weight[i] << ")";
            }
        } 
        cout << endl << endl;
    }
    return 0;
}