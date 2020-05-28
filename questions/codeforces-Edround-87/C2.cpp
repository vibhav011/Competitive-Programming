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
		double d = 1/sin(pi/2/n);
		int k = n/4;
		double theta = min(abs(180.0/n * k - 45), abs(180.0/n * (k+1) - 45));
		cout << d*cos(theta*pi/180) << endl;
		//cout << max(1 + cos(pi/2/n)/sin(pi/2/n), 1/sin(pi/2/n))/sqrt(2) << endl;
	}
}