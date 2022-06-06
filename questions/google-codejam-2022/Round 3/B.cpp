#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
using namespace std;

set<int> s;
vector<int> cnt;
vector<pii> ab;
int n, c;

void modify(int col, int val) {
    cnt[col] += val;

    if (cnt[col] == 0 || (ab[col].ff <= cnt[col] && ab[col].ss >= cnt[col])) s.erase(col);
    else s.insert(col);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";
		
		cin >> n >> c;
        
        vector<int> p(n);
        ab.clear(); ab.resize(c);
        for (int i = 0; i < c; i++) {
            cin >> ab[i].ff >> ab[i].ss;
        }
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            --p[i];
        }
        s.clear(); cnt.clear();
        cnt.resize(c);

        int ans = 0;
        cnt[p[n-1]]++;
        for (int len = 2; len <= n-1; len++) {
            int col = p[n-1];
            modify(p[n-1], -1);
            modify(p[len-2], 1);
            modify(p[len-1], 1);

            if (s.empty()) ans++;
            for (int i = 1; i < n; i++) {
                modify(p[i-1], -1);
                modify(p[(i+len-1)%n], 1);
                if (s.empty()) ans++;
            }
        }
        cout << ans << '\n';
	}
}