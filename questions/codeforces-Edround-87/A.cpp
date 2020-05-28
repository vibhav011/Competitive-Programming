#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		ll a, b, c, d;
		cin >> a >> b >> c >> d;

		if (b >= a) {
			cout << b << endl;
			continue;
		}
		if (d >= c) {
			cout << "-1\n";
			continue;
		}
		ll rem = (a-b)/(c-d);
		if ((a-b)%(c-d)) rem++;
		cout << b + rem*c << endl;
	}
}