#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

string s;
bool vis[7][7];
int ans, x, y;
map<char, pii> dir;
bool b1, b2, b3, b4, b5;

bool check(int x, int y) {
	if (x < 0 || x > 6 || y < 0 || y > 6) return false;
	return !vis[x][y];
}

void calc(int ind) {
	if (ind == 48) {
		ans++;
		return;
	}
	if (x == 6 && y == 0) return;
	string d (1, s[ind]);
	if (s[ind] == '?') d = "DULR";
	for (int i = 0; i < d.size(); i++) {
		pii p = dir[d[i]];
		if (check(x+p.ff, y+p.ss)) {
			x += p.ff;
			y += p.ss;
			vis[x][y] = true;
			b1 = check(x+p.ss, y+p.ff);
			b2 = check(x+p.ff+p.ss, y+p.ss+p.ff);
			b3 = check(x+p.ff, y+p.ss);
			b4 = check(x+p.ff-p.ss, y+p.ss-p.ff);
			b5 = check(x-p.ss, y-p.ff);
			if (!(
				(!b3 && b1 && b5) ||
				(!b2 && b1 && (b3 || b5)) ||
				(!b4 && b5 && (b3 || b1))
				))
					calc(ind+1);
			vis[x][y] = false;
			x -= p.ff;
			y -= p.ss;
		}
	}
	return;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> s;
	memset(vis, false, sizeof(vis));
	vis[0][0] = true;
	ans = x = y = 0;
	dir['D'] = mp(1, 0); dir['U'] = mp(-1, 0);
	dir['R'] = mp(0, 1); dir['L'] = mp(0, -1);
	calc(0);
	cout << ans << endl;
}

