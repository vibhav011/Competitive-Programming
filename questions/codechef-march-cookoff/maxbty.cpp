// incorrect

#include <bits/stdc++.h>
using namespace std;
long long int sumAr[400000];
long long int maxAr[400000];
long long int minAr[400000];
int N;

void makeSumArr(int b[], int n) {

	for (int i = 0; i < n; i++) {
		// int del = b[i];
		// int a = 0, b = n, curr = 0;
		// while (true) {
		// 	sumAr[curr] += del;
			
		// 	if (a == b-1) break;
		// 	if (x < (a+b)/2) {
		// 		b = (a+b)/2;
		// 		curr = 2*curr + 1;
		// 	}
		// 	else {
		// 		a = (a+b)/2;
		// 		curr = 2*curr + 2;
		// 	}
		// }

		if (i == 0) sumAr[i] = b[i];
		else sumAr[i] = sumAr[i-1] + b[i];
	}
}
void makeMaxAr(int n) {
	for (int i = 0; i < n; i++) {
		int a = 0, b = n, curr = 0;
		while (true) {
			maxAr[curr] = max(sumAr[i], maxAr[curr]);
			
			if (a == b-1) break;
			if (i < (a+b)/2) {
				b = (a+b)/2;
				curr = 2*curr + 1;
			}
			else {
				a = (a+b)/2;
				curr = 2*curr + 2;
			}
		}
	}
}

void makeMinAr(int n) {
	for (int i = 0; i < n; i++) {
		int a = 0, b = n, curr = 0;
		while (true) {
			maxAr[curr] = min(sumAr[i], maxAr[curr]);
			
			if (a == b-1) break;
			if (i < (a+b)/2) {
				b = (a+b)/2;
				curr = 2*curr + 1;
			}
			else {
				a = (a+b)/2;
				curr = 2*curr + 2;
			}
		}
	}
}
long long int getMaxElem(int l, int r, int a, int b, int curr) {
	if (a == l && b == r) return maxAr[curr];

	if (r < (a+b)/2) return getMaxElem(l, r, a, (a+b)/2-1, 2*curr+1);
	if (l >= (a+b)/2) return getMaxElem(l, r, (a+b)/2, b, 2*curr+2);

	return max(getMaxElem(l, (a+b)/2-1, a, (a+b)/2-1, 2*curr+1), getMaxElem((a+b)/2, r, (a+b)/2, b, 2*curr+2));
}

long long int getMinElem(int l, int r, int a, int b, int curr) {
	if (a == l && b == r) return maxAr[curr];

	if (r < (a+b)/2) return getMaxElem(l, r, a, (a+b)/2-1, 2*curr+1);
	if (l >= (a+b)/2) return getMaxElem(l, r, (a+b)/2, b, 2*curr+2);

	return min(getMaxElem(l, (a+b)/2-1, a, (a+b)/2-1, 2*curr+1), getMaxElem((a+b)/2, r, (a+b)/2, b, 2*curr+2));
}

int main () {
	int t; cin >> t;

	while (t--) {
		int n, q; cin >> n >> q;
		int b[n];
		N = n;

		for (int i = 0; i < n; i++) cin >> b[i];

		for (int i = 0; i < 400000; i++) sumAr[i] = 0;
		for (int i = 0; i < 400000; i++) maxAr[i] = -100000000000001;
		for (int i = 0; i < 400000; i++) minAr[i] = 100000000000001;

		makeSumArr(b, n);
		makeMaxAr(n);
		makeMinAr(n);

		for (int i = 0; i < q; i++) {
			char c; int l, r;
			cin >> c >> l >> r;

			if (c == 'U') {

			}

			else {
				long long int mn, mx;
				if (l == 1) mn = 0;
				else mn = getMinElem(0, l-2, 0, n, 0);
				if (mn < 0) mn = 0;
				mx = getMaxElem(l-1, n-1, 0, n, 0);
				cout << mx-mn << endl;
			}
		}
	}

}