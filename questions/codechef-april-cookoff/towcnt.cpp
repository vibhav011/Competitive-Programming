#include <bits/stdc++.h>
#define ll long long int
using namespace std;

struct Obs {
	ll t, x, y, ind;
};

bool custSort (Obs &p, Obs &q) {
	return (p.x == q.x) ? (p.y < q.y) : (p.x < q.x);
}

int main () {
	int T; cin >> T;

	while (T--) {
		int h, n;
		cin >> h >> n;
		
		Obs ob[n];

		for (int i = 0; i < n; i++) {
			cin >> ob[i].t >> ob[i].x >> ob[i].y;
			ob[i].ind = i;
		}
		sort(ob, ob+n, custSort);
		int ans[n];
		fill (ans, ans+n, 0);

		for (int i = 0; i < n-1; i++) {
			ll yu = 1, xu = 0, yl = -1, xl = 0;

			for (int j = i+1; j < n; j++) {

				if (yu*(ob[j].x - ob[i].x) > xu*(ob[j].y - ob[i].y) || ob[i].x == ob[j].x) {
					if (yl*(ob[j].x - ob[i].x) < xl*(ob[j].y - ob[i].y) || ob[i].x == ob[j].x) {
						ans[ob[i].ind]++;
						ans[ob[j].ind]++;

						if (ob[j].t) {
							yu = ob[j].y - ob[i].y;
							xu = ob[j].x - ob[i].x;
						}
						else {
							yl = ob[j].y - ob[i].y;
							xl = ob[j].x - ob[i].x;
						}
					}
					else if (ob[j].t) break;
				}
				else if (!ob[j].t) break;
			}
		}

		for (int i = 0; i < n; i++) cout << ans[i] << ' ';
		cout << endl;
	}
}