#include <bits/stdc++.h>
using namespace std;
int sums[200000];

bool custSort(const int &a, const int &b) {
	return (sums[a] > sums[b]);
}

int main () {
	int n; cin >> n;
	int a[n];
	int indices[n];
	for (int i = 0; i < n ; i++) {
		cin >> a[i];
		sums[i] = a[i]+i+1;
		indices[i] = i;
	}
	sort(indices, indices+n, custSort);
	int cur = 0;

	for (int i = 0; i < n; i++) {
		cout << sums[indices[cur]]+i << ' ';
		sums[n-i-1] -= n;
		if (indices[cur] == n-i-1 && sums[indices[cur]] < sums[indices[(cur+1)%n]]) cur++;
	}
	cout << endl;
}