#include <bits/stdc++.h>
#define ll long long int
using namespace std;
vector<pair<int, int> > graph[231];
ll cost[231][231];
ll inf;
int c, f;

ll calcCost(int a, int b) {
	if (cost[a][b] != inf) return cost[a][b];

	cost[a][a] = 0;
	int assigned = 0;
	bool done[c+1]; fill(done, done+c+1, false);

	while (assigned < c) {
		int src;
		ll mn = inf;
		for (int i = 1; i <= c; i++) {
			if (!done[i] && cost[a][i] < mn) {
				mn = cost[a][i];
				src = i;
			}
		}
		done[src] = true;
		cost[src][a] = cost[a][src];
		assigned++;

		for (int i = 0; i < graph[src].size(); i++) {
			pair<int, int> node = graph[src][i];

			if (!done[node.first]) {
				cost[a][node.first] = min(cost[a][node.first], cost[a][src]+node.second);
			}
		}
	}
	return cost[a][b];
}

int main () {
	inf = 1;
	inf <<= 40;
	
	cin >> c >> f;
	
	for (int i = 0; i < f; i++) {
		int x, y, p;
		cin >> x >> y >> p;
		graph[x].push_back(make_pair(y, p));
		graph[y].push_back(make_pair(x, p));
	}
	for (int i = 1; i <= c; i++) for (int j = 1; j <= c; j++) cost[i][j] = inf;
	ll cst = -1;
	for (int i = 1; i <= c; i++) {
		for (int j = 1; j <= c; j++) cst = max(cst, calcCost(i, j));
	}
	cout << cst << endl;
}