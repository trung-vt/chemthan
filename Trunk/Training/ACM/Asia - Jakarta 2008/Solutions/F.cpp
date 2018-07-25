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

const int maxn = 30 + 10;
const int maxk = 6000 + 10;
int n;
int a[maxn];
string op[maxn];
bitset<maxk> f[maxn][maxn];

void solve() {
	while (1) {
		string express;
		getline(cin, express);
		if (express == "") break;
		stringstream ss(express);
		n = 0; ss >> a[n];
		while (ss >> op[n]) {
			n++;
			ss >> a[n];
		}
		n++;
		FOR(i, 0, n) FOR(j, 0, n) f[i][j].reset();
		f[0][0][a[0] + 3005] = 1;
		FOR(i, 1, n) FORd(j, n + 1, 0) {
			f[i][j] |= f[i][j + 1];
			if (op[i - 1] == "+") {
				if (!(j & 1)) {
					f[i][j] |= f[i - 1][j] << a[i];
					if (j) {
						f[i][j - 1] |= f[i - 1][j] >> a[i];
					}
				}
				else {
					f[i][j] |= f[i - 1][j] >> a[i];
					if (j) {
						f[i][j - 1] |= f[i - 1][j] << a[i];
					}
				}
			}
			else {
				if (!(j & 1)) {
					f[i][j] |= f[i - 1][j] >> a[i];
					if (j) {
						f[i][j - 1] |= f[i - 1][j] << a[i];
					}
					f[i][j + 1] |= f[i - 1][j] >> a[i];
				}
				else {
					f[i][j] |= f[i - 1][j] << a[i];
					if (j) {
						f[i][j - 1] |= f[i - 1][j] >> a[i];
					}
					f[i][j + 1] |= f[i - 1][j] << a[i];
				}
			}
		}
		bitset<maxk> res;
		FOR(i, 0, n + 1) res |= f[n - 1][i];
		cout << res.count() << "\n";
	}
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
