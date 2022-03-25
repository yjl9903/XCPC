// O(n + k^2 log k)
// Hashes
#include <bits/stdc++.h>
using namespace std;

constexpr int kInf = 1000 * 1000 * 1000 + 7;

int AddMod(int x, int y, int mod) {
  return x + y >= mod ? x + y - mod : x + y;
}

int SubMod(int x, int y, int mod) {
  return x - y < 0 ? x - y + mod : x - y;
}

constexpr int kMod1 = 1000 * 1000 * 1000 + 7;
constexpr int kMod2 = 1000 * 1000 * 1000 + 9;
constexpr int kP1 = 37;
constexpr int kP2 = 13331;

const int N = 2 * 1000 * 1000 + 7;
int p1[N], p2[N];

void Precompute() {
  p1[0] = p2[0] = 1;
  for (int i = 1; i < N; ++i) {
    p1[i] = (1LL * p1[i - 1] * kP1) % kMod1;
    p2[i] = (1LL * p2[i - 1] * kP2) % kMod2;
  }
}

struct hash_t {
  int val1{}, val2{};

  friend hash_t operator *(const hash_t& a, int index) {
    return {static_cast<int>(1LL * a.val1 * p1[index] % kMod1), static_cast<int>(1LL * a.val2 * p2[index] % kMod2)};
  }

  friend hash_t operator -(const hash_t& a, const hash_t& b) {
    return {SubMod(a.val1, b.val1, kMod1), SubMod(a.val2, b.val2, kMod2)};
  }

  friend bool operator ==(const hash_t& a, const hash_t& b) {
    return a.val1 == b.val1 && a.val2 == b.val2;
  }
};

struct LcpStruct {
  LcpStruct(const string& first, const string& second)
    : first_hash_(first.size() + 1),
      second_hash_(second.size() + 1) {
      for (size_t i = 0; i < first.size(); ++i) {
        first_hash_[i + 1] = {
          static_cast<int>((1LL * first_hash_[i].val1 * kP1 + first[i]) % kMod1),
          static_cast<int>((1LL * first_hash_[i].val2 * kP2 + first[i]) % kMod2),
        };
      }

      for (size_t i = 0; i < second.size(); ++i) {
        second_hash_[i + 1] = {
          static_cast<int>((1LL * second_hash_[i].val1 * kP1 + second[i]) % kMod1),
          static_cast<int>((1LL * second_hash_[i].val2 * kP2 + second[i]) % kMod2),
        };
      }
    }

  int Lcp(int i, int j) {
    int l = -1, r = min(static_cast<int>(first_hash_.size()) - i, static_cast<int>(second_hash_.size()) - j) + 1;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (first_hash_[i + m] - first_hash_[i] * m == second_hash_[j + m] - second_hash_[j] * m)
        l = m;
      else
        r = m; 
    }

    return l;
  }

  vector<hash_t> first_hash_, second_hash_;
};

struct DpMatrix {
  DpMatrix(int n, int m, int k)
    : n_(n),
      m_(m),
      k_(k),
      diagonals_(2 * k_ + 1) {}

  int Value(int x, int y) const {
    if (x < 0 || x > n_ || y < 0 || y > m_)
      return kInf;

    int diagonal = x - y + k_;
    
    if (diagonal < 0 || diagonal >= static_cast<int>(diagonals_.size()))
      return kInf;

    pair<pair<int, int>, int> search_item = {{x, y}, 0};
    auto iter = lower_bound(diagonals_[diagonal].begin(), diagonals_[diagonal].end(), search_item);
    if (iter == diagonals_[diagonal].end())
      return kInf;

    return iter->second;
  }

  pair<int, int> Next(int x, int y) const {
    int diagonal = x - y + k_;
    pair<pair<int, int>, int> search_item = {{x, y}, 0};
    auto iter = lower_bound(diagonals_[diagonal].begin(), diagonals_[diagonal].end(), search_item);
    return iter->first;
  }

