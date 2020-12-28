#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

const int N = 5e5+5;
int n;
pii t[2 * N];

void build() {
  for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, pii value) {
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

pii query(int l, int r) {
  pii res = mp(-1, -1);
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(res, t[--r]);
  }
  return res;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; i++) t[i+n] = mp(0, -1);
	build();
	
	int ptr = 0;
	int cust = 1;
	
	for (int q = 0; q < n; q++) {
		int c; cin >> c;
		if (c == 1) {
			int m; cin >> m;
			modify(cust-1, mp(m, -cust));
			cust++;
		}
		else if (c == 2) {
			while (t[ptr+n].ff == 0) ptr++;
			cout << ptr+1 << ' ';
			modify(ptr, mp(0, -1));
		}
		else {
			pii ans = query(0, n);
			// cout << "\nTEST: " << ans.ff << ' ' << ans.ss << endl;
			cout << -ans.ss << ' ';
			modify(-ans.ss-1, mp(0, -1));
		}
	}
	cout << endl;
	
}

