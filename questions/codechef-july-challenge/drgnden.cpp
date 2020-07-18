#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int n, q;
const int M = 2e5+5;
int h[M], h2[M];
pair<int, pii> lst[2*M], rst[2*M];

void fill1() {
	for (int i = n-1; i > 0; i--) {
		rst[i].ss.ff = rst[i<<1].ss.ff;
		rst[i].ss.ss = rst[i<<1].ss.ss;
		rst[i].ff = rst[i<<1].ff;
		if (h[rst[i<<1|1].ss.ff] > h[rst[i<<1].ss.ss]) {
			rst[i].ss.ss = rst[i<<1|1].ss.ss;
			rst[i].ff += rst[i<<1|1].ff;
		}
	}
}

void fill2() {
	for (int i = n-1; i > 0; i--) {
		lst[i].ss.ff = lst[i<<1].ss.ff;
		lst[i].ss.ss = lst[i<<1].ss.ss;
		lst[i].ff = lst[i<<1].ff;
		if (h2[lst[i<<1|1].ss.ff] > h2[lst[i<<1].ss.ss]) {
			lst[i].ss.ss = lst[i<<1|1].ss.ss;
			lst[i].ff += lst[i<<1|1].ff;
		}
	}
}

void update(int k, int v) {
	int k2 = k;
	k += n-1;
	rst[k].ff = v;
	while (k > 1) {
		k = k>>1;
		rst[k].ss.ff = rst[k<<1].ss.ff;
		rst[k].ss.ss = rst[k<<1].ss.ss;
		rst[k].ff = rst[k<<1].ff;
		if (h[rst[k<<1|1].ss.ff] > h[rst[k<<1].ss.ss]) {
			rst[k].ss.ss = rst[k<<1|1].ss.ss;
			rst[k].ff += rst[k<<1|1].ff;
		}
	}
	k = 2*n-k2;
	lst[k].ff = v;
	while (k > 1) {
		k = k>>1;
		lst[k].ss.ff = lst[k<<1].ss.ff;
		lst[k].ss.ss = lst[k<<1].ss.ss;
		lst[k].ff = lst[k<<1].ff;
		if (h2[lst[k<<1|1].ss.ff] > h2[lst[k<<1].ss.ss]) {
			lst[k].ss.ss = lst[k<<1|1].ss.ss;
			lst[k].ff += lst[k<<1|1].ff;
		}
	}
}

ll ans(int a, int b) {
	pair<int, pii> *st;
	int *hh;
	if (a > b) {
		a = n+1-a;
		b = n+1-b;
		st = lst;
		hh = h2;
	}
	else {
		st = rst;
		hh = h;
	}

	// cout << "Heights: " << hh[a] << ' ' << hh[b] << endl;
	
	ll res = 0;

	int lastl = 0, lastr = 0;
	for (a += n-1, b += n; a < b; a >>= 1, b >>= 1) {
		// if (b-a <= 2) {
		// 	if (b-a == 2) {
		// 		if (a&1) {
		// 			res += st[a].ff;
		// 			res += st[b-1].ff;
		// 			if (hh[st[a].ss.ss] >= hh[st[b-1].ss.ff]) return -1;
		// 			break;
		// 		}
		// 	}
		// 	else {
		// 		res += st[a].ff;
		// 		if (a&1) {
		// 			if (lastr) {
		// 				if (hh[st[a].ss.ss] >= hh[st[lastr].ss.ff]) return -1;
		// 			}
		// 		}
		// 		else {
		// 			if (lastl) {
		// 				if (hh[st[lastl].ss.ss] >= hh[st[a].ss.ff]) return -1;
		// 			}
		// 		}
		// 		break;
		// 	}
		// }

		if (a&1) {
			if (lastl) {
				if (hh[st[lastl].ss.ss] >= hh[st[a].ss.ff]) return -1;
			}
			lastl = a;
			res += st[a++].ff;
		}
		if (b&1) {
			if (lastr) {
				if (hh[st[lastr].ss.ff] <= hh[st[b-1].ss.ss]) return -1;
			}
			lastr = b-1;
			res += st[--b].ff;
		}
	}
	if (lastl && lastr) {
		if (hh[st[lastl].ss.ss] >= hh[st[lastr].ss.ff]) return -1;
	}
	return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> q;

	for (int i = 1; i<= n; i++) {
		cin >> h[i];
		h2[n+1-i] = h[i];
	}
	for (int i = 1; i<= n; i++) {
		cin >> rst[i+n-1].ff;
		rst[i+n-1].ss.ff = i;
		rst[i+n-1].ss.ss = i;
		lst[2*n-i].ff = rst[i+n-1].ff;
		lst[2*n-i].ss.ff = n-i+1;
		lst[2*n-i].ss.ss = n-i+1;
	}
	fill1();
	fill2();

	// cout << "rst:\n";
	// for (int i = 1; i <= 2*n-1; i++) printf("%d : (%d, (%d, %d))\n", i, rst[i].ff, rst[i].ss.ff, rst[i].ss.ss);
	// cout << "\nlst:\n";
	// for (int i = 1; i <= 2*n-1; i++) printf("%d : (%d, (%d, %d))\n", i, lst[i].ff, lst[i].ss.ff, lst[i].ss.ss);
	// cout << endl;

	while(q--) {
		int t, b, c;
		cin >> t >> b >> c;
		if (t == 1) {
			update(b, c);
			continue;
		}
		cout << ans(c, b) << endl;
	}
	return 0;
}

