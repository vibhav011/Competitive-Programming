#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int, int> 
#define pb push_back
using namespace std;

const int M = 1e5+5;
int n, m, op, ww;
bool snf;
vector<int> adj[M], adjT[M], tree[M];
int dom[M], label[M], arr[M], rev[M], T;
stack<int> st;


void dfsop3(int u) {
	T++;
	arr[u] = dom[u] = T;
	label[u] = 1;
	st.push(u);

	for (int j = 0; j < adj[u].size(); j++) {
		int v = adj[u][j];

		if (!arr[v]) {
			dfsop3(v);
			dom[u] = min(dom[u], dom[v]);
		}
		else if (label[v]) 
			dom[u] = min(dom[u], arr[v]);

	}

	if (dom[u] == arr[u]) {
		while (st.top() != u) {
			rev[st.top()] = u;
			label[st.top()] = 0;
			st.pop(); 
		}
		rev[u] = u;
		label[u] = 0;
		st.pop();
	}

}

vector<int> newver;
set<int> ou1[M], in1[M];
set<int> isol, sources, sinks;

void maxmatch(int u) {
	if (label[u]) return;
	if (ou1[u].size() == 0) {
		ww = u;
		snf = false;
	}
	label[u] = 1;

	// if (sinks.find(u) != sinks.end()) {
	// 	label[u] = 1;
	// 	for (set<int>::iterator it = in1[u].begin(); it != in1[u].end(); it++) {
	// 		ou1[*it].erase(u);
	// 	}
	// 	return u;
	// }
	// if (!snf) return;
	for (set<int>::iterator it = ou1[u].begin(); it != ou1[u].end(); it++) {
		int w = *it;
		if (snf) maxmatch(w);
	}
	return;
}


void solve3 () {
	if (newver.size() == 1) {
		cout << "0\n";
		return;
	}
	for (int i = 0; i < newver.size(); i++) {
		int nd = newver[i];
		if (ou1[nd].size() == 0) {
			if (in1[nd].size() == 0) isol.insert(nd);
			else sinks.insert(nd);
		}
		else if (in1[nd].size() == 0) sources.insert(nd);
	}

	if (sources.size() == 0) {
		int nn = isol.size();
		set<int>::iterator it = isol.begin();
		int fs = *it;
		cout << nn << '\n';
		it++;
		while (it != isol.end()) {
			it--;
			cout << *it+1 << ' ';
			it++;
			cout << *it+1 << '\n';
			it++;
		}
		it--;
		cout << *it+1 << ' ' << fs+1 << '\n';
		return;
	}
	int a = sources.size();
	int b = sinks.size();
	cout << max(a, b) + isol.size() << '\n';

	for (int i = 0; i < newver.size(); i++) label[newver[i]] = 0;

	vector<pii> match;
	set<int> sor2;

	for (set<int>::iterator it = sources.begin(); it != sources.end(); it++) {
		ww = -1;
		snf = true;
		maxmatch(*it);
		if (ww != -1) {
			match.pb(mp(*it, ww));
			sinks.erase(ww);
		}
		else {
			sor2.insert(*it);
		}
	}

	int nn = match.size();

	for (int i = 0; i < nn-1; i++) {
		cout << match[i+1].ss+1 << ' ' << match[i].ff+1 << endl;
	}
	
	if (isol.size() == 0) cout << match[0].ss+1 << ' ' << match[nn-1].ff+1 << '\n';
	else {
		set<int>::iterator it = isol.begin();
		cout << match[0].ss+1 << ' ' << *it+1 << '\n';
		it++;
		while (it != isol.end()) {
			it--;
			cout << *it+1 << ' ';
			it++;
			cout << *it+1 << '\n';
			it++;
		}
		it--;
		cout << *it+1 << ' ' << match[nn-1].ff+1 << '\n';
	}
	set<int>::iterator it1 = sor2.begin();
	set<int>::iterator it2 = sinks.begin();

	while (it1 != sor2.end() && it2 != sinks.end()) {
		cout << *it2+1 << ' ' << *it1+1 << '\n';
		it1++; it2++;
	}
	if (a < b) {
		while (it2 != sinks.end()) {
			cout << *it2+1 << ' ' << match[0].ff+1 << '\n';
			it2++;
		}
	}
	else if (a > b) {
		while (it1 != sor2.end()) {
			cout << match[0].ss+1 << ' ' << *it1+1 << '\n';
			it1++;
		}
	}
	return;

}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		adj[x-1].pb(y-1);
		adjT[y-1].pb(x-1);
	}
	
	
	// disc -> arr
	// low -> dom
	// stackmem -> label
	T = 0;
	for (int i = 0; i <= n; i++) {
		arr[i] = 0;
		label[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		if (!arr[i]) dfsop3(i);
	}

	for (int i = 0; i < n; i++) {
		if (rev[i] == i) {
			newver.pb(i);
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < adj[i].size(); j++) {
			int w = adj[i][j];
			if (rev[i] != rev[w]) {
				ou1[rev[i]].insert(rev[w]);
				in1[rev[w]].insert(rev[i]);
			}
		}
	}
	solve3();
	return 0;	
}
