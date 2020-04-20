#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const ll p = 998244353;
string l;

ll pwr(ll x, ll y) {
	ll res = 1;
	x = x%p;
	while (y > 0) {
		if (y&1) res = (res*x)%p;

		y = y>>1;
		x = (x*x)%p;
	}
	return res;
}

ll countHashes(int s, int e) {
	int chars = 0;
	for (int i = s; i < e; i++) {
		if (l[i] == '#') chars++;
	}
	return pwr(2, chars);
}

ll calcPos(int s, int e) {
	if (l[s] == '#') return (ll)1;

	int brac = 0;
	int i = s+1;
	for (; i < e-1; i++) {
		if (l[i] == '(') brac++;
		else if (l[i] == ')') brac--;
		if (brac == 0) break;
	}
	char op = l[i+1];

	ll a1b1 = countHashes(s+1, i+1), a2b2 = countHashes(i+2, e-1);
	ll a1 = calcPos(s+1, i+1), a2 = calcPos(i+2, e-1);
	ll b1 = (p+a1b1-a1)%p, b2 = (p+a2b2-a2)%p;
	
	if (op == '&') {
		return ((a1b1*a2b2)%p + p - (b1*b2)%p)%p;
	}
	if (op == '|') {
		return (a1*a2)%p;
	}
	if (op == '^') {
		return ((a1*a2)%p + (b1*b2)%p)%p;
	}
}

int main() {
	int t; cin >> t;
	while (t--) {
		cin >> l;

		int n = l.size();
		ll dd = countHashes(0, n);
		ll den = pwr(dd, 2*p-4);
		ll a, b, c;
		
		a = calcPos(0, n); b = (p+dd-a)%p;
		c = (a*b)%p;
		a = (a*a)%p; b = (b*b)%p;
		//printf("%lld %lld %lld %lld / %lld\n", a, b, c, c, (dd*dd)%p);

		cout << (a*den)%p << ' ' << (b*den)%p << ' ' << (c*den)%p << ' ' << (c*den)%p << endl;
	}
}