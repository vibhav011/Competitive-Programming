#include <bits/stdc++.h>
using namespace std;

bool custSort (const pair<int, int> &a, const pair<int, int> &b) {
	return (a.second >= b.second);
}

int main () {
	int n; cin >> n;
	vector<pair<int, int> > tim;
	for (int i = 0; i < n ; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		tim.push_back(make_pair(a, b+c));
	}
	sort(tim.begin(), tim.end(), custSort);
	long long int sum1 = 0;
	long long int mx = 0;
	for (int i = 0; i < n; i++) {
		sum1 += tim[i].first;
		mx = max(mx, sum1+tim[i].second);
	}
	cout << mx << endl;
}