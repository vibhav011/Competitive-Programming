#include <bits/stdc++.h>
using namespace std;
 
int main () {
	int t; cin >> t;
 
	while (t--) {
		int n; cin >> n;
		map <int, int> skill;
		int m = 0;
		for (int i = 0; i < n; i++) {
			int a; cin >> a;
			skill[a]++;
			if (skill[a] > m) m = skill[a];
		}
		int s = skill.size();
		if (m == s) cout << m-1 << endl;
		else cout << min(m, s) << endl;
	}
}