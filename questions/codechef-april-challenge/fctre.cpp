#include <bits/stdc++.h>
#define ll long long int
#define MAX 1000001
#define N 100001
#define M 1000000007
using namespace std;
//using namespace std::chrono;
vector<int> dfsnodes;
vector<int> primes;
vector<pair<int, int> > fact[MAX];
ll invpwr[N+5];
int st[N], en[N], curtime = 0;
bool visited[N];
int block_size;
int ansFacs[MAX];
ll finalAns1[N];
ll finalAns2[N];
int thresh = 5000;

ll pwr(ll x, ll y) {
	ll res = 1;
	x = x%M;
	while (y > 0) {
		if (y&1) res = (res*x)%M;

		y = y>>1;
		x = (x*x)%M;
	}
	return res;
}

void multiply (int ind, vector<pair<int, int> > &b) {
	int pr = b.back().first;
	if (pr > thresh) {
		ansFacs[pr]++;
		finalAns1[ind] = (((finalAns1[ind] * (ansFacs[pr]+1))%M)*invpwr[ansFacs[pr]])%M;
	}
}
void divide (int ind, vector<pair<int, int> > &b) {
	int pr = b.back().first;
	if (pr > thresh) {
		ansFacs[pr]--;
		finalAns1[ind] = (((finalAns1[ind] * (ansFacs[pr]+1))%M)*invpwr[ansFacs[pr]+2])%M;
	}
}

void dfs(int node, vector<int> adj[]) {
	if (visited[node]) return;
	visited[node] = true;
	st[node] = ++curtime;
	dfsnodes.push_back(node);
	for (int i = 0; i < adj[node].size(); i++) {
		dfs(adj[node][i], adj);
	}
	en[node] = ++curtime;
	dfsnodes.push_back(node);
}

struct Query {
	int id, l, r, lca;
};
bool sortQ(Query &q1, Query &q2) {
	return (q1.l/block_size == q2.l/block_size) ? (q1.r < q2.r) : (q1.l/block_size < q2.l/block_size);
}

int main () {
	bool is_composite[MAX];
	fill(is_composite, is_composite+MAX, false);

	for (int i = 2; i < MAX; i++) {
		if (!is_composite[i]) {
			primes.push_back(i);
			fact[i].push_back(make_pair(i, 1));
		}
		for (int j = 0; j < primes.size() && i*primes[j] < MAX; j++) {
			is_composite[i*primes[j]] = true;

			if (i%primes[j] == 0) {
				fact[i*primes[j]] = fact[i];
				fact[i*primes[j]][0].second++;
				break;
			}
			else {
				fact[i*primes[j]] = fact[primes[j]];
				fact[i*primes[j]].insert(fact[i*primes[j]].end(), fact[i].begin(), fact[i].end());
			}
		}
	}

	invpwr[1] = 1;
	for (int i = 2; i < N+5; i++) invpwr[i] = pwr(i, M-2);

	int T; cin >> T;
	
	while (T--) {
		int n; cin >> n;
		int p[n+1], depth[n+1], degree[n+1], jump_parent[n+1];

		fill(p, p+n+1, -1); fill(jump_parent, jump_parent+n+1, -1);
		fill(depth, depth+n+1, -1); fill(degree, degree+n+1, 0);
		
		vector<int> adj[n+1];
		for (int i = 1; i < n; i++) {
			int x, y; cin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
			degree[x]++;
			degree[y]++;
		}

		int a[n+1];
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

		queue<int> leafs;
		for (int i = 1; i <= n; i++) {
			if (degree[i] == 1) leafs.push(i);
		}
		int n2 = n;

		while (n2 > 2) {
			int sz = leafs.size();
			while (sz--) {
				int fr = leafs.front();
				leafs.pop();
				n2--;

				for (auto j = adj[fr].begin(); j != adj[fr].end(); j++) { 
					degree[*j]--; 
					if (degree[*j] == 1) 
						leafs.push(*j); 
				}
			}
		}

		int root = leafs.front();
		dfsnodes.clear(); dfsnodes.push_back(0);
		memset(visited, false, sizeof(visited));
		curtime = 0;

		dfs(root, adj);

		vector<pair<int, int> > prod[n+1];
		for (int i = 0; i < fact[a[root]].size(); i++) {
			if (fact[a[root]][i].first > thresh) break;
			prod[root].push_back(fact[a[root]][i]);
		}

		p[root] = root; jump_parent[root] = root;
		depth[root] = 0;
		vector<int> sources(1, root);
		
		bool visited2[n+1];
		memset(visited2, false, sizeof(visited2));
		visited2[root] = true;

		int ii = 0;
		while (sources.size() < n) {
			int ss = sources.size();
			for (; ii < ss; ii++) {
				for (int j = 0; j < adj[sources[ii]].size(); j++) {
					int node = adj[sources[ii]][j];
					if (!visited2[node]) {
						visited2[node] = true;
						sources.push_back(node);
						p[node] = sources[ii];
						depth[node] = depth[sources[ii]]+1;

						if (depth[node]%int(sqrt(n)) == 0) {
							jump_parent[node] = sources[ii];
							//prod[node] = fact[a[node]];
						}
						else {
							jump_parent[node] = jump_parent[sources[ii]];
							//multiply(fact[a[node]], prod[sources[ii]], prod[node]);
						}

						int pp = 0, qq = 0;
						while (pp < fact[a[node]].size() || qq < prod[sources[ii]].size()) {
							if (pp == fact[a[node]].size()) {
								prod[node].push_back(prod[sources[ii]][qq]);
								qq++;
							}
							else if (qq == prod[sources[ii]].size()) {
								if (fact[a[node]][pp].first > thresh) break;
								prod[node].push_back(fact[a[node]][pp]);
								pp++;
							}
							else {
								pair<int, int> pr1 = fact[a[node]][pp], pr2 = prod[sources[ii]][qq];
								if (pr1.first < pr2.first) {prod[node].push_back(pr1); pp++;}
								else if (pr1.first > pr2.first) {prod[node].push_back(pr2); qq++;}
								else {
									prod[node].push_back(make_pair(pr1.first, pr1.second+pr2.second));
									pp++;
									qq++;
								}
							}
						}
						
					}
				}
			}
		}
		
		int q; cin >> q;
		Query *qrs;
		qrs = new Query[q+1];
		block_size = max(1, 2*n/int(sqrt(q)));
		fill(finalAns2, finalAns2+q+1, 1);

		for (ii = 0; ii < q; ii++) {
			int u, v;
			scanf("%d %d", &u, &v);
			int u1 = u, v1 = v;

			vector<pair<int, int> > U, V, W;
			U = prod[u]; V = prod[v];
			
			while (depth[jump_parent[u]] > depth[jump_parent[v]]) {
				u = jump_parent[u];
			}
			while (depth[jump_parent[v]] > depth[jump_parent[u]]) {
				v = jump_parent[v];
			}
			while (jump_parent[u] != jump_parent[v]) {
				u = jump_parent[u];
				v = jump_parent[v];
			}
			while (depth[u] > depth[v]) {
				u = p[u];
			}
			while (depth[v] > depth[u]) {
				v = p[v];
			}
			while (u != v) {
				u = p[u];
				v = p[v];
			}
			if (st[u1] > st[v1]) swap(u1, v1);
			if (u1 != u) {
				qrs[ii+1].l = en[u1];
				qrs[ii+1].r = st[v1];
			}
			else {
				qrs[ii+1].l = st[u1];
				qrs[ii+1].r = st[v1];
			}
			qrs[ii+1].lca = u;
			qrs[ii+1].id = ii+1;

			W = prod[u];
			vector<pair<int, int> > X;
			
			int uu = 0, vv = 0;
			while (uu < U.size() || vv < V.size()) {
				if (uu == U.size()) {X.push_back(V[vv]); vv++;}
				else if (vv == V.size()) {X.push_back(U[uu]); uu++;}
				else {
					pair<int, int> pr1 = U[uu], pr2 = V[vv];
					if (pr1.first < pr2.first) {X.push_back(pr1); uu++;}
					else if (pr1.first > pr2.first) {X.push_back(pr2); vv++;}
					else {
						X.push_back(make_pair(pr1.first, pr1.second+pr2.second));
						uu++;
						vv++;
					}
				}
			}

			U = fact[a[u]];
			int xx = 0; uu = 0;
			while (uu < U.size()) {
				pair<int, int> pr2 = U[uu];
				if (pr2.first > thresh) break;

				pair<int, int> pr1 = X[xx];

				if (pr1.first == pr2.first) {
					X[xx].second = pr1.second + pr2.second;
					uu++;
				}
				xx++;
			}

			int ww = 0; xx = 0;
			while (xx < X.size()) {
				if (ww < W.size()) {
					pair<int, int> pr1 = X[xx], pr2 = W[ww];

					if (pr1.first == pr2.first) {
						X[xx].second = pr1.second-2*pr2.second;
						ww++;
					}
				}
				finalAns2[ii+1] = (finalAns2[ii+1]*(X[xx].second+1))%M;
				xx++;
			}
		}

		sort(qrs+1, qrs+q+1, sortQ);
		memset(ansFacs, 0, sizeof(ansFacs));
		fill(finalAns1, finalAns1+q+1, 1);

		bool vis[n+1];
		memset(vis, false, sizeof(vis));

		int curL = qrs[1].l, curR = qrs[1].r;

		for (int i = curL; i <= curR; i++) {
			if (!vis[dfsnodes[i]]) {
				vis[dfsnodes[i]] = true;
				multiply(qrs[1].id, fact[a[dfsnodes[i]]]);
			}
			else {
				vis[dfsnodes[i]] = false;
				divide(qrs[1].id, fact[a[dfsnodes[i]]]);
			}
		}
		if (dfsnodes[qrs[1].l] != qrs[1].lca) {
			multiply(qrs[1].id, fact[a[qrs[1].lca]]);
		}

		finalAns1[qrs[2].id] = finalAns1[qrs[1].id];

		if (dfsnodes[qrs[1].l] != qrs[1].lca) {
			divide(qrs[2].id, fact[a[qrs[1].lca]]);
		}

		for (int i = 2; i < q+1; i++) {
			int L = qrs[i].l, R = qrs[i].r;

			while (L > curL) {
				if (!vis[dfsnodes[curL]]) {
					vis[dfsnodes[curL]] = true;
					multiply(qrs[i].id, fact[a[dfsnodes[curL]]]);
				}
				else {
					vis[dfsnodes[curL]] = false;
					divide(qrs[i].id, fact[a[dfsnodes[curL]]]);
				}
				curL++;
			}
			while (L < curL) {
				curL--;
				if (!vis[dfsnodes[curL]]) {
					vis[dfsnodes[curL]] = true;
					multiply(qrs[i].id, fact[a[dfsnodes[curL]]]);
				}
				else {
					vis[dfsnodes[curL]] = false;
					divide(qrs[i].id, fact[a[dfsnodes[curL]]]);
				}
			}
			while (R > curR) {
				curR++;
				if (!vis[dfsnodes[curR]]) {
					vis[dfsnodes[curR]] = true;
					multiply(qrs[i].id, fact[a[dfsnodes[curR]]]);
				}
				else {
					vis[dfsnodes[curR]] = false;
					divide(qrs[i].id, fact[a[dfsnodes[curR]]]);
				}
			}
			while (R < curR) {
				if (!vis[dfsnodes[curR]]) {
					vis[dfsnodes[curR]] = true;
					multiply(qrs[i].id, fact[a[dfsnodes[curR]]]);
				}
				else {
					vis[dfsnodes[curR]] = false;
					divide(qrs[i].id, fact[a[dfsnodes[curR]]]);
				}
				curR--;
			}
			if (dfsnodes[qrs[i].l] != qrs[i].lca) {
				multiply(qrs[i].id, fact[a[qrs[i].lca]]);
			}

			if (i < q) {
				finalAns1[qrs[i+1].id] = finalAns1[qrs[i].id];

				if (dfsnodes[qrs[i].l] != qrs[i].lca) {
					divide(qrs[i+1].id, fact[a[qrs[i].lca]]);
				}
			}
		}

		for (int i = 1; i < q+1; i++) printf("%lld\n", (finalAns1[i] * finalAns2[i])%M);
	}

	return 0;
}