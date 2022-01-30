#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 998244353;

ll pwr(ll x, ll y, ll mod = MOD) {
	ll res = 1;
	x = x%mod;
	while (y > 0) {
		if (y&1) res = (res*x)%mod;

		y = y>>1;
		x = (x*x)%mod;
	}
	return res;
}

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}
int vis[1005][1005];
string s[1005];
int n, m;

void dfs(int u, int v) {
	if (u < 1 || u > n || v < 1 || v > m) return;
	if (s[u][v-1] == '#' || vis[u][v]) return;
	vis[u][v] = 1;
	dfs(u-1, v);
	dfs(u+1, v);
	dfs(u, v+1);
	dfs(u, v-1);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> s[i];
	int ans = 0;
	for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) vis[i][j] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!vis[i][j] && s[i][j-1] == '.') {
				ans++;
				dfs(i, j);
			}
		}
	}
	cout << ans << '\n';
	
}

