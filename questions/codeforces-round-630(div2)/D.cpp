#include <iostream>
using namespace std;

int main() {
	int k; cin >> k;
	int k2 = k;
	int n = 0;
	while (k2 > 0) {
		n++;
		k2 = k2 >> 1;
	}
	int z = 0;
	int p = 1 << n;
	printf("3 4\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n", p+k, k, k, z, p, 0, k, 0, p, p, p+k, k);

	return 0;
}