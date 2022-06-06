#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
using namespace std;

string s = "ACDEHIJKMORST";
vector<set<int> > adj;
int n;
vector<int> l, r, letr;

void dfs(int u) {
    if (letr[u] != -1) return;
    set<int> pos;
    for (int  i =0 ;i < 13; i++) pos.insert(i);
    for (int v : adj[u]) pos.erase(letr[v]);

    letr[u] = *pos.begin();

    for (int v : adj[u]) dfs(v);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";
		
		cin >> n;
        adj.clear(); adj.resize(n+1);
        l.clear(); r.clear();
        l.resize(n+1); r.resize(n+1);
        letr.clear();
        letr.resize(n+1, -1);

        for (int i = 1; i <= n; i++) cin >> l[i];
        for (int i = 1; i <= n; i++) cin >> r[i];

        bool pos = true;
        for (int i = 1; i <= n; i++) {
            int x = l[i];
            adj[i].insert(x);
            adj[x].insert(i);
            x = l[x];
            adj[i].insert(x);
            adj[x].insert(i);
            x = r[l[i]];
            adj[i].insert(x);
            adj[x].insert(i);

            x = r[i];
            adj[i].insert(x);
            adj[x].insert(i);
            x = l[x];
            adj[i].insert(x);
            adj[x].insert(i);
            x = r[r[i]];
            adj[i].insert(x);
            adj[x].insert(i);
        }

        for (int i = 1; i <= n; i++) {
            if (adj[i].find(i) != adj[i].end()) {
                pos = false;
                break;
            }
        }

        if (!pos) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        for (int i = 1; i <= n; i++) {
            dfs(i);
        }
        for (int i = 1; i <= n; i++) {
            cout << s[letr[i]];
        }
        cout << '\n';
	}
}