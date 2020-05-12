#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;

	while (t--) {
		int n, k; cin >> n >> k;
		set<int> ar;
		
		for (int i = 0; i < n; i++) {
			int temp; cin >> temp;
			ar.insert(temp);
		}

		if (ar.size() > k) cout << "-1\n";
		else {
			vector<int> ar2(k, 1);
			int ind = 0;
			for (set<int>::iterator it = ar.begin(); it != ar.end(); it++) {
				ar2[ind] = *it;
				ind++;
			}
			cout << n*k << endl;
			for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) cout << ar2[j] << ' ';
			cout << endl;
		} 
	}
}