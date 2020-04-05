//incomplete

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<pair<int, int> > v;
	for (int i = 1; i <= m; i++) {
		int l; cin >> l;
		v.push_back(make_pair(l, i));
	}
	sort(v.begin(), v.end());
	ll prefSum[m+1];
	fill(prefSum, prefSum+n+1, 0);
	for (int i = 1; i <= m; i++) {
		prefSum[i] = prefSum[i-1] + v[i].first;
	}

	ans[m+1];
	bool notPossible = false;
	int i = m;
	int n2 = n;
	while (i > 0) {
		if (prefSum[i] < n2) {
			notPossible = true;
			break;
		}
		ans[v[i].second] = n-v[i].first+1;
		n2 -= v[i].first;

	}
	if (notPossible) cout << "-1\n";
	else {
		for (int i = 1; i <= m; i++) cout << ans[i] << ' ';
		cout << endl;
	}

}