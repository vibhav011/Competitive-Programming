#include <bits/stdc++.h>
#define ll long long int
#define MAX 1000001
#define N 200001
#define M 1000000007
using namespace std;

int calcAns(int freq[]) {
	int last = 0, ans = 100;
	for (int i = 1; i < 101; i++) {
		if (freq[i] > 1) return 0;
		if (freq[i]) {
			if (last) ans = min(ans, i - last);
			last = i;
		}
	}
	return ans;
}

int main () {
	
	int t; cin >> t;
	while (t--) {
		int n, q; cin >> n >> q;
		int p[n+1], depth[n+1];
		fill(p, p+n+1, -1); fill(depth, depth+n+1, -1);
		p[1] = 1; depth[1] = 0;
		int a[n + 1];
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		vector<int> adj[n+1];
		for (int i = 1; i < n; i++) {
			int x, y; cin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		
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
						p[node] = sources[ii];
						depth[node] = depth[sources[ii]]+1;
					}
				}
			}
		}

		for (ii = 0; ii < q; ii++) {
			int u, v;
			scanf("%d %d", &u, &v);
			
			int freq[101];
			memset(freq, 0, sizeof(freq));
			int steps = 0;
			bool zero = false;
			while (depth[u] > depth[v]) {
				freq[a[u]]++;
				u = p[u];
				steps++;
				if (steps > 100) {
					zero = true;
					break;
				}
			}
			while (depth[v] > depth[u]) {
				freq[a[v]]++;
				v = p[v];
				steps++;
				if (steps > 100) {
					zero = true;
					break;
				}
			}
			while (u != v) {
				freq[a[u]]++;
				freq[a[v]]++;
				u = p[u];
				v = p[v];
				steps++;
				if (steps > 100) {
					zero = true;
					break;
				}
			}
			freq[a[u]]++;

			if (zero) {
				cout << "0\n";
				continue;
			}
			
			cout << calcAns(freq) << endl;
		}
	}
}