#include <bits/stdc++.h>
using namespace std;

int n, m;
int g[50][50];
bool connected[2501][2501];
vector<vector<int> > graph;

int c, curNode;
vector<pair<int, int> > pts;

void createGraph(int i, int j) {
	if (i < 0 || i >= n || j < 0 || j >= m) return;
	int cur = g[i][j];
	if (cur > 0) {
		if (cur != curNode && !connected[cur][curNode]) {
			graph[curNode].push_back(cur);
			graph[cur].push_back(curNode);
			connected[cur][curNode] = true;
		}
		return;
	}

	if (cur != c) {
		pts.push_back(make_pair(i, j));
		return;
	}

	g[i][j] = curNode;
	createGraph(i+1, j);
	createGraph(i-1, j);
	createGraph(i, j+1);
	createGraph(i, j-1);
	return;
}

int BFSdepth(int src) {
	int status[graph.size()];
	fill(status, status+graph.size(), 0);		// 0 = inactive, 1 = active, 2 = visited

	vector<int> sources; sources.push_back(src);
	int it = 0, it2;
	int ans = -1;
	while (it < sources.size()) {
		int e = sources.size();
		for (; it < e; it++) {
			status[sources[it]] = 2;
			for (it2 = 0; it2 < graph[sources[it]].size(); it2++) {
				int ind = graph[sources[it]][it2];
				if (status[ind] == 0) {
					sources.push_back(ind);
					status[ind] = 1;
				}
			}
		}
		ans++;
	}
	return ans;
}

int main() {
	int t; cin >> t;

	while (t--) {
		cin >> n >> m;
		int temp;
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
			cin >> temp;
			g[i][j] = temp-1;
		}

		for (int i = 0; i < 2501; i++) for (int j = 0; j < 2501; j++) connected[i][j] = false;

		graph.clear(); graph.push_back(vector<int>());
		pts.clear(); pts.push_back(make_pair(0, 0));
		curNode = 0;

		while (!pts.empty()) {
			vector<pair<int, int> > pts2 (pts);
			pts.clear();
			for (int i = 0; i < pts2.size(); i++) {
				int p = pts2[i].first, q = pts2[i].second;

				if (g[p][q] <= 0) {
					graph.push_back(vector<int>());
					curNode++;
					c = g[p][q];
					createGraph(p, q);
				}
			}
		}

		int ans = 2500;
		for (int i = 1; i < graph.size(); i++) ans = min(BFSdepth(i), ans);

		cout << ans << endl;
	}
}