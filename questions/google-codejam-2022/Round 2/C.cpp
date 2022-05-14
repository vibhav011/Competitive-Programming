#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
using namespace std;

int n;
set<pair<pair<int, set<pair<ull, int> > >, int > > s;
vector<pii> children;
vector<pii> candies;
vector<pii> ans;

ull calc_dist(int i, int j) {
    return (ull)(children[i].ff-candies[j].ff)*(ull)(children[i].ff-candies[j].ff)
         + (ull)(children[i].ss-candies[j].ss)*(ull)(children[i].ss-candies[j].ss);
}

bool solve() {
    if (s.size() == 1 && s.begin()->ff.ff > 1) {
        ans.pb(mp(1+s.begin()->ss, 1-s.begin()->ff.ss.begin()->ss));
        return true;
    }
    if (s.size() == 1 && s.begin()->ff.ff == 1) return false;

    auto it = s.begin();
    int rank = it->ff.ff;
    int check = 1;

    for (; it != s.end(); it++) {
        if (it->ff.ff != rank) break;
        check++;
    }
    it = s.begin();
    for (int i = 0; i < check; i++) {
        auto &z = it->ff.ss;
        ull mn = z.begin()->ff;
        for (auto &p : z) {
            if (p.ff != mn) break;
            int candy = -p.ss;

            ans.pb(mp(1+it->ss, 1+candy));

        }
        it++;
    }
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";
		
		s.clear();
        children.clear();
        candies.clear();

        cin >> n;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            children.pb(mp(x, y));
        }
        for (int i = 0; i < n+1; i++) {
            int x, y;
            cin >> x >> y;
            candies.pb(mp(x, y));
        }

        for (int i = 0; i < n; i++) {
            set<pair<ull, int> > temp;
            for (int j = 0; j < n+1; j++) {
                temp.insert(mp(calc_dist(i, j), -j));
            }
            int x = 0;
            for (auto it = temp.begin(); it != temp.end(); it++) {
                x++;
                if (it->ss == 0) break;
            }
            s.insert(mp(mp(x, temp), i));
        }

        if (solve()) {
            cout << "POSSIBLE\n";
            for (auto &x: ans) cout << x.ff << ' ' << x.ss << '\n';
        } else {
            cout << "IMPOSSIBLE\n";
        }
	}
}