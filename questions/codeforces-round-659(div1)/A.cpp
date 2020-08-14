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
		int n; cin >> n;
		string a, b;
		cin >> a >> b;
		bool pos = true;
		int ar[20][20];
		// vector<int> fst(20, 20);
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) ar[i][j] = 0;
		}
		for (int i = 0; i < n; i++) {
			if (a[i] > b[i]) {
				pos = false;
				break;
			}
			if (a[i] < b[i]) {
				ar[a[i]-'a'][b[i]-'a'] = 1;
				// fst[a[i]-'a'] = min(fst[a[i]-'a'], b[i]-'a');
			}
		}
		if (!pos) {
			cout << "-1\n";
			continue;
		}
		int ans = 0;
		for (int i = 0; i < 20; i++) {
			int fst = -1;
			for (int j = 0; j < 20; j++) {
				if (ar[i][j]) {
					fst = j;
					break;
				}
			}
			if (fst == -1) continue;
			ans++;
			for (int j = fst+1; j < 20; j++) {
				if (ar[i][j]) ar[fst][j] = ar[i][j];
			}
		}
		cout << ans << endl;
	}
}

