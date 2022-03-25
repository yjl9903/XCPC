#include <bits/stdc++.h>
#define FastIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define inf 0x3f3f3f3f
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repp(i, a, b) for (int i = a; i <= b; i++)
#define rep1(i, a, b) for (int i = a; i >= b; i--)
#define mem(gv) memset(gv, 0, sizeof(gv))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define QAQ 0
#ifdef miaojie
#define dbg(args...)        \
  do {                      \
    cout << #args << " : "; \
    err(args);              \
  } while (0)
void err() { std::cout << std::endl; }
template <typename T, typename... Args>
void err(T a, Args... args) {
  std::cout << a << ' ';
  err(args...);
}
#else
#define dbg(...)
#endif

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pLL;

struct Palindromic_Tree {
  static const int maxn = 1e5 + 20;
  static const int Letter = 26;

  deque<int> text;
  int len[maxn];  /// len[i]��ʾ�ڵ�i��ʾ�Ļ��Ĵ��ĳ���
  int cnt[maxn];  ///�� i �ڵ��ʾ�Ļ��Ĵ����ֵĴ�����ע�������� getCnt ������ɼ���
  int num[maxn];  ///��ʾ�Խڵ� i ����Ļ��Ĵ��˵�Ϊ�˵�Ĳ�ͬ���Ĵ�����
  int nxt[maxn][Letter];  /// nxt��ָ̬����ֵ������ƣ�ָ��Ĵ�Ϊ��ǰ�����˼���ͬһ���ַ�����
  int fail[maxn];         ///ʧ��ָ��
  int odd, even;          ///��żԭʼ�ڵ�
  int pre, suf;
  int totNode;  ///�Զ������нڵ�ĸ���
  ll totNum;    ///�������л��Ĵ�����

  int newNode(int _len) {
    int ret = totNode++;
    len[ret] = _len;
    cnt[ret] = num[ret] = 0;
    fail[ret] = 0;
    memset(nxt[ret], 0, sizeof(nxt[ret]));
    return ret;
  }

  inline void init() {
    text.clear();
    totNode = 0;
    totNum = 0;
    even = newNode(0);
    odd = newNode(-1);
    fail[even] = fail[odd] = odd;
    pre = suf = even;
  }

  int encode(char c) { return c - 'a'; }

  template <typename FunT>
  int getFail(int ch, int cur, FunT getNext) {
    for (int i = getNext(len[cur]);
         i < 0 || i >= (int)text.size() || text[i] != ch;
         cur = fail[cur], i = getNext(len[cur]))
      ;
    return cur;
  }

  template <typename FunT>
  int Insert(int ch, int last, FunT getNext) {
    last = getFail(ch, last, getNext);
    if (!nxt[last][ch]) {
      int cur = newNode(len[last] + 2);
      fail[cur] = nxt[getFail(ch, fail[last], getNext)][ch];
      nxt[last][ch] = cur;
      num[cur] = num[fail[cur]] + 1;
    }

    last = nxt[last][ch];
    totNum += (ll)num[last];
    cnt[last]++;
    return last;
  }

  int push_front(char c) {
    text.push_front(encode(c));
    pre = Insert(encode(c), pre, [](int i) -> int { return i + 1; });
    if (len[pre] == (int)text.size()) suf = pre;
    return totNode;
  }

  int push_back(char c) {
    text.push_back(encode(c));
    suf = Insert(encode(c), suf,
                 [this](int i) -> int { return this->text.size() - i - 2; });
    if (len[suf] == (int)text.size()) pre = suf;
    return totNode;
  }

  int push_front(char *s) {
    int ret = 0;
    for (int i = 0; s[i]; i++) ret = push_front(s[i]);
    return ret;
  }

  int push_back(char *s) {
    int ret = 0;
    for (int i = 0; s[i]; i++) ret = push_back(s[i]);
    return ret;
  }

  inline void getCnt() {
    for (int i = totNode - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
  }

  int dfs(int u) {
    int sum = 1;
    for (int i = 0; i < 26; i++) {
      if (nxt[u][i] > 1) {
        sum += dfs(nxt[u][i]);
      }
    }
    return sum;
  }

} PAM1, PAM2;

const int maxn = 4e5 + 10;

char str[maxn];
ll L[maxn], R[maxn];

bool vis1[30], vis2[30];
int cha;

int main() {
  int len;
  scanf("%d", &len);
  PAM1.init();
  PAM2.init();
  scanf("%s", str);
  for (int i = 0; i < len; i++) {
    PAM1.push_back(str[i]);
    L[i] = PAM1.totNode - 2;
  }
  for (int i = 0; i < len; i++) {
    vis1[str[i] - 'a'] = 1;
  }
  for (int i = 1; i < len; i++) {
    if (str[i] == str[i - 1]) {
      vis2[str[i] - 'a'] = 1;
    }
  }

  for (int i = 0; i < 26; i++) {
    if (vis1[i]) cha++;
    // if (vis2[i]) cha++;
  }
  int ans = PAM1.dfs(PAM1.odd) - 1 - cha;
  printf("%d\n", ans);
  // printf("%lld\n", L[len - 1] - cha);
  return 0;
}