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
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;
	set<int> s;
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		s.insert(x);
	}
	cout << s.size() << endl;
}

