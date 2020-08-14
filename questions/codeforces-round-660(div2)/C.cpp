#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

const int M = 1e5+5;
vector<int> adj[M];
int n, m;
int cit[M];
int hap[M];
int tot[M];
int good[M];
bool vis[M];
bool OK;

void dfs(int root) {
	vis[root] = true;
	tot[root] = cit[root];
	for (int i = 0; i < adj[root].size(); i++) {
		if (!vis[adj[root][i]]) {
			dfs(adj[root][i]);
			tot[root] += tot[adj[root][i]];
		}
	}
}

void dfs2(int root) {
	vis[root] = true;
	int sum = 0;
	for (int i = 0; i < adj[root].size(); i++) {
		if (!vis[adj[root][i]]) {
			sum += good[adj[root][i]];
			dfs2(adj[root][i]);
		}
	}
	if (sum > good[root]) OK = false;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> cit[i];
		for (int i = 1; i <= n; i++) cin >> hap[i];
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			vis[i] = false;
		}

		for (int i = 1; i <= n-1; i++) {
			int x, y;
			cin >> x >> y;
			adj[x].pb(y);
			adj[y].pb(x);
		}

		if (n==1) {
			if (abs(hap[1]) > cit[1] || (hap[1]+cit[1])&1)
				cout << "NO\n";
			else cout << "YES\n";
			continue;
		}

		dfs(1);
		
		bool ok = true;
		for (int i = 1; i <= n; i++) {
			if (abs(hap[i]) > tot[i] || (hap[i]+tot[i])&1) {
				ok = false;
				break;
			}
			good[i] = (hap[i]+tot[i])/2;
		}
		if (!ok) {
			cout << "NO\n";
			continue;
		}
		for (int i = 1; i <= n; i++)
			vis[i] = false;

		OK = true;
		dfs2(1);

		cout << (OK ? "YES\n" : "NO\n");
	}
}

