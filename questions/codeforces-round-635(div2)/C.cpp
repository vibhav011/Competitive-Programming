#include <bits/stdc++.h>
#define ll long long int
#define N 200005
using namespace std;

vector<vector<int> > adj (N, vector<int>());
int depth[N];
int children[N];
bool visited2[N];

int ch (int node) {
	if (visited2[node]) return -1;
	visited2[node] = true;

	if (children[node] > -1) return children[node];

	int c = 0;
	for (int i = 0; i < adj[node].size(); i++) {
		c += 1 + ch(adj[node][i]);
	}
	children[node] = c;
	return c;
}

int main () {
	memset(depth, 0, sizeof(depth));
	memset(visited2, false, sizeof(visited2));
	fill(children, children+N, -1);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 2; i <= n; i++) {
		if (adj[i].size() == 1) children[i] = 0;
	}
	ch(1);

	depth[1] = 0;
	vector<int> sources(1, 1);
	
	bool visited[n+1];
	memset(visited, false, sizeof(visited));
	visited[1] = true;
	int ii = 0;
	while (sources.size() < n) {
		int ss = sources.size();
		for (; ii < ss; ii++) {
			for (int j = 0; j < adj[sources[ii]].size(); j++) {
				int node = adj[sources[ii]][j];
				if (!visited[node]) {
					visited[node] = true;
					sources.push_back(node);
					depth[node] = depth[sources[ii]]+1;
				}
			}
		}
	}

	int cd[n+1];
	for (int i = 1; i <= n; i++) cd[i] = children[i] - depth[i];
	sort(cd+1, cd+n+1, greater<int>());

	ll ans = 0;
	for (int i = 1; i <= n-k; i++) {
		ans += cd[i];
	}
	cout << ans << endl;
}