#include <iostream>
#include <map>
#include <set>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second

using namespace std;

int main () {
	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		int u; cin >> u;
		map<char, set<int> > chmap;
		map<char, int> chfreq;
		set<int> intset;
		for (int p = 0; p < 10; p++) intset.insert(p);
		string ans(10, 'A');
		bool mis = false;

		for (int i = 0; i < 10000; i++) {
			ll q; cin >> q;
			string r; cin >> r;
			if (chmap.size() < 10) {
				for (int j = 0; j < r.size(); j++) {
					if (chmap.find(r[j]) == chmap.end()) {
						chmap[r[j]] = intset;
					}
				}
			}
			
			chmap[r[0]].erase(0);
			if (q != -1) {
				ll m = q;
				int d = 0;
				int ld;
				while (m > 0) {
					d++;
					if (m < 10) ld = m;
					m /= 10;
				}

				if (d == r.size()) {
					for (int rm = ld+1; rm <= 9; rm++) chmap[r[0]].erase(rm);
				}
			}
			else {
				mis = true;
				chfreq[r[0]]++;
			}
			
		}

		map<char, set<int> >::iterator it1, it2;

		if (!mis) {

			for (int i = 1; i <= 10; i++) {

				for (it1 = chmap.begin(); it1 != chmap.end(); it1++) {
					if (it1->ss.size() == 1) {
						int f = *it1->ss.begin();
						for (it2 = chmap.begin(); it2 != chmap.end(); it2++) {
							if (it1 != it2) it2->ss.erase(f);
						}
					}
				}
			}

			for (auto elem : chmap) {
				ans[*elem.ss.begin()] = elem.ff;
			}
		}
		else {
			for (it1 = chmap.begin(); it1 != chmap.end(); it1++) {
				if (it1->ss.size() == 10) {
					ans[0] = it1->ff;
					chfreq[it1->ff] = -1;
				}
			}
			map<char, int>::iterator it3, itm;
			for (int i = 1; i < 10; i++) {
				int mx = -1;
				for (it3 = chfreq.begin(); it3 != chfreq.end(); it3++) {
					if (it3->ss > mx) {
						mx = it3->ss;
						itm = it3;
					}
				}
				itm->ss = -1;
				ans[i] = itm->ff;
			}
		}
		
		printf("Case #%d: ", cn);
		cout << ans << endl;
	}
}