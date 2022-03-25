#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<string,string> PSS;
const int maxn = 1000 + 5;

map<string, int> f;
vector<PSS> books;
vector<int> vis;
int cnt = 0;

int main(){
    string t, t2;
    while (true){
        getline(cin, t);
        if (t[0] == 'E')
            break;
        int len = 1;
        for (; len < t.length(); len++)
            if (t[len] == '"')
                break;
        string tit = t.substr(0, len + 1);
        string nam = t.substr(len + 5);
        books.push_back(make_pair(nam, tit));
        vis.push_back(0);
        //f[tit] = books.size() - 1;
    }
    sort(books.begin(), books.end());
    for (int i = 0; i < books.size(); i++)
        f[books[i].second] = i;
    //for (int i = 0; i < books.size(); i++)
    //    cout << books[i].first << ':' << books[i].second << endl;
    while (true){
        getline(cin, t);
        if (t[0] == 'E')    break;
        if (t[0] == 'B'){
            t2 = t.substr(7);
            int k = f[t2];
            vis[k] = 1;
        }
        else if (t[0] == 'R'){
            t2 = t.substr(7);
            int k = f[t2];
            vis[k] = 2;
        }
        else if (t[0] == 'S'){
            for (int i = 0; i < books.size(); i++){
                if (vis[i] == 2){
                    int flag = -1;
                    for (int j = i - 1; j >= 0; j--){
                        if (vis[j] == 0){
                            flag = j;
                            break;
                        }
                    }
                    if (flag > -1){
                        cout << "Put " << books[i].second << " after " << books[flag].second << endl;
                    }
                    else{
                        cout << "Put " << books[i].second << " first\n";
                    }
                    vis[i] = 0;
                }
            }
            cout << "END" << endl;
        }
    }
    return 0;
}