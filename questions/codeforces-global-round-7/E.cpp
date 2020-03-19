#include <bits/stdc++.h>
using namespace std;

struct custSort {
	bool operator() (const pair<int, int> &p1, const pair<int, int> &p2) {
		return (p1.first >= p2.first);
	}
};

int main() {
	int n; cin >> n;

	set <pair<int, int>, custSort > s;

	for (int i = 0; i < n; i++) {
		int temp; cin >> temp;
		s.insert(make_pair(temp, i+1));
	}

	set<pair<int, int> >::iterator it = s.begin();

	int ans[n+1];
	ans[1] = it->first;
	int qmax = 0;
	bool bombAfter = false;
	int mm = it->second;

	for (int i = 1; i <= n; i++) {
		int q; cin >> q;
		qmax = max(qmax, q);
		mm = min(mm, it->second);
		if (i < n) {
			if (q >= it->second || (bombAfter && q >= mm)) {
				it++;
				bombAfter = (qmax >= it->second);
			}
			ans[i+1] = it->first;
		}
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
	cout << endl;
}