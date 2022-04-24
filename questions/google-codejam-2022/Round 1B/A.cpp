#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		int n; cin >> n;
		printf("Case #%d: ", cn);

		deque<int> pan;
		for (int i = 0; i < n; i++) {
			int x; cin >> x;
			pan.push_back(x);
		}
		int mx = 0;
		int ans = 0;

		for (int i = 0; i < n; i++) {
			if (pan.front() <= pan.back()) {
				ans += (pan.front() >= mx) ? 1 : 0;
				mx = max(mx, pan.front());
				pan.pop_front();
			}
			else {
				ans += (pan.back() >= mx) ? 1 : 0;
				mx = max(mx, pan.back());
				pan.pop_back();
			}
		}
		cout << ans << '\n';
	}
}