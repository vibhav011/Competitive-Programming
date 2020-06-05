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
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;

	while (t--) {
		int n;
		cin >> n;
		string a, b;
		cin >> a >> b;
		string ans;
		int cnt = 0;

		if (a == b) {
			cout << "0\n";
			continue;
		}

		bool pos = true;
		vector<int> ind[26];
		for (int i = 0; i < n; i++) {
			ind[b[i] - 'a'].pb(i);
		}
		for (int i = 25; i >= 0 && pos; i--) {
			if (ind[i].size() == 0) continue;
			bool found = false;
			vector<int> ii;
			for (int j = 0; j < ind[i].size(); j++) {
				if (a[ind[i][j]] - 'a' < i) {
					pos = false;
					break;
				}
				else if (a[ind[i][j]] - 'a' > i) {
					found = true;
					ii.pb(ind[i][j]);
				}
			}
			if (found) {
				int lol;
				bool f2 = false;
				for (int k = 0; k < n; k++) {
					if (a[k] == i + 'a') {
						f2 = true;
						lol = k;
						break;
					}
				}
				if (f2) {
					cnt++;
					ans += to_string(ii.size() + 1) + " " + to_string(lol) + " ";
					for (int h = 0; h < ii.size(); h++) {
						ans += to_string(ii[h]) + " ";
						a[ii[h]] = i + 'a';
					}
					ans += "\n";
				}
				else pos = false;
			}
		}
		if (pos) cout << cnt << "\n" << ans;
		else cout << "-1\n";
	}
	
}

