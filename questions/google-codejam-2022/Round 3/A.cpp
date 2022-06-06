#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define fio fflush(stdout)
using namespace std;

vector<pii> ans;

int t, n, k;
vector<int> v, col_v;
vector<vector<int> > cycles;


void find_cycles() {
	set<int> all;
	for (int i = 1; i <= n; i++) all.insert(i);
	cycles.clear();

	while (!all.empty()) {
		int x = *all.begin();
		all.erase(x);
		vector<int> cycle(1, x);
		int y = v[x];
		while (y != x) {
			cycle.pb(y);
			all.erase(y);
			y = v[y];
		}
		cycles.pb(cycle);
	}
}

void read_nums() {
	for (int i = 1; i <= n; i++) cin >> v[i];
	find_cycles();
}

void print_nums() {
	for (int i = 1; i <= n; i++) cout << col_v[i] << " ";
	cout << endl; fio;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t >> n >> k;
	v.resize(n+1);
	col_v.resize(n+1);
	int res;

	for (int cn = 1; cn <= t; cn++) {
		
		while (true) {
			read_nums();
			
			int col = 1;
			for (auto &c : cycles) {
				for (auto &x : c) {
					col_v[x] = col;
				}
				col++;
			}
			print_nums();
			cin >> res;
			if (res == -1) return 0;
			if (res == 1) break;
		}
	}
	return 0;
}