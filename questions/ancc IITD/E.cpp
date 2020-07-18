// incorrect

#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 998244353;

const int N = 1e6+5;
int n;
ll t[2 * N];

void build() {
  for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] & t[i<<1|1];
}

ll query(int l, int r) {
  ll res = ((ll)1<<32) - 1;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res &= t[l++];
    if (r&1) res &= t[--r];
  }
  return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;
	ll u, v;
	cin >> u >> v;
	ll a[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		t[i+n] = a[i];
	}

	if (n==1) {
		if (u == v && u == a[0]) cout << "1\n";
		else cout << "-1\n";
		return 0;
	}

	int xp[n+1]; xp[0] = 0;
	for (int i = 1; i <= n; i++) {
		xp[i] = xp[i-1]^a[i-1];
	}
	build();
	// int mx = n;
	int st = 0, en = 1;
	ll cur = a[0];
	int ans = n+5;
	while (!(en == n && cur > v)) {
		if (ans == 1) break;
		// cout << st << ' ' << en << endl;
		if (cur > v) {
			cur &= a[en];
			en++;
		}
		else if (cur < v) {
			st++;
			cur = query(st, en);
		}
		else {
			if ((xp[en]^xp[st]) == u && en != st) ans = min(ans, en-st);
			if (en == n) st++;
			else en++;
			cur = query(st, en);
		}
	}
	if (ans == n+5) cout << "-1\n";
	else cout << ans << endl;

}

