#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;

int D, P;

bool checkTime(const string& time) {
  assert(time.length() == 5);
  int x = (time[0] - '0') * 10 + (time[1] - '0');
  int y = (time[3] - '0') * 10 + (time[4] - '0');
  return 0 <= x && x <= 23 && 0 <= y && y <= 59;
}

bool checkID(const string& id) {
  if (id.length() == 18) {
    for (int i = 0; i < 18; i++) {
      if ('0' <= id[i] && id[i] <= '9') {
      } else {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

struct Node {
  string name, id, time;
  int body, dfn;

  bool operator < (const Node& rhs) const {
    if (time == rhs.time) {
      return dfn < rhs.dfn;
    } else {
      return time < rhs.time;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin >> D >> P;
  map<string,int> last;
  vector<Node> all;
  for (int i = 1; i <= D; i++) {
    int T, S, today = i;
    cin >> T >> S;
    vector<Node> vec;
    for (int i = 1; i <= T; i++) {
      string name, id, time;
      int body;
      cin >> name >> id >> body >> time;
      assert(checkTime(time) && (body == 0 || body == 1));
      if (checkID(id)) {
        all.push_back({ name, id, time, body, i });
        if (!last.count(id) || last[id] <= today) {
          vec.push_back({ name, id, time, body, i });
        }
      }
    }
    sort(vec.begin(), vec.end());
    for (auto& u: vec) {
      cout << u.name << ' ' << u.id << '\n';
      last[u.id] = today + P + 1;
      S--;
      if (S == 0) break;
    }
  }
  set<string> vis;
  vector<Node> ans;
  // reverse(all.begin(), all.end());
  for (auto& u: all) {
    if (u.body == 1) {
      ans.push_back(u);
      // vis.insert(u.id);
    }
  }
  // reverse(ans.begin(), ans.end());
  for (auto& u: ans) {
    cout << u.name << " " << u.id << endl;
  }
  // cout << "?" << endl;
  // for (auto& u: all) {
  //   if (u.body == 1) {
  //     vis.insert(u.id);
  //   }
  // }
  // for (auto& u: all) {
  //   if (vis.count(u.id)) {
  //     cout << u.name << ' ' << u.id << '\n';
  //     // out.insert(u.id);
  //     vis.erase(u.id);
  //   }
  // }
  return 0;
}