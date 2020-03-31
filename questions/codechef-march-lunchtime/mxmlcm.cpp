#include <bits/stdc++.h>
#define M 10001
using namespace std;
vector<pair<int, int> > fact[M];
vector<int> primes;

int gcdRat (vector<pair<int, int> > &a, int lc[]) {
	int ans = 1;
	for (int j = 0; j < a.size(); j++) {
		ans *= pow(a[j].first, a[j].second - min(a[j].second, lc[a[j].first]));
	}
	return ans;
}

int main() {
	bool is_composite[M]; fill(is_composite, is_composite + M, false);

	for (int i = 2; i < M; i++) {
		if (!is_composite[i]) {
			primes.push_back(i);
			fact[i].push_back(make_pair(i, 1));
		}
		for (int j = 0; j < primes.size() && i*primes[j] < M; j++) {
			is_composite[i*primes[j]] = true;
			if (i % primes[j] == 0) {
				fact[i*primes[j]] = fact[i];
				break;
			}
			else {
				fact[i*primes[j]] = fact[i];
				fact[i*primes[j]].push_back(make_pair(primes[j], 1));
			}
		}
	}

	for (int i = 2; i < M; i++) {
		if (fact[i][0].first != i) {
			int i2 = i;
			for (int j = 0; j < fact[i].size(); j++) {
				int cnt = 0;
				while (i2 % fact[i][j].first == 0) {
					cnt++;
					i2 /= fact[i][j].first;
				}
				fact[i][j].second = cnt;
			}
		}
	}

	int t; cin >> t;
	while(t--) {
		int n, m; cin >> n >> m;
		int lc[m+1];
		fill(lc, lc+m+1, 0);
		for (int i = 0; i < n; i++) {
			int temp; cin >> temp;
			for (int j = 0; j < fact[temp].size(); j++) {
				lc[fact[temp][j].first] = max(lc[fact[temp][j].first], fact[temp][j].second);
			}
		}
		int mx = 1, j = 1;
		for (int i = 2; i <= m; i++) {
			int tmx = gcdRat(fact[i], lc);
			if (tmx > mx) {
				mx = tmx;
				j = i;
			}
		}
		cout << j << endl;
	}
}