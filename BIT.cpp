#include <iostream>
using namespace std;

class BIT {
	int *bit;
	int N;

	void update(int x, int val) {
		int ind = x;
		while (ind <= N) {
			bit[ind] += val;
			ind += (ind & (-ind));
		}
	}

public:
	BIT(int ar[], int n) {
		bit = new int[n+1];
		N = n+1;
		for (int i = 1; i < N; i++) bit[i] = 0;
		for (int i = 1; i < N; i++) update(i, ar[i-1]);
	}

	int getSum(int x) {
		int ind = x+1;
		int sum = 0;
		while (ind > 0) {
			sum += bit[ind];
			ind = (ind & (ind-1));
		}
		return sum;
	}

	int getValue(int x) {
		return getSum(x) - getSum(x-1);
	}

	void changeElem(int x, int val) {
		update(x+1, val-getValue(x));
	}
};

int main() {
	int ar[6] = {5, 1, 7, 3, -4, 6};
	BIT b(ar, 6);
	b.changeElem(4, 4);
	for (int i=0; i < 6; i++) cout << b.getSum(i) << endl;

	return 0;
}