#include <bits/stdc++.h>
using namespace std;

struct Point {
	double x, y, x5;
	Point *buddy;
	bool bottom, horizontal;
	int qn;
	Point () {buddy = NULL; horizontal = false;}
};

bool compareHeight(Point* p1, Point* p2) {
	if (p1->y == p2->y) {
		if (p1->horizontal != p2->horizontal) {
			if (p1->horizontal) {
				if (p2->bottom) return false;
				else return true;
			}
			else {
				if (p1->bottom) return true;
				else return false;
			}
		}
		else {
			return p1->bottom;
		}
	}
	return (p1->y < p2->y);
}

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

	int t; cin >> t;

	while (t--) {
		int n, q;
		cin >> n >> q;
		int a[n];
		vector<Point*> pts;

		for (int i = 0; i < n; i++) cin >> a[i];

		for (int i = 0; i < n-1; i++) {
			Point *p1, *p2;
			p1 = new Point();
			p2 = new Point();
			p1->x = i+1.5; p1->y = a[i];
			p2->x = i+1.5; p2->y = a[i+1];
			if (a[i+1] >= a[i]) {
				p1->bottom = true; p2->bottom = false;
			}
			else {p2->bottom = true; p1->bottom = false;}
			p1->buddy = p2;
			p2->buddy = p1;
			pts.push_back(p1);
			pts.push_back(p2);
		}

		int q1 = q;

		while (q1--) {
			int x1, x2, y0;
			cin >> x1 >> x2 >> y0;

			Point *p1;
			p1 = new Point();
			p1->x = x1; p1->x5 = x2; p1->y = y0;
			p1->horizontal = true;
			p1->qn = q-q1;
			pts.push_back(p1);
		}

		vector <int> ans (q, 0);

		sort(pts.begin(), pts.end(), compareHeight);

		set <int> ycords;

		int ar2[n-1];
		for (int i = 0; i < n-1; i++) ar2[i] = 0;
		BIT activepts(ar2, n-1);

		for (int i = 0; i < pts.size(); i++) ycords.insert(pts[i]->y);

		set<int>::iterator it;

		int ind = 0;

		for (it = ycords.begin(); it != ycords.end(); it++) {
			int ys = *it;
			while (pts[ind]->y == ys) {
				Point* pnt = pts[ind];
				if (!pnt->horizontal) {
					if (pnt->bottom) activepts.changeElem(pnt->x-1.5, 1);
					else activepts.changeElem(pnt->buddy->x-1.5, 0);
				}
				else {
					int x1 = pnt->x;
					int x2 = pnt->x5;

					ans[(pnt->qn)-1] += activepts.getSum(x2-2) - ((x1 > 1) ? activepts.getSum(x1-2) : 0);
				}
				ind++;
				if (ind == pts.size()) break;
			}
		}
		for (int i = 0; i < q; i++) cout << ans[i] << endl;
	}
}