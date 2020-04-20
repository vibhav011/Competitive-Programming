#include <bits/stdc++.h>
using namespace std;

int main () {
	int n; cin >> n;
	printf("1 %d\n", n);
	for (int i = 1; i < n; i++) {
		printf("%d %d\n", i, i+1);
		//printf("%d %d\n", i, 2*i+1);
	}
	srand(time(0));
	for (int i = 1; i <= n; i++) printf("%d ", rand()%1000001);
	printf("\n%d\n", n);
	for (int i = 1; i <= n; i++) {
		printf("%d %d\n", rand()%n+1, rand()%n+1);
	}
}