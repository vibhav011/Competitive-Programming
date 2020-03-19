#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
	int t; cin >> t;

	while (t--) {
		int n, m;
		cin >> n >> m;

		int f[n], p[n];

		for (int i = 0; i < n; i++) cin >> f[i];
		for (int i = 0; i < n; i++) cin >> p[i];

		int cost[m];
		for (int i=0; i < m; i++) cost[i] = -1;

		for (int i = 1; i <= m; i++) {
			for (int j = 0; j < n; j++) {
				if (f[j] == i) cost[i-1] = (cost[i-1] == -1) ? p[j] : cost[i-1] + p[j];
			}
		}

		int min = -1;
		for (int i = 0; i < m; i++) {
			if (cost[i] != -1) {
				if (min == -1) min = cost[i];
				else min = (min < cost[i]) ? min : cost[i];
			}
		}
		cout << min << endl;
	}

	return 0;
}