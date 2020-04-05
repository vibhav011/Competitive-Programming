#include <bits/stdc++.h>
using namespace std;
int a[1000001];
int ans[1000001];
int backAns[1000001];
int inf, N;

int calcBackAns(int n) {
	if (backAns[n] != inf) return backAns[n];
	backAns[n] = max(a[n-1]+calcBackAns(n-1), a[n-2]+calcBackAns(n-2));
	return backAns[n];
}

int calcAns(int n) {
	if (ans[n] != inf) return ans[n];
	if (n == N) {
		ans[n] = calcBackAns(n);
	}
	else if (n == N-1) {
		ans[n] = max(calcBackAns(n), a[n+1]+calcBackAns(n+1));
	}
	else {
		ans[n] = max(calcBackAns(n), max(a[n+1]+calcAns(n+1), a[n+2]+calcAns(n+2)));
	}
	return ans[n];
}

int main () {
	int n, k; cin >> n >> k;
	N = n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	inf = 1<<31;
	fill(ans, ans+n+1, inf); fill(backAns, backAns+n+1, inf);
	backAns[1] = 0; backAns[2] = a[1];
	cout << calcAns(k) << endl;
}