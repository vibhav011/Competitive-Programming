#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> ans;
		ll sum = 0;
		ll totalsum = 0;
		int a[n];
		bool areDistinctF[n+1], areDistinctL[n+1];
		memset(areDistinctF, false, sizeof(areDistinctF));
		memset(areDistinctL, false, sizeof(areDistinctL));
		bool present[n];
		memset(present, false, sizeof(present));

		for (int i = 0; i < n; i++) {
			cin >> a[i];
			totalsum += a[i];
		}

		for (int i = 0; i < n; i++) {
			if (present[a[i]]) {
				break;
			}
			areDistinctF[i+1] = true;
			present[a[i]] = true;
		}
		memset(present, false, sizeof(present));
		for (int i = n-1; i >= 0; i--) {
			if (present[a[i]]) {
				break;
			}
			areDistinctL[n-i] = true;
			present[a[i]] = true;
		}

		for (ll i = 1; i <= n-1; i++) {
			if (!areDistinctF[i]) break;
			sum += a[i-1];
			if (sum == i*(i+1)/2 && totalsum-sum == (n-i)*(n-i+1)/2 && areDistinctL[n-i]) {
				ans.push_back(i);
			}
		}

		cout << ans.size() << endl;
		for (int i = 0; i < ans.size(); i++) {
			printf("%d %d\n", ans[i], n-ans[i]);
		}
	}
}