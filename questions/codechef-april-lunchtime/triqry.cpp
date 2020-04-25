#include <bits/stdc++.h>
#define ll long long int
using namespace std;
int N2 = 2000005;

struct Query {
	int l, r, ind;
};

bool custSort (Query &a, Query &b) {
	return (a.l < b.l); 
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

int main () {
	int t; cin >> t;

	while (t--) {
		int n, q;
		cin >> n >> q;
		vector <pair<int, int> > pts;

		int ar[N2];
		fill(ar, ar+N2, 0);
		BIT lol(ar, N2);

		for (int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			pts.push_back(make_pair(x-y, x+y));
			lol.update(x+y+1, 1);
		}
		sort(pts.begin(), pts.end());

		Query qrs[q];
		int ans[q];

		for (int i = 0; i < q; i++) {
			cin >> qrs[i].l >> qrs[i].r;
			qrs[i].ind = i;
		}

		sort (qrs, qrs+q, custSort);

		int ii = 0;

		for (int i = 0; i < q; i++) {
			while (ii < n && pts[ii].first < qrs[i].l) {
				lol.update(pts[ii].second+1, -1);
				ii++;
			}
			
			ans[qrs[i].ind] = lol.getSum(qrs[i].r) - lol.getSum(qrs[i].l-1);
		}

		for (int i = 0; i < q; i++) {
			cout << ans[i] << ' ';
		}
		cout << endl;
	}
}