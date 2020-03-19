#include <bits/stdc++.h>
using namespace std;
int M = 998244353;

struct custSort {
	bool operator() (const pair<int, int> &p1, const pair<int, int> &p2) {
		return (p1.first >= p2.first);
	}
};

int main() {
	long long int n, k;
	cin >> n >> k;

	set <pair<int, int>, custSort > s;

	for (int i = 0; i < n; i++) {
		int temp; cin >> temp;
		s.insert(make_pair(temp, i+1));
	}

	long long int sum = n*k - k*(k-1)/2;
	long long int pts = 1;
	set <pair<int, int> >::iterator it = s.begin();
	int ar[k];
	for (int i = 0; i < k; i++) {
		ar[i] = it->second;
		it++;
	}
	sort(ar, ar+k);
	int a = 0, b = 1;

	while (--k) {
		pts = (pts * (ar[b] - ar[a])) % M;
		a++; b++;
	}
	cout << sum << ' ' << pts << endl;
}