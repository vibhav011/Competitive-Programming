#include <bits/stdc++.h>
using namespace std;

bool compSets(const pair<int, set<pair<int, int> > > &p1, const pair<int, set<pair<int, int> > > &p2) {
	return (p1.second.size() < p2.second.size());
}

int main() {
	int t; cin >> t;


	while (t--) {
		int n, k;
		//cin >> n >> k;
		scanf("%d %d", &n, &k);

		int ar[k][n];

		for (int i =0; i < k; i++) for (int j = 0; j < n; j++) scanf("%d", &ar[i][j]);

		vector<vector<vector<int> > > v, w;
		for (int i = 0; i < n; i++) {
			vector<vector<int> > temp(n, vector<int>());
			v.push_back(temp);
			w.push_back(temp);
		}
		for (int i = 0; i < k; i++) {
			for (int p = 0; p < n-1; p++) {
				
				for (int q = p+1; q < n; q++) {
					v[i][ar[i][p]-1].push_back(ar[i][q]);
				}
			}

			for (int p = 1; p < n; p++) {
				
				for (int q = p-1; q > -1; q--) {
					w[i][ar[i][p]-1].push_back(ar[i][q]);
				}
			}
		}

		set<pair<int, int> > f;
		vector<pair<int, set<pair<int, int> > > > lol(n+1, make_pair(0, f));
		int freq[n+1];
		for (int i = 1; i <=n; i++) freq[i] = 0;

		for (int i = 1; i <= n; i++) {
			int z[n+1];

			for (int i = 1; i <= n; i++) {z[i] = -k;}
			for (int j = 0; j < k; j++) {
				for (int l = 0; l < w[j][i-1].size(); l++) z[w[j][i-1][l]]++;
			}

			lol[i].first = i;
			for (int d = 1; d <= n; d++) {
				if (!z[d]) freq[i]++;
			}
		}

		for (int i = 1; i <= n; i++) {
			int m[n+1];

			for (int i = 1; i <= n; i++) {m[i] = -k;}
			for (int j = 0; j < k; j++) {
				for (int l = 0; l < v[j][i-1].size(); l++) m[v[j][i-1][l]]++;
			}

			for (int d = 1; d <= n; d++) {
				if (!m[d]) lol[i].second.insert(make_pair(freq[d], d));
			}
		}

		sort(lol.begin()+1, lol.end(), compSets);

		int ans[n+1];
		for (int i = 1; i <= n; i++) ans[i] = 0;

		int mn = n;

		for (int i = 1; i <= n; i++) {
			set <pair<int, int> > choices = lol[i].second;
			if (choices.size() > 0) {
				ans[lol[i].first] = choices.begin()->second;
				mn--;

				for (int j = i+1; j <= n; j++) lol[j].second.erase(*(choices.begin()));
				sort(lol.begin() + i + 1, lol.end(), compSets);
			}
		}

		cout << mn << endl;
		for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
		cout << endl;
	}
}