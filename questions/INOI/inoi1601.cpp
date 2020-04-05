#include <bits/stdc++.h>
#define N 100001
using namespace std;

int a[N], pp[N];

int calcMax(int aa, int bb) {
	int mx = 1 << 31;
	int mn = 1 << 30;
	int cur = aa;
	int i_mn, p = 0, i_mx, q = 0, cnt = 0;

	while (cur != bb) {
		cnt++;
		if (a[cur] < mn) {
			mn = a[cur];
			i_mn = cur;
			p = cnt;
		}
		if (a[cur] > mx) {
			mx = a[cur];
			i_mx = cur;
			q = cnt;
		}
		cur = pp[cur];
	}
	if (cnt <= 1) return 1<<31;
	else if (q >= p) return a[i_mx] - a[i_mn];
	else {
		int cur = aa;
		int mn2 = 1 << 30, i_mn2;
		while (cur != i_mx) {
			if (a[cur] < mn2) {
				mn2 = a[cur];
				i_mn2 = cur;
			}
			cur = pp[cur];
		}
		cur = pp[i_mn];
		int mx2 = 1 << 31, i_mx2;
		while (cur != bb) {
			if (a[cur] > mx2) {
				mx2 = a[cur];
				i_mx2 = cur;
			}
			cur = pp[cur];
		}
		return max(calcMax(pp[i_mx], i_mn), max(a[i_mx2]-a[i_mn], a[i_mx]-a[i_mn2]));
	}
}

int main() {
	int n; cin >> n;
	set <int> leafs;
	for (int i = 1; i <= n; i++) leafs.insert(i);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {cin >> pp[i]; leafs.erase(pp[i]);}

	int mx = 1<<31;
	for (set<int>::iterator it = leafs.begin(); it != leafs.end(); it++) {
		mx = max(mx, calcMax(*it, -1));
	}
	cout << mx << endl;
}