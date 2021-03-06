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

int bsh(pll ar[], ll n, ll val) {		// return ind such that val >= ar[ind] and val < ar[ind+1]
	ll a = 1, b = n - 1, c = (a+b)/2;
	if (val >= ar[0].ff) return 0;
	// if (val >= ar[b]) return b;

	while (!(val >= ar[c].ff && val < ar[c-1].ff)) {
		if (val < ar[c].ff) {
			if (b-a == 1 && c == a) a = b;
			else a = c;
		}
		else {
			b=c;
		}
		c = (a+b)/2;
	}
	return c;
}

bool custSort(pll &p1, pll &p2) {
	return (p1.ff == p2.ff) ? (p1.ss > p2.ss) : (p1.ff > p2.ff);
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> freq(26);
		bool pos = true;
		for (int i = 0; i < n; i++) {
			char c; cin >> c;
			freq[c-'a']++;
		}
		for (int i = 0; i < 26; i++) {
			if (freq[i]&1) {
				pos = false;
				break;
			}
		}
		if (pos) cout << "YES\n";
		else cout << "NO\n";
	}
}

