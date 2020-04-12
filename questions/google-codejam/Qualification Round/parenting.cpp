#include <bits/stdc++.h>
using namespace std;

bool custSort(const pair<int, pair<int, int> > &a, const pair<int, pair<int, int> > &b) {
	return (a.second.first < b.second.first);
}

int main() {
	int t; cin >> t;
	for (int cn=1; cn <= t; cn++) {
		int n; cin >> n;
		bool imp = false;
		int cam[1441], jam[1441];
		memset(cam, 0, sizeof(cam));
		memset(jam, 0, sizeof(jam));
		char ans[n+1]; ans[n] = '\0';
		vector <pair<int, pair<int, int> > > v;

		for (int i = 0; i < n; i++) {
			int s, e;
			cin >> s >> e;
			v.push_back(make_pair(i, make_pair(s, e)));
		}
		sort(v.begin(), v.end(), custSort);

		for (int i = 0; i < n; i++) {
			int s = v[i].second.first, e = v[i].second.second;
			if (!imp) {
				bool cc = true;
				for (int j = s; j < e; j++) {
					if (cam[j] == 1) {
						cc = false;
						break;
					}
				}
				if (cc) {
					fill(cam+s, cam+e, 1);
					ans[v[i].first] = 'C';
				}
				else {
					bool jj = true;
					for (int j = s; j < e; j++) {
						if (jam[j] == 1) {
							jj = false;
							break;
						}
					}
					if (jj) {
						fill(jam+s, jam+e, 1);
						ans[v[i].first] = 'J';
					}
					else imp = true;
				}
			}
		}

		printf("Case #%d: ", cn);
		if (!imp) cout << ans << endl;
		else cout << "IMPOSSIBLE\n";
	}
}