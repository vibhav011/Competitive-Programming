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

	int n; cin >> n;

	set<int> qrs[14], ind[n+1];
	int cnt = 1;
	ll x[14]; memset(x, 0, sizeof(x));

	for (int i = 31; i < (1 << 13) && cnt <= n; i++) {
		bitset<16> ch(i);
		if (ch.count() != 5) continue;

		for (int pow = 0; pow < 13; pow++) { 
			if (i&(1 << pow)) {
				qrs[pow+1].insert(cnt);
				ind[cnt].insert(pow+1);
			}
		}
		cnt++;
	}
	for (int i = 1; i < 14; i++) {
		if (qrs[i].size()) {
			cout << "? " << qrs[i].size();
			for (int z : qrs[i]) cout << ' ' << z;
			cout << endl;
			fflush(stdout);
			cin >> x[i];
		}
		else break;
	}
	cout << '!';
	for (int i = 1; i <= n; i++) {
		ll ans = 0;
		for (int j = 1; j < 14; j++) {
			if (ind[i].find(j) == ind[i].end()) ans = ans|x[j];
		}
		cout << ' ' << ans;
	}
	cout << endl;
	return 0;
}

