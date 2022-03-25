#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std ;

typedef long long LL ;

#define clr( a , x ) memset ( a , x , sizeof a )
#define ls ( o << 1 )
#define rs ( o << 1 | 1 )
#define lson ls , l , m
#define rson rs , m + 1 , r
#define root 1 , 1 , n
#define rt o , l , r
#define mid ( ( l + r ) >> 1 )

const int MAXN = 100005 ;
const int mod = 998244353 ;

struct Node {
    int g , idx , L , R ;
    Node () {}
    Node ( int g , int idx , int L , int R ) : g ( g ) , idx ( idx ) , L ( L ) , R ( R ) {}
    bool operator < ( const Node& a ) const {
        return g != a.g ? g < a.g : idx < a.idx ;
    }
} ;

int a[MAXN] ;
vector < pair < int , int > > G[2] ;
Node node[MAXN * 25] ;
int cnt ;
int vis[MAXN << 2] , Time ;
int maxv[MAXN << 2] ;
int sum[MAXN << 2] ;
int add[MAXN << 2] ;
int query_max , query_sum ;
int ans_max , ans_sum ;
int n ;

int gcd ( int a , int b ) {
    return b ? gcd ( b , a % b ) : a ;
}

void check ( int o ) {
    if ( vis[o] < Time ) {
        vis[o] = Time ;
        maxv[o] = sum[o] = add[o] = 0 ;
    }
}

void upd ( int Max , int Add , int o , int len ) {
    check ( o ) ;
    if ( Max > maxv[o] ) {
        maxv[o] = Max ;
        add[o] = Add ;
        sum[o] = ( LL ) len * Add % mod ;
    } else if ( Max == maxv[o] ) {
        add[o] = ( add[o] + Add ) % mod ;
        sum[o] = ( sum[o] + ( LL ) len * Add ) % mod ;
    }
}

void pushdown ( int o , int l , int r ) {
    int m = mid ;
    if ( add[o] ) {
        upd ( maxv[o] , add[o] , ls , m - l + 1 ) ;
        upd ( maxv[o] , add[o] , rs , r - m ) ;
        add[o] = 0 ;
    }
}

void pushup ( int o ) {
    check ( ls ) ;
    check ( rs ) ;
    if ( maxv[ls] == maxv[rs] ) {
        sum[o] = ( sum[ls] + sum[rs] ) % mod ;
        maxv[o] = maxv[ls] ;
    } else if ( maxv[ls] > maxv[rs] ) {
        maxv[o] = maxv[ls] ;
        sum[o] = sum[ls] ;
    } else {
        maxv[o] = maxv[rs] ;
        sum[o] = sum[rs] ;
    }
}

void update ( int L , int R , int x , int v , int o , int l , int r ) {
    check ( o ) ;
    if ( L <= l && r <= R ) {
        upd ( x , v , o , r - l + 1 ) ;
        return ;
    }
    int m = mid ;
    pushdown ( rt ) ;
    if ( L <= m ) update ( L , R , x , v , lson ) ;
    if ( m <  R ) update ( L , R , x , v , rson ) ;
    pushup ( o ) ;
}

void query ( int L , int R , int o , int l , int r ) {
    if ( R < L ) return ;
    check ( o ) ;
    if ( L <= l && r <= R ) {
        if ( query_max < maxv[o] ) {
            query_max = maxv[o] ;
            query_sum = sum[o] ;
        } else if ( query_max == maxv[o] ) query_sum = ( query_sum + sum[o] ) % mod ;
        return ;
    }
    int m = mid ;
    pushdown ( rt ) ;
    if ( L <= m ) query ( L , R , lson ) ;
    if ( m <  R ) query ( L , R , rson ) ;
}

int g[18][MAXN];
int qgcd(int l, int r) {
  int k = __lg(r - l + 1);
  return __gcd(g[k][l], g[k][r - (1 << k) + 1]);
}

void solve () {
    cnt = 0 ;
    for ( int i = 1 ; i <= n ; ++ i ) {
        scanf ( "%d" , &a[i] ) ;
        g[0][i] = a[i];
    }
    for (int j = 1; j < 18; j++) {
      for (int i = 1; i + (1 << j) <= n + 1; i++) {
        g[j][i] = __gcd(g[j - 1][i], g[j - 1][i + (1 << (j - 1))]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) {
        int l = j, r = n, ans = j, g = qgcd(i, j);
        while (l <= r) {
          int m = (l + r) / 2;
          if (qgcd(i, m) == g) {
            ans = m; l = m + 1;
          } else {
            r = m - 1;
          }
        }
        node[cnt++] = (Node){ g, i, j, ans };
        j = ans;
      }
    }
    // G[cur].clear () ;
    // G[cur].push_back ( make_pair ( a[n] , n ) ) ;
    // node[cnt ++] = Node ( a[n] , n , n , n ) ;
    // for ( int i = n - 1 ; i >= 1 ; -- i ) {
    //     cur ^= 1 ;
    //     G[cur].clear () ;
    //     G[cur].push_back ( make_pair ( a[i] , i ) ) ;
    //     int pre = a[i] ;
    //     int m = 1 ;
    //     for ( int j = 0 ; j < G[cur ^ 1].size () ; ++ j ) {
    //         int v = G[cur ^ 1][j].first ;
    //         int g = gcd ( pre , v ) ;
    //         if ( g != pre ) {
    //             G[cur].push_back ( make_pair ( g , G[cur ^ 1][j].second ) ) ;
    //             node[cnt ++] = Node ( pre , i , G[cur][m - 1].second , G[cur][m].second - 1 ) ;
    //             ++ m ;
    //         }
    //         pre = g ;
    //     }
    //     node[cnt ++] = Node ( pre , i , G[cur][m - 1].second , n ) ;
    // }
    ans_sum = ans_max = 0 ;
    sort ( node , node + cnt ) ;
    for ( int i = 0 , j = 0 ; i < cnt ; i = j ) {
        while ( j < cnt && node[j].g == node[i].g ) ++ j ;
        {
            ++ Time ;
            update ( node[i].L , node[i].R , 1 , 1 , root ) ;
        //  printf ( "%d %d\n" , maxv[1] , sum[1] ) ;
            for ( int l = i + 1 ; l < j ; ++ l ) {
                int idx = node[l].idx ;
                query_max = query_sum = 0 ;
        //      printf ( "%d %d %d %d\n" , node[l].g , node[l].idx , node[l].L , node[l].R ) ;
                query ( 1 , idx - 1 , root ) ;
                if ( query_max == 0 ) query_sum = 1 ;
        //      printf ( "max = %d , sum = %d\n" , query_max , query_sum ) ;
                update ( node[l].L , node[l].R , query_max + 1 , query_sum , root ) ;
        //      printf ( "%d %d\n" , maxv[1] , sum[1] ) ;
            }
            if ( ans_max < maxv[1] ) {
                ans_max = maxv[1] ;
                ans_sum = sum[1] ;
            } else if ( ans_max == maxv[1] ) {
                ans_sum = ( ans_sum + sum[1] ) % mod ;
            }
        }
    }
    printf ( "%d %d\n" , ans_max , ans_sum ) ;
}

int main () {
    clr ( vis , 0 ) ;
    Time = 0 ;
    while ( ~scanf ( "%d" , &n ) ) solve () ;
}