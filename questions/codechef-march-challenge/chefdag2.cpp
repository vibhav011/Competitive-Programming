#include <bits/stdc++.h>
using namespace std;

bool compSets(const pair<int, set<int> > &p1, const pair<int, set<int> > &p2) {
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

		set<int> f;
		vector<pair<int, set<int> > > lol(n+1, make_pair(0, f));
		vector<vector<int> > rofl(n+1, vector<int>());
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
			int zz[n+1];

			for (int i = 1; i <= n; i++) {m[i] = -k; zz[i] = -k;}
			for (int j = 0; j < k; j++) {
				for (int l = 0; l < v[j][i-1].size(); l++) m[v[j][i-1][l]]++;
				for (int l = 0; l < w[j][i-1].size(); l++) zz[w[j][i-1][l]]++;
			}

			for (int d = 1; d <= n; d++) {
				if (!m[d]) lol[i].second.insert(d);
				if (!zz[d]) rofl[i].push_back(d);
			}
		}

		sort(lol.begin()+1, lol.end(), compSets);

		int ans[n+1];
		for (int i = 1; i <= n; i++) ans[i] = 0;

		int mn = n;

		for (int i = 1; i <= n; i++) {
			set <int> choices = lol[i].second;
			if (choices.size() > 0) {

				int minm = 2*n+1;
				set <int>::iterator it2;// = choices.begin();

				set <int>::iterator it;
				for (it = choices.begin(); it != choices.end(); it++) {
					if (minm > freq[*it]) {
						minm = freq[*it];
						it2 = it;
					}
					else if (minm == freq[*it]) {
						int minsum = 0; int freqsum = 0;

						vector<int> ch = rofl[*it2];
						for (int x5=0; x5 < ch.size(); x5++) {
							for (int kj = i+1; kj <= n; kj++) {
								if (lol[kj].first == ch[x5]) minsum += lol[kj].second.size();
							}
						}

						ch = rofl[*it];
						for (int x5=0; x5 < ch.size(); x5++) {
							for (int kj = i+1; kj <= n; kj++) {
								if (lol[kj].first == ch[x5]) freqsum += lol[kj].second.size();
							}
						}

						if (freqsum < minsum) {
							minm = freq[*it];
							it2 = it;
						}
					}
				}
				
				ans[lol[i].first] = *it2;
				mn--;

				vector<int> delnum;
				delnum.push_back(*it2);
				for (it = choices.begin(); it != choices.end(); it++) {
					freq[*it]--;
					if (freq[*it] <= 0) delnum.push_back(*it);
				}

				for (int j = i+1; j <= n; j++) {
					for (int x3 = 0; x3 < delnum.size(); x3++)
						lol[j].second.erase(delnum[x3]);
				}
				
				sort(lol.begin() + i + 1, lol.end(), compSets);
			}
		}

		cout << mn << endl;
		for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
		cout << endl;
	}
}