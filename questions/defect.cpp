#include <bits/stdc++.h>
using namespace std;

int n, m;
int g[50][50];

int c, curNode;
vector<pair<int, int> > pts;

void createGraph(int i, int j, vector<set<int> > &graph) {
	if (i < 0 || i >= n || j < 0 || j >= m) return;
	int cur = g[i][j];
	if (cur > 0) {
		if (cur != curNode) {
			graph[curNode].insert(cur);
			graph[cur].insert(curNode);
		}
		return;
	}

	if (cur != c) {
		pts.push_back(make_pair(i, j));
		return;
	}

	g[i][j] = curNode;
	createGraph(i+1, j, graph);
	createGraph(i-1, j, graph);
	createGraph(i, j+1, graph);
	createGraph(i, j-1, graph);
	return;
}

int BFSdepth(vector<set<int> > &graph, int src) {
	bool visited[graph.size()];
	for (int i = 1; i < graph.size(); i++) visited[i] = false;
	set<int> sources; sources.insert(src);
	set<int>::iterator it, it2;
	int ans = -1;
	while (!sources.empty()) {
		set<int> sources2;
		for (it = sources.begin(); it != sources.end(); it++) {
			visited[*it] = true;
			for (it2 = graph[*it].begin(); it2 != graph[*it].end(); it2++) {
				if (!visited[*it2]) sources2.insert(*it2);
			}
		}
		sources = sources2;
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

		vector<set<int> > graph;
		graph.push_back(set<int>());
		curNode = 0;
		pts.clear(); pts.push_back(make_pair(0, 0));

		while (!pts.empty()) {
			vector<pair<int, int> > pts2 (pts);
			for (int i = 0; i < pts2.size(); i++) {
				pts.clear();
				graph.push_back(set<int>());
				curNode++;
				int p = pts2[i].first, q = pts2[i].second;
				c = g[p][q];
				createGraph(p, q, graph);
			}
		}

		int ans = 2500;
		for (int i = 1; i <= graph.size()-1; i++) ans = min(BFSdepth(graph, i), ans);

		cout << ans << endl;
	}
}