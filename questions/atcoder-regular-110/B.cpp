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

ll gcd(ll a, ll b) {
	if (a > b) swap(a, b);
	if (b%a == 0) return a;
	return gcd(b%a, a);
}
ll lcm(ll a, ll b) {
	return a*b/gcd(a, b);
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	string s; cin >> s;
	ll num = 10000000000LL;

	if (s == "1") {
		cout << 2*num << endl;
		return 0;
	}
	if (s == "11") {
		cout << num << endl;
		return 0;
	}

	bool firs = false, valid = true;
	int f = 0, cur = 0;

	for (int i = 0; i < n; i++) {
		if (s[i] == '0') {
			if (!firs) {
				firs = true;
				f = i;
				cur = 0;
			}
			else {
				if (cur != 2) {
					valid = false;
					break;
				}
				cur = 0;
			}
		}
		else {
			cur++;
		}
		if (cur >= 3) {
			valid = false;
			break;
		}
	}
	if (cur >= 3 || f >= 3) valid = false;
	if (!valid) {
		cout << "0\n";
		return 0;
	}
	n -= f+1;
	cout << num - n/3 - int(n%3 != 0) << endl;
	
}

