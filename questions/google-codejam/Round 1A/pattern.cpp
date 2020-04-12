#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		int n; cin >> n;
		string strs[n];
		string start[n];
		string end[n];
		pair<int, int> seind[n];
		int st_ind = 0, jm1 = 0, en_ind = 0, jm2 = 0;
		for (int i = 0; i < n; i++) {
			cin >> strs[i];
			for (int j = 0; j < strs[i].size(); j++) {
				if (strs[i][j] == '*') {
					seind[i].first = j;
					start[i] = strs[i].substr(0, j);
					if (j > jm1) {
						jm1 = j;
						st_ind = i;
					}
					break;
				}
			}
			for (int j = strs[i].size()-1; j >= 0; j--) {
				if (strs[i][j] == '*') {
					seind[i].second = j;
					end[i] = strs[i].substr(j+1);
					if (strs[i].size()-j-1 > jm2) {
						jm2 = strs[i].size()-j-1;
						en_ind = i;
					}
					break;
				}
			}
		}
		bool notPossible = false;

		for (int i = 0; i < n && !notPossible; i++) {
			if (i == st_ind) continue;
			for (int j = 0; j < start[i].size(); j++) {
				if (start[i][j] != start[st_ind][j]) {
					notPossible = true;
					break;
				}
			}
		}

		for (int i = 0; i < n && !notPossible; i++) {
			if (i == en_ind) continue;
			string a = end[i], b = end[en_ind];
			reverse(a.begin(), a.end()); reverse(b.begin(), b.end());

			for (int j = 0; j < a.size(); j++) {
				if (a[j] != b[j]) {
					notPossible = true;
					break;
				}
			}
		}

		if (notPossible) printf("Case #%d: *\n", cn);
		else {
			string mid = "";
			for (int i = 0; i < n; i++) {
				for (int j = seind[i].first+1; j < seind[i].second; j++) {
					if (strs[i][j] != '*') mid = mid + strs[i][j];
				}
			}
			string final = start[st_ind] + mid + end[en_ind] + '\n';
			printf("Case #%d: ", cn);
			cout << final;
		}

	}
}