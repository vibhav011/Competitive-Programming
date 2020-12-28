#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

string s;
int n;
pii obs;
map<char, pii> pos;

pii simulate() {
	pii ret = mp(0, 0);
	pii nxt;
	for (int j = 0; j < n; j++) {
		nxt.ff = ret.ff + pos[s[j]].ff;
		nxt.ss = ret.ss + pos[s[j]].ss;
		if (nxt != obs) ret = nxt;
	}
	return ret;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	pos['L'] = mp(-1, 0);
	pos['R'] = mp(1, 0);
	pos['D'] = mp(0, -1);
	pos['U'] = mp(0, 1);

	int t; cin >> t;
	while (t--) {
		cin >> s;
		n = s.size();

		bool found = false;
		pii cur = mp(0, 0);
		for (int i = 0; i < n; i++) {
			obs.ff = cur.ff + pos[s[i]].ff;
			obs.ss = cur.ss + pos[s[i]].ss;
			pii ans = simulate();
			if (ans.ff == 0 && ans.ss == 0) {
				cout << obs.ff << ' ' << obs.ss << '\n';
				found = true;
				break;
			}
			cur = obs;
		}
		if (!found) cout << "0 0\n";
	}
	
}

