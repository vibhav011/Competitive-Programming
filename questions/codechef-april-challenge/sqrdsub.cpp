#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		ll n; cin >> n;

		vector<ll> evens(1, 0);
		vector<int> num(1, 0);

		for (int i = 1; i <= n; i++) {
			int a; cin >> a;
			if (!(a%2)) {
				evens.push_back(i);
				num.push_back(a);
			}
		}
		evens.push_back(n+1);
		num.push_back(n+1);
		ll ans = 0;
		for (int i = 1; i < evens.size()-1; i++) {
			if (num[i]%4 == 0) continue;
			ans += (evens[i+1]-evens[i])*(evens[i]-evens[i-1]);
		}
		cout << n*(n+1)/2-ans << endl;
	}
}