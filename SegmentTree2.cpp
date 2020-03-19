#include <iostream>
using namespace std;

int arSum(int ar[], int s, int e) {
	int sum = 0;
	for (int i = s; i < e; i++) sum += ar[i];
	return sum;
}

class SegmentTree {
	int *st;
	int N;

	void update(int ar[], int a, int b, int root) {
		st[root] = arSum(ar, a, b);

		if (a != b-1) {
			update(ar, a, (a+b)/2, 2*root+1);
			update(ar, (a+b)/2, b, 2*root+2);
		}
	}

public:

	SegmentTree(int ar[], int n) {
		st = new int[4*n];
		N = n;
		update(ar, 0, n, 0);
	}

	int getSum(int x) {
		int a = 0, b = N, curr = 0;
		int sum = 0;
		while (true) {
			if (x == b-1) {
				sum += st[curr]; break;
			}
			if (a == b-1) break;
			if (x < (a+b)/2) {
				b = (a+b)/2;
				curr = 2*curr + 1;
			}
			else {
				sum += st[2*curr + 1];
				a = (a+b)/2;
				curr = 2*curr + 2;
			}
		}
		return sum;
	}
	void changeElem(int x, int val) {
		int del = val - (getSum(x) - getSum(x-1));
		int a = 0, b = N, curr = 0;
		while (true) {
			st[curr] += del;
			
			if (a == b-1) break;
			if (x < (a+b)/2) {
				b = (a+b)/2;
				curr = 2*curr + 1;
			}
			else {
				a = (a+b)/2;
				curr = 2*curr + 2;
			}
		}
	}
};

int main() {
	int ar[6] = {5, 1, 7, 3, -4, 6};
	SegmentTree s(ar, 6);
	for (int i=0; i < 6; i++) cout << s.getSum(i) << endl;
	s.changeElem(3, 0);
	for (int i=0; i < 6; i++) cout << s.getSum(i) << endl;

}