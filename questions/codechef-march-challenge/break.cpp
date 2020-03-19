#include <bits/stdc++.h>
using namespace std;

bool canDraw(int a[], int b[], int n) {
	int p = 0, q = 0;
	int lastCard;

	set<int> cards;

	while (p < n && q < n) {
		if (!cards.empty() && cards.find(a[p]) == cards.end()) return false;
		cards.insert(a[p]);
		lastCard = a[p];
		p++;
		
		if (b[q] <= lastCard) return false;
		cards.insert(b[q]);
		q++;
	}
	return true;
}

// bool canDraw2(vector<int> &a, vector<int> &b) {
	
// }

int main() {
	int t, s;
	cin >> t >> s;

	while (t--) {
		int n; cin >> n;

		int a[n], b[n];

		for (int i = 0; i < n ; i++) cin >> a[i];
		for (int i = 0; i < n ; i++) cin >> b[i];

		sort(a, a+n); sort(b, b+n);

		if (s == 1) {
			if (canDraw(a, b, n)) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
		else {
			if (canDraw(a, b, n)) cout << "YES" << endl;
			else cout << "NO" << endl;
		}

	}
}