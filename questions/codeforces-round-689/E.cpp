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

	ll k, l, r, t, x, y;
	cin >> k >> l >> r >> t >> x >> y;
	if (k-x < l && k+y > r) {
		cout << "No\n";
		return 0;
	}
	if (x == y) {
		cout << "Yes\n";
	}
	else if (y < x) {
		ll num = 0;
		if (k+y > r) {
			k -= x;
			num = 1;
		}
		num += (k-l)/(x-y);
		if (t > num) cout << "No\n";
		else cout << "Yes\n";
	}
	else {
		if (x+y <= r-l+1) cout << "Yes\n";
		else {
			ll num = 0;
			ll jp = r-y;
			ll times = y/x;
			ll rem = y%x;
			if (k+y > r) {
				num = (k-l)/x;
				k -= num * x;
			}
			if (k+y <= r) {
				if (rem) {
					ll ini = (jp-k)/rem;
					num += ini*times;
					k += ini*rem;
					if (k + rem - x < l) num += times;
					else num += (k+rem - (l+x))/(x-rem)*(times+1) + times;
				}
				else t = -1;
			}
			if (num >= t) cout << "Yes\n";
			else cout << "No\n";
		}
	}
	
}

