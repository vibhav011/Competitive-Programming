#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if ((n*m)%2 == 0) {
					if ((n&1) == 0) {
						if (i == 1 && j == 0) {printf("B"); continue;}
						if (i&1) printf("W");
						else printf("B");
					}
					else {
						if (i == 0 && j == 1) {printf("B"); continue;}
						if (j&1) printf("W");
						else printf("B");
					}
				}
				else {
					if (i != n-1) {
						if (i&1) printf("W");
						else printf("B");
					}
					else {
						if (j&1) printf("W");
						else printf("B");
					}
				}
			}
			printf("\n");	
		}
	}

	return 0;
}