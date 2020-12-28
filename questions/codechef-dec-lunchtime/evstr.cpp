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

ll pwr(ll x, ll y) {
	ll res = 1;
	x = x%MOD;
	while (y > 0) {
		if (y&1) res = (res*x)%MOD;

		y = y>>1;
		x = (x*x)%MOD;
	}
	return res;
}

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}

class BIT {
	int *bit;
	int N;

public:
	void update(int x, int val) {
		int ind = x;
		while (ind <= N) {
			bit[ind] += val;
			ind += (ind & (-ind));
		}
	}

	BIT(int ar[], int n) {
		bit = new int[n+1];
		N = n+1;
		for (int i = 1; i < N; i++) bit[i] = 0;
		for (int i = 1; i < N; i++) update(i, ar[i-1]);
	}

	int getSum(int x) {
		if (x < 0) return 0;

		int ind = x+1;
		int sum = 0;
		while (ind > 0) {
			sum += bit[ind];
			ind = (ind & (ind-1));
		}
		return sum;
	}

	int getValue(int x) {
		return getSum(x) - getSum(x-1);
	}

	void changeElem(int x, int val) {
		update(x+1, val-getValue(x));
	}
};

int bsh(int val, int ar[], int n) {		// return ind such that val >= ar[ind] and val < ar[ind+1]
	int a = 0, b = n - 1, c = (a+b)/2;
	if (val < ar[0]) return -1;
	if (val >= ar[b]) return b;

	while (!(val >= ar[c] && val < ar[c+1])) {
		if (val < ar[c]) b = c;
		else {
			if (b-a == 1 && c == a) a = b;
			else a = c;
		}
		c = (a+b)/2;
	}
	return c;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		int a[n];
		for (int i = 0; i < n; i++) cin >> a[i];
		if (n == 1) {
			cout << "1\n";
			continue;
		}
		int cur = a[0];
		int cnt = 1;
		int ans = 0;
		vector<pii> freq;
		for (int i = 1; i < n; i++) {
			if (cur == a[i]) cnt++;
			else {
				freq.pb(mp(cnt, cur));
				cnt = 1;
				cur = a[i]; 
			}
		}
		freq.pb(mp(cnt, a[n-1]));
		int m = freq.size();
		freq.pb(mp(0, 0)); freq.pb(mp(0, 0));

		if (m == 1) {
			if (freq[0].ff&1) cout << "1\n";
			else cout << "0\n";
			continue;
		}
		if (m == 2) {
			cout << (freq[0].ff&1) + (freq[1].ff&1) << endl;
			continue;
		}
		// for (int i = 0; i < m; i++) cout << freq[i].ff << ' ';
		// cout << endl;
		int last = -1;
		int ev = 0;
		for (int i = 0; i < m; i++) {
			if (freq[i].ff&1) {
				ans++;
				// if (i < m-2 && freq[i+1].ff == 1 && (freq[i+2].ff&1) && freq[i+2].ss == freq[i].ss) {
				// 	// cout << "Hi: " << i << endl;
				// 	i += 2;
				// }
				if (ev) {
					ev = 0;
					last = freq[i].ss;
					continue;
				}
				if (last == -1) {
					last = freq[i].ss;
					continue;
				}
				if (last == freq[i].ss) {
					ans -= 2;
					last = -1;
				}
			}
			else ev = 1;
		}
		cout << ans << endl;
	}
	
}