  void Extend(int x, int y, int value) {
    int diagonal = x - y + k_;
    diagonals_[diagonal].emplace_back(make_pair(x, y), value);
  }

  int N() const {
    return n_;
  }

  int M() const {
    return m_;
  }

  int K() const {
    return k_;
  }

  int n_;
  int m_;
  int k_;
  vector<vector<pair<pair<int, int>, int>>> diagonals_;
};

struct Operation {
  string ToString() const {
    string result = type + " " + to_string(position);
    if (type != "DELETE") {
      result += ' ';
      result += symbol;
    }

    return result;
  }

  string type;
  int position;
  char symbol;
};

DpMatrix ComputeDpMatrix(const string& a, const string& b, int k) {
  const int n = static_cast<int>(a.size());
  const int m = static_cast<int>(b.size());

  DpMatrix matrix(n, m, k);

  set<pair<int, pair<int, int>>> s = {{0, {0, 0}}};

  for (int i = 1; i <= min(n, k); ++i) {
    s.insert({i, {i, 0}});
  }

  for (int i = 1; i <= min(m, k); ++i) {
    s.insert({i, {0, i}});
  }

  LcpStruct lcp_struct(a, b);
  int cnt = 0;

  while (!s.empty()) {
    auto item = *s.begin();
    s.erase(s.begin());

    int value = item.first;
    int x = item.second.first, y = item.second.second;
    int c = 0;

    while (true) {
      ++c;
      int lcp = x < n && y < m ? lcp_struct.Lcp(x, y) : 0;
      x += lcp;
      y += lcp;

      if (x == n || y == m) {
        break;
      }

      int right_value = matrix.Value(x, y + 1);
      int down_value = matrix.Value(x + 1, y);
      if (value < min(right_value, down_value) + 1) {
        break;
      } else {
        int max_diff = 1;
        if (right_value == value - 1) {
          auto nxt = matrix.Next(x, y + 1);
          max_diff = max(max_diff, nxt.second - y);
        }

        if (down_value == value - 1) {
          auto nxt = matrix.Next(x + 1, y);
          max_diff = max(max_diff, nxt.first - x);
        }

        x += max_diff;
        y += max_diff;
      }
    }

    matrix.Extend(x, y, value);

    ++x; ++y; ++value;
    if (x <= n && y <= m && value <= k) {
      // cerr << x - y << ' ' << value << ' ' << s.size() << endl;
      s.insert({value, {x, y}});
    }
  }

  // cerr << "finished building" << endl;

  return matrix;
}

vector<Operation> RestoreAnswer(const string& a, const string& b, const DpMatrix& matrix) {
  const int n = matrix.N();
  const int m = matrix.M();

  vector<Operation> result;

  int i = n, j = m;
  while (i > 0 || j > 0) {
    auto cur_value = matrix.Value(i, j);
    // cout << i << ' ' << j << ' ' << cur_value << endl;
    if (i == 0 || matrix.Value(i, j) == matrix.Value(i, j - 1) + 1) {
      result.push_back({"INSERT", j, b[j - 1]});
      --j;
      continue;
    }

    if (j == 0 || matrix.Value(i, j) == matrix.Value(i - 1, j) + 1) {
      result.push_back({"DELETE", j + 1});
      --i;
      continue;
    }

    if (a[i - 1] != b[j - 1]) {
      result.push_back({"REPLACE", j, b[j - 1]});
    }

    --i;
    --j;
  }

  reverse(result.begin(), result.end());
  return result;
}

void Solve() {
  int n, m, k;
  cin >> n >> m >> k;

  k = min(k, max(n, m));

  string a, b;
  cin >> a >> b;

  auto matrix = ComputeDpMatrix(a, b, k);
  int answer = matrix.Value(a.size(), b.size());
  if (answer == kInf) {
    cout << "NO\n";
    return;
  }

  auto result = RestoreAnswer(a, b, matrix);

  cout << "YES\n";
  cout << answer << "\n";
  for (const auto& operation: result) {
    cout << operation.ToString() << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Precompute();

  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    Solve();
  }
}