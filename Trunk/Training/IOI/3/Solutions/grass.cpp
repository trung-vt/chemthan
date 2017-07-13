#include <bits/stdc++.h>
using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define FORall(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define sz(a) int((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
const int MOD = (int) 1e9 + 7;
const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;
const ld PI = acos((ld) -1);
const ld EPS = 1e-9;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return a > val ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}

const int maxn = 100000 + 10;
int n, m;
vi adj[maxn];
vi radj[maxn];
int vis[maxn];
vi ver;
int cnt;
int com[maxn];
int tot[maxn];
int f[maxn];
int g[maxn];

void dfs1(int u) {
	vis[u] = 1;
	FOR(i, 0, sz(adj[u])) {
		int v = adj[u][i];
		if (!vis[v]) {
			dfs1(v);
		}
	}
	ver.pb(u);
}

void dfs2(int u, int cnt) {
	vis[u] = 1, tot[com[u] = cnt]++;
	FOR(i, 0, sz(radj[u])) {
		int v = radj[u][i];
		if (!vis[v]) {
			dfs2(v, cnt);
		}
	}
}

void solve() {
	if (fopen("grass.in", "r")) {
		freopen("grass.in", "r", stdin);
		freopen("grass.out", "w", stdout);
	}
	cin >> n >> m;
	vii edge;
	FOR(i, 0, m) {
		int u, v; cin >> u >> v; u--, v--;
		adj[u].pb(v), radj[v].pb(u);
		edge.pb(mp(u, v));
	}
	FOR(i, 0, n) if (!vis[i]) dfs1(i);
	fill_n(vis, n, 0);
	FORd(i, n, 0) {
		int u = ver[i];
		if (!vis[u]) {
			dfs2(u, cnt++);
		}
	}
	FOR(i, 0, cnt) adj[i].clear(), radj[i].clear();
	FOR(i, 0, sz(edge)) {
		int u = edge[i].fi;
		int v = edge[i].se;
		u = com[u], v = com[v];
		if (u != v) {
			adj[u].pb(v), radj[v].pb(u);
		}
	}
	int z = com[0];
	f[z] = tot[z];
	FOR(i, 0, cnt) if (f[i]) {
		FOR(j, 0, sz(adj[i])) {
			int k = adj[i][j];
			chkmax(f[k], f[i] + tot[k]);
		}
	}
	g[z] = tot[z];
	FORd(i, cnt, 0) if (g[i]) {
		FOR(j, 0, sz(radj[i])) {
			int k = radj[i][j];
			chkmax(g[k], g[i] + tot[k]);
		}
	}
	int ans = f[z];
	FOR(i, 0, cnt) if (g[i]) {
		FOR(j, 0, sz(adj[i])) {
			int k = adj[i][j];
			if (f[k]) {
				chkmax(ans, g[i] + f[k] - f[z]);
			}
		}
	}
	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef _LOCAL_
	freopen("in.txt", "r", stdin); //freopen("out.txt", "w", stdout);
#endif
	solve();
#ifdef _LOCAL_
	//printf("\nTime elapsed: %dms", 1000 * clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}