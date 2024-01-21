#include <bits/stdc++.h>

#ifdef LOCAL
#include <debug.h>
#else
#define debug(...) 1606
#endif

using namespace std;
#define all(x) x.begin(), x.end()
#define mp make_pair
#define st first
#define nd second
#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define pc __builtin_popcount
#define bit(i) 1LL << i

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef string str;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef array<int, 3> iii;
typedef array<ll, 3> lll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ii> vii;
typedef vector<pll> vll;
typedef vector<bool> vb;
typedef vector<db> vd;

template<typename T> T gcd(T a, T b){return (b == 0? a : gcd(b, a % b));}
template<typename T> T lcm(T a, T b){return a / gcd(a, b) * b;}
template<typename T> T mod(T a, T m){if (a < 0) return a + m; if (a >= m) a -= m; if (a < m) return a; return a % m;}
template<typename T> T minimize(T &x, T const &v){if (x == -1 || x > v){x = v; return true;} return false;}
template<typename T> T maximize(T &x, T const &v){if (x == -1 || x < v){x = v; return true;} return false;}

#define file "fiel"
bool const SINGLE_TEST = 1;

struct edge{
    int a, b, w;
    edge(){}
    edge(int a, int b, int w): a(a), b(b), w(w){}
};

int const N = 2e5 + 1;
int const M = 5e5 + 1;

int n, m, q;
edge edl[M];
vector<ii> g[N];

int tin[N], low[N], ti = 0; 

bool isBrige[M];

void findBrige(int v, int p = -1){
    low[v] = n + 1;
    tin[v] = ++ti;
    for (auto u: g[v]) if (u.st != p){
        if (tin[u.st]) low[v] = min(low[v], tin[u.st]);
        else{
            findBrige(u.st, v);
            low[v] = min(low[v], low[u.st]);
            if (low[u.st] > tin[v]) isBrige[u.nd] = 1;
        }
    }
}

int ccid[N], id = 0;
void findCC(int v, int p = -1){
    if (ccid[v]) return;
    ccid[v] = id;
    for (auto u: g[v]) if (u.st != p && !isBrige[u.nd])
        findCC(u.st, v);
}

int const L = 18;
int p[N][L], h[N];
ll sum[N];

void DFS(int v){
    for (auto u: g[v]) if (u.st != p[v][0]){
        h[u.st] = h[v] + 1;
        sum[u.st] = sum[v] + u.nd;
        p[u.st][0] = v;
        for (int i = 1; i < L; i++) p[u.st][i] = p[p[u.st][i - 1]][i - 1];
        DFS(u.st);
    }
}

int LCA(int a, int b){
    if (h[a] > h[b]) swap(a, b);
    int k = h[b] - h[a];
    for (int i = 0; i < L; i++) if (k & (1 << i)) 
        b = p[b][i];
    if (a == b) return a;
    for (int i = log2(h[a]); i >= 0; i--) 
        if (p[a][i] != p[b][i])
            a = p[a][i], b = p[b][i];
    return p[a][0];
}

void solve(){	
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++){
        cin >> edl[i].a >> edl[i].b >> edl[i].w;
        g[edl[i].a].pb(mp(edl[i].b, i));
        g[edl[i].b].pb(mp(edl[i].a, i));
    }

    findBrige(1);

    for (int i = 1; i <= n; i++) if (!ccid[i]){
        id++;
        findCC(i);
    }

    for (int i = 1; i <= n; i++) g[i].clear();

    for (int i = 1; i <= m; i++) if (isBrige[i]){
        int a = edl[i].a, b = edl[i].b, w = edl[i].w;
        g[ccid[a]].pb(mp(ccid[b], w));
        g[ccid[b]].pb(mp(ccid[a], w));
    } 

    DFS(1);

    while (q--){
        int a, b; cin >> a >> b;
        a = ccid[a], b = ccid[b];
        cout << sum[a] + sum[b] - 2LL * sum[LCA(a, b)] << "\n";
    }
}  

int main(){
    ios_base::sync_with_stdio(0);//      the
    cin.tie(0);cout.tie(0);// 	    magical lines	
    // freopen(file".inp", "r", stdin);
    // freopen(file".out", "w", stdout);
    int t;
    if (SINGLE_TEST) t = 1;
    else cin >> t;
    while (t--) solve();
    return 0;
}//khong phai _HDH, _HDH ko xai template!!!
