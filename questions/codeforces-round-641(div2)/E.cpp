#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

const int MAX = 1002;
int n, m;
int a[MAX][MAX], dist[MAX][MAX];
bool visited[MAX][MAX];

int main () {
	int t;
	cin >> n >> m >> t;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c; cin >> c;
			a[i][j] = c - '0';
		}
	}

	for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++) dist[i][j] = -1;

	memset(visited, 0, sizeof(visited));
	vector<pii> pivots;
	int adj[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int u = 0; u < 4; u++) {
				int nx = i + adj[u][0], ny = j + adj[u][1];
				if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
					if (a[i][j] == a[nx][ny]) {
						dist[i][j] = 0;
						pivots.pb(mp(i, j));
					}
				}
			}
		}
	}

	int ind = 0;

	while (ind < pivots.size()) {
		int x = pivots[ind].ff, y = pivots[ind].ss;
		ind++;
		if (visited[x][y]) continue;
		visited[x][y] = true;

		for (int u = 0; u < 4; u++) {
			int nx = x + adj[u][0], ny = y + adj[u][1];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
				if (dist[nx][ny] == -1) {
					dist[nx][ny] = dist[x][y] + 1;
					pivots.pb(mp(nx, ny));
				}
			}
		}
	}

	while (t--) {
		int i, j;
		ll p;
		cin >> i >> j >> p;

		if (dist[i][j] == -1) cout << a[i][j] << endl;
		else {
			p = max((ll)0, p-dist[i][j]) & 1;
			cout << (a[i][j] ^ p) << endl;
		}
	}

}