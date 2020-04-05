#include <bits/stdc++.h>
using namespace std;

int countRelative(vector<int> graph[], int n) {
	bool visited[n+1]; fill(visited, visited+n+1, false);
	visited[1] = true;
	int ans = 1;
	vector<int> sources (1, 1);

	while (!sources.empty()) {
		vector<int> sources2;
		for (int i = 0; i < sources.size(); i++) {	
			for (int j = 0; j < graph[sources[i]].size(); j++) {
				if (!visited[graph[sources[i]][j]]) {
					visited[graph[sources[i]][j]] = true;
					sources2.push_back(graph[sources[i]][j]);
					ans++;
				}
			}
		}
		sources = sources2;
	}
	return ans;
}

int common(vector<int> &a, vector<int> &b) {
	int p = 0, q = 0, ans = 0;
	while (p < a.size() && q < b.size()) {
		if (a[p] == b[q]) {
			ans++; p++; q++;
		}
		else if (a[p] < b[q]) p++;
		else q++;
	}
	return ans;
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<vector<int> > s;

	for (int i = 0; i < n; i++) {
		int p; cin >> p;
		vector<int> temp;
		for (int j = 0; j < p; j++) {
			int z; cin >> z;
			temp.push_back(z);
		}
		sort(temp.begin(), temp.end());
		s.push_back(temp);
	}
	vector<int> graph[n+1];
	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; j < n; j++) {
			if (common(s[i], s[j]) >= k) {
				graph[i+1].push_back(j+1);
				graph[j+1].push_back(i+1);
			}
		}
	}
	cout << countRelative(graph, n) << endl;
}