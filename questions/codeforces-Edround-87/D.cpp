#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

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
	int n, q;
	cin >> n >> q;
	int freq[n+1];
	fill(freq, freq+n+1, 0);
	for (int i = 0; i < n; i++) {
		int temp; scanf("%d", &temp);
		freq[temp]++;
	}
	int qry[q];
	int cur = n;
	for (int i = 0; i < q; i++) {
		scanf("%d", &qry[i]);
		if (qry[i] > 0) cur++;
		else cur--;
	}
	if (cur == 0) {
		cout << "0\n";
		return 0;
	}

	BIT tree(freq, n+1);

	for (int i = 0; i < q; i++) {
		int k = qry[i];
		if (k > 0) {
			tree.update(k+1, 1);
			freq[k]++;
		}
		else {
			k = -k;
			int a = 1, b = n, c = (a+b)/2;
			int gs1 = tree.getSum(c), gs2 = gs1 - freq[c];
			while (!(gs1 >= k && gs2 < k)) {
				if (gs1 < k) {
					if (b-a == 1 && c == a) a = b;
					else a = c;
				}
				else b = c;
				c = (a+b)/2;
				gs1 = tree.getSum(c);
				gs2 = gs1 - freq[c];
			}
			tree.update(c+1, -1);
			freq[c]--;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (freq[i] > 0) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}