#include <bits/stdc++.h>
#define ll long long int
using namespace std;
ll M = 1000000000;
string s;
int sz;

pair<ll, ll> move (int n, int e) {
	if (n == e) return make_pair(0, 0);
	int a = 0, b = 0;
	if (s[n] == 'N') b = -1;
	else if (s[n] == 'S') b = 1;
	else if (s[n] == 'W') a = -1;
	else if (s[n] == 'E') a = 1;

	if (a || b) {
		pair<ll, ll> ans = move(n+1, e);
		return make_pair((a + M + ans.first)%M, (b + M + ans.second)%M);
	}
	int d = s[n] - '0';
	int br = 0;
	int ind = n + 1;
	while (true) {
		if (s[ind] == '(') br++;
		if (s[ind] == ')') br--;
		if (!br) break;
		ind++;
	}
	pair<ll, ll> ans1 = move(n+2, ind);
	pair<ll, ll> ans2 = move(ind+1, e);
	return make_pair((d*ans1.first + ans2.first)%M, (d*ans1.second + ans2.second)%M);
}

int main () {
	int t; cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		cin >> s;
		sz = s.size();
		pair<ll, ll> ans;
		ans = move(0, sz);

		int w = (ans.first + M)%M + 1;
		int h = (ans.second + M)%M + 1;

		printf("Case #%d: %d %d\n", cn, w, h);
	}
}