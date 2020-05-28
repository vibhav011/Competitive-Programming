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
	cout.precision(15);
	double pi = 3.141592653589;
	while (t--) {
		int n; cin >> n;
		cout << cos(pi/2/n)/sin(pi/2/n) << endl;
	}
}