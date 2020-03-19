#include <iostream>
using namespace std;

int main() {
	int n; cin >> n;
	int b[n];
	for (int i = 0; i < n; i++) cin >> b[i];

	int a[n];
	a[0] = b[0];
	int max = a[0];

	cout << a[0] << ' ';
	for (int i = 1; i < n; i++) {
		a[i] = max + b[i];
		if (max < a[i]) max = a[i];
		cout << a[i] << ' ';
	}
	cout << endl;
}