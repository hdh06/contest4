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

int const N = 1e5 + 1;
int const D = 400;

struct query{
    int l, r, id;
    query(){}
    query(int l, int r, int id): l(l), r(r), id(id) {}
};

int n, q;
int c[N], v[N];

int ccnt[N];
ll ans[N];

query qrys[N];

void solve(){	
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> v[i];

    for (int i = 1; i <= q; i++){
        cin >> qrys[i].l >> qrys[i].r;
        qrys[i].id = i;
    }
    
    sort(qrys + 1, qrys + q + 1, [](query a, query b){
        if (a.l / D == b.l / D) return a.r < b.r;
        return a.l / D < b.l / D;
    });

    ll sum = 0;
    int cnt = 0;
    for (int i = 1, r = 0, l = 1; i <= q; i++){
        int L = qrys[i].l, R = qrys[i].r;
        while (L < l){
            l--;
            ccnt[c[l]]++;
            if (ccnt[c[l]] == 1) sum += v[c[l]], cnt++;
        }
        while (r < R){
            r++;
            ccnt[c[r]]++;
            if (ccnt[c[r]] == 1) sum += v[c[r]], cnt++;
        }
        while (l < L){
            ccnt[c[l]]--;
            if (ccnt[c[l]] == 0) sum -= v[c[l]], cnt--;
            l++;
        }
        while (R < r){
            ccnt[c[r]]--;
            if (ccnt[c[r]] == 0) sum -= v[c[r]], cnt--;
            r--;
        }

        ans[qrys[i].id] = sum * cnt;
    }

    for (int i = 1; i <= q; i++)
        cout << ans[i] << "\n"; 
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
