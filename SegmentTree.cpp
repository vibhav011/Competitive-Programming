#include <iostream>
using namespace std;

int arSum(int ar[], int s, int e) {
	int sum = 0;
	for (int i=s; i < e; i++) sum += ar[i];
	return sum;
}

class SegmentTree {
	int value;
	int l, r;
	SegmentTree *ltree, *rtree;

	// void update(int ar[], int s, int e, int root) {
	// 	if (e-s == 1) st[root] = ar[s];
	// 	else {
	// 		st[root] = arSum(ar, s, e);
	// 		update(ar, s, (s+e)/2, 2*root+1);
	// 		update(ar, (s+e)/2, e, 2*root+2);
	// 	}
	// }

public:

	SegmentTree(int ar[], int a, int b) {
		ltree = rtree = NULL;
		value = arSum(ar, a, b);
		l = a; r = b;
		if (a != b-1) {
			ltree = new SegmentTree(ar, a, (a+b)/2);
			rtree = new SegmentTree(ar, (a+b)/2, b);
		}
	}

	int getSum(int x) {
		if (x == r-1) return value;
		if (x < (l+r)/2) return ltree->getSum(x);
		return ltree->value + rtree->getSum(x);
	}
};

int main() {
	int ar[6] = {5, 1, 7, 3, -4, 6};
	SegmentTree s(ar, 0, 6);
	for (int i=0; i < 6; i++) cout << s.getSum(i) << endl;
}