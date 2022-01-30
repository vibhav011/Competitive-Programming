#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define fio fflush(stdout)

using namespace std;

const int inf = 1LL << 60LL;

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	srand(time(0));

	int t, n, q;
	cin >> t >> n >> q;
	vector<int> a(n);
	vector<int> b(n);
	int k, ind;
	while (t--) {
		for (int i = 0; i < n; i++) b[i] = i+1;
		a[0] = 1;
		a[1] = 2;
		for (int i = 2; i < n; i++) {
			int ch = rand()%(n-i)+i;
			int lo = 0, hi = i-1;
			int mid = (lo+hi)/2;
			ind = -1;
			while (hi-lo > 1) {
				cout << a[mid] << ' ' << b[ch] << ' ' << a[mid+1] << endl; fio;
				cin >> k;
				if (k == -1) return 0;
				if (k == b[ch]) {
					ind = mid+1;
					break;
				}
				if (k == a[mid]) hi = mid;
				else lo = mid+2;
				mid = (lo+hi)/2;
			}
			if (ind == -1) {
				if (hi-lo == 1) {
					cout << a[lo] << ' ' << b[ch] << ' ' << a[hi] << endl; fio;
					cin >> k;
					if (k == -1) return 0;
					if (k == b[ch]) ind = hi;
					else if (k == a[lo]) ind = lo;
					else ind = hi+1;
				}
				else ind = hi+1;
			}
			for (int j = i; j > ind; j--) a[j] = a[j-1];
			a[ind] = b[ch];
			swap(b[i], b[ch]);
		}
		for (int x : a) cout << x << ' ';
		cout << endl; fio;
		cin >> k;
		if (k == -1) return 0;
	}
}

