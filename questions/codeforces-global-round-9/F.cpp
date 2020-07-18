#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define fio fflush(stdout)

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

// int* srt(ll a[]) {
// 	int *ret = new int[3];
// 	if (a[0] < a[1]) {
// 		if (a[0] < a[2]) {
// 			ret[0] = 0;
// 			if (a[1] < a[2]) {
// 				ret[1] = 1;
// 				ret[2] = 2;
// 			}
// 			else {
// 				ret[1] = 2;
// 				ret[2] = 1;
// 			}
// 		}
// 		else {
// 			ret[0] = 2;
// 			ret[1] = 0;
// 			ret[2] = 1;
// 		}
// 	}
// 	else {					// a[0] > a[1]
// 		if (a[0] > a[2]) {
// 			ret[2] = 0;
// 			if (a[1] < a[2]) {
// 				ret[0] = 1;
// 				ret[1] = 2;
// 			}
// 			else {
// 				ret[0] = 2;
// 				ret[1] = 1;
// 			}
// 		}
// 		else {
// 			ret[0] = 1;
// 			ret[1] = 0;
// 			ret[2] = 2;
// 		}
// 	}
// 	return ret;
// }

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	ll a[4], y;
	cin >> a[1] >> a[2] >> a[3];
	int x;

	cout << "First\n"; fio;
	y = max(a[1], max(a[2], a[3])) - min(a[1], min(a[2], a[3]));
	cout << y << endl; fio;
	cin >> x;
	a[x] += y;
	y = 3*max(a[1], max(a[2], a[3])) - a[1] - a[2] - a[3];
	cout << y << endl; fio;
	cin >> x;
	a[x] += y;
	y = (max(a[1], max(a[2], a[3])) - min(a[1], min(a[2], a[3])))/2;
	cout << y << endl; fio;
	cin >> x;

}

