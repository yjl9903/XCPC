#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

char buf[maxn];

enum NodeType {
  List,
  Concat,
  Sorted,
  Shuffle
};

struct Info {
  NodeType type;
  vector<int> a;
};
vector<Info> va, vb;

struct Node {
  vector<int> a = {};
  NodeType type;
  Node* son[2] = { nullptr, nullptr };

  bool same = true;
  int last = -1;
  
  Node(NodeType tp = List): type(tp) {}

  void clear() {
    vector<int>().swap(a);
    clearSon();
  }
  void clearSon() {
    if (son[0]) {
      son[0]->clear();
      son[0] = nullptr;
    }
    if (son[1]) {
      son[1]->clear();
      son[1] = nullptr;
    }
  }

  void push(int x) {
    a.push_back(x);
    if (same) {
      if (last == -1 || x == last) {
        last = x;
      } else {
        same = false;
      }
    }
  }

  void join() {
    if (son[0]) {
      for (int x: son[0]->a) {
        push(x);
      }
    }
    if (son[1]) {
      for (int x: son[1]->a) {
        push(x);
      }
    }
  }

  void getSubList() {
    vector<int> a;
    function<void(Node*)> dfs = [&](Node* u) {
      if (u->type == List) {
        for (int x: u->a) {
          a.push_back(x);
        }
      } else if (u->type == Sorted || u->type == Shuffle) {
        assert(u->son[0] != nullptr);
        dfs(u->son[0]);
      } else {
        assert(u->son[0] != nullptr);
        assert(u->son[1] != nullptr);
        dfs(u->son[0]);
        dfs(u->son[1]);
      }
    };
    if (son[0] != nullptr) {
      dfs(son[0]);
    }
    if (son[1] != nullptr) {
      dfs(son[1]);
    }
    for (int x: a) push(x);
  }

  void sort() {
    getSubList();
    ::sort(a.begin(), a.end());
  }

  void merge(vector<Info>& vec) {
    if (type == Concat) {
      assert(son[0] != nullptr);
      assert(son[1] != nullptr);
      son[0]->merge(vec);
      son[1]->merge(vec);
      // if (son[0]->type == List && son[1]->type == List) {
      //   join();
      //   clearSon();
      //   type = List;
      // }
    } else if (type == Shuffle || type == Sorted) {
      sort();
      clearSon();
      if (type == Sorted || same) {
        type = List;
      }
      vec.push_back({ type, a });
    } else if (type == List) {
      vec.push_back({ type, a });
    }
  }

  void print() {
    #ifdef XLor
      cout << "{ ";
      for (int x: a) {
        cout << x << ' ';
      }
      cout << "}";
      cout << endl;
    #endif
  }
} pool[maxn];
int ncnt = 0;

Node* parse(char buf[]) {
  int i = 0, n = strlen(buf);
  function<Node*()> expr = [&]() {
    Node* cur = &pool[++ncnt];
    if (buf[i] == '[') {
      i++;
      while (i < n && buf[i] != ']') {
        int x = 0;
        while (i < n && buf[i] != ',' && buf[i] != ']') {
          x = x * 10 + (buf[i] - '0');
          i++;
        }
        cur->push(x);
        if (buf[i] == ',') i++;
      }
      i++;

      cur->type = List;
    } else if (buf[i] == 'c') {
      i += 7;
      cur->son[0] = expr();
      assert(buf[i] == ',');
      i++;
      cur->son[1] = expr();
      assert(buf[i] == ')');
      i++;

      cur->type = Concat;
      // if (cur->son[0]->type == List && cur->son[1]->type == List) {
      //   cur->join();
      //   cur->clearSon();
      //   cur->type = List;
      // } else {
      //   cur->type = Concat;
      // }

    } else if (buf[i] == 's') {
      if (buf[i + 1] == 'o') {
        i += 7;
        cur->son[0] = expr();
        assert(buf[i] == ')');
        i++;

        cur->type = Sorted;
        // cur->sort();
        // cur->clearSon();

      } else if (buf[i + 1] == 'h') {
        i += 8;
        cur->son[0] = expr();
        assert(buf[i] == ')');
        i++;

        cur->type = Shuffle;
        // cur->sort();
        // cur->clearSon();

      } else {
        assert(false);
      }
    } else {
      assert(false);
    }
    return cur;
  };

  return expr();
}

vector<PII> get(vector<Info>& va) {
  vector<PII> ans;
  int shC = 0;
  for (auto& info: va) {
    if (info.type == List) {
      for (int x: info.a) {
        ans.emplace_back(x, 0);
      }
      shC = 0;
    } else if (info.type == Shuffle) {
      shC++;
      for (int x: info.a) {
        ans.emplace_back(x, shC);
      }
    } else {
      assert(false);
    }
  }
  return ans;
}

bool diff(vector<Info>& va, vector<Info>& vb) {
  return get(va) == get(vb);
}

int main() {
  scanf("%s", buf);
  Node* a = parse(buf);
  a->merge(va);
  scanf("%s", buf);
  Node* b = parse(buf);
  b->merge(vb);
  puts(diff(va, vb) ? "equal" : "not equal");
  return 0;
}