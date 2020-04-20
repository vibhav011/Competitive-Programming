#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;

	while (t--) {
		string s, r;
		cin >> s;
		cin >> r;

		bool found = false;
		vector <int> diff;
		int prev;
		int sum = 1;

		for (int i = 0; i < s.size(); i++) {
			if (s[i] != r[i]) {
				if (found) {
					diff.push_back(i - prev);
					sum += i-prev;
				}
				prev = i;
				found = true;
			}
		}

		if (sum == 1) {
			if (found) cout << "1\n";
			else cout << "0\n";
			continue;
		}

		sort(diff.begin(), diff.end(), greater<int>());
		
		int cost = sum;

		for (int k = 2; k <= diff.size()+1; k++) {
			sum -= (diff[k-2]-1);
			cost = min(cost, k*sum);
		}
		cout << cost << endl;
	}
}