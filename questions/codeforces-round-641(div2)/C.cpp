#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define MAX 200005

using namespace std;

ll MOD = 998244353;

ll pwr(ll x, ll y) {
	ll res = 1;
	while (y > 0) {
		if (y&1) res = res*x;

		y = y>>1;
		x = x*x;
	}
	return res;
}

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}

vector<int> primes;
vector<pii> fact[MAX];

int main () {
	vector<pair<int, pii> > ans;
	vector<pair<int, pii> >::iterator it;

	bool is_composite[MAX];
	fill(is_composite, is_composite+MAX, false);

	for (int i = 2; i < MAX; i++) {
		if (!is_composite[i]) {
			primes.push_back(i);
			fact[i].push_back(make_pair(i, 1));
			ans.push_back(make_pair(i, make_pair(30, 30)));
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

	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		int p = 0, q = 0;
		while (p < ans.size()) {
			if (q == fact[a].size()) {
				ans[p].ss.ss = ans[p].ss.ff;
				ans[p].ss.ff = 0;
				p++;
				continue;
			}

			if (ans[p].ff < fact[a][q].ff) {
				ans[p].ss.ss = ans[p].ss.ff;
				ans[p].ss.ff = 0;
			}
			else if (ans[p].ff == fact[a][q].ff) {
				int x = ans[p].ss.ff, y = ans[p].ss.ss, z = fact[a][q].ss;
				if (z <= x) {
					ans[p].ss.ss = x;
					ans[p].ss.ff = z;
				}
				else if (z < y) ans[p].ss.ss = z;
			}
			else {q++; p--;}
			p++;
		}

		it = ans.begin();

		while (it != ans.end()) {

			if(it->ss.ff + it->ss.ss == 0) {
				it = ans.erase(it);
			}
			else ++it;
		}
	}

	ll finans = 1;
	
	it = ans.begin();

	while (it != ans.end()) {
		//printf("%d : %d %d\n", it->ff, it->ss.ff, it->ss.ss);
		finans *= pwr(it->ff, it->ss.ss);
		++it;
	}
	cout << finans << endl;

	return 0;
}