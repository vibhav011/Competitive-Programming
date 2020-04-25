#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const ll p = 998244353;

// class BIT {
// 	int *bit;
// 	int N;

// 	void update(int x, int val) {
// 		int ind = x;
// 		while (ind <= N) {
// 			bit[ind] += val;
// 			ind += (ind & (-ind));
// 		}
// 	}

// public:
// 	BIT(int ar[], int n) {
// 		bit = new int[n+1];
// 		N = n+1;
// 		for (int i = 1; i < N; i++) bit[i] = 0;
// 		for (int i = 1; i < N; i++) update(i, ar[i-1]);
// 	}

// 	int getSum(int x) {
// 		int ind = x+1;
// 		int sum = 0;
// 		while (ind > 0) {
// 			sum += bit[ind];
// 			ind = (ind & (ind-1));
// 		}
// 		return sum;
// 	}

// 	int getValue(int x) {
// 		return getSum(x) - getSum(x-1);
// 	}

// 	void changeElem(int x, int val) {
// 		update(x+1, val-getValue(x));
// 	}
// };

int main () {
	int t; cin >> t;

	while (t--) {
		int n, m, q;
		cin >> n >> m >> q;

		int a[n];

		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}

		while (q--) {
			int x, y;
			cin >> x >> y;
			a[x-1] = y;
			ll sum = 0;
			ll tempsum = 0;

			for (int i = 0; i < n-m+1; i++) {
				tempsum = (tempsum + a[i]) % p;
			}

			sum = (tempsum*tempsum) % p;

			for (int i = 1; i < m; i++) {
				tempsum = (tempsum - a[i-1] + a[i+n-m] + p) % p;
				sum = (sum + ((tempsum * tempsum)%p)) % p;
			}
			cout << sum << endl;
		}
	}
}