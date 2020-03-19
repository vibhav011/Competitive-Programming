#include <iostream>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	
	int tree[(1 << (n+1))-1];

	for (int i = 0; i < (1 << (n+1)); i++) tree[i] = 0;
	for (int i = (1 << n) - 1; i < (1 << (n+1))-1; i++) cin >> tree[i];	

	for (int i = (1 << n)-1; i < (1 << (n+1))-1; i+=2) {
		int curr = (i-1)/2;
		bool OR = true;

		while (true) {
			if (OR) tree[curr] = tree[2*curr+1] | tree[2*curr+2];
			else tree[curr] = tree[2*curr+1] ^ tree[2*curr+2];
			if (curr == 0) break;
			curr = (curr-1)/2;
			OR = !OR;
		}
	}

	for (int i = 0; i < m ; i++) {
		int p, b;
		cin >> p >> b;
		tree[p+(1<<n)-2] = b;

		int curr = (p+(1<<n)-3)/2;
		bool OR = true;

		while (true) {
			if (OR) tree[curr] = tree[2*curr+1] | tree[2*curr+2];
			else tree[curr] = tree[2*curr+1] ^ tree[2*curr+2];
			if (curr == 0) break;
			curr = (curr-1)/2;
			OR = !OR;
		}
		cout << tree[0] << endl;
	}
}