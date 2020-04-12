#include <bits/stdc++.h>
using namespace std;
int type[51], ar[101];
int checker = 0, checker_type = 0, _n, cur_ind;

string toStr(int n) {
	string ans = "";
	for (int i = 1; i < n; i++) {
		if (ar[i] == 1) ans += '1';
		else ans += '0';
	}
	return ans;
}

void comp(int n) {
	for (int i = 1; i < n; i++) {
		ar[i] = 1-ar[i];
	}
	return;
}
void rev(int n) {
	for (int i = 1; i <= n/2; i++) {
		swap(ar[i], ar[n-i]);
	}
	return;
}

void updateAr(int n, int step) {
	if (step == 3) return;
	if (step == 0) comp(n);
	else if (step == 2) rev(n);
	else {comp(n); rev(n);}
}

void solve () {
	if (cur_ind > _n/2) return;

	if (checker == 0) {
		int x;
		cout << 1 << endl; fflush(stdout);
		cin >> x;
		if (x != ar[1]) updateAr(_n, 0);
		cout << 1 << endl; fflush(stdout);
		cin >> x;
		for (int i = cur_ind; i <= cur_ind+3 && i <= _n/2; i++) {
			cout << i << endl; fflush(stdout);
			cin >> ar[i];
			cout << _n-i << endl; fflush(stdout);
			cin >> ar[_n-i];
			if (ar[i] == ar[_n-i]) type[i] = 1;
			else type[i] = 2;
			if (checker == 0) {
				if (type[i] != type[i-1]) {
					checker = i-1;
					checker_type = type[i-1];
				}
			}
		}
	}
	else {
		int x, y;
		cout << checker << endl; fflush(stdout);
		cin >> x;
		cout << checker+1 << endl; fflush(stdout);
		cin >> y;
		int step = ((3-checker_type)*(x==ar[checker]) + checker_type*(y==ar[checker+1]));
		updateAr(_n, step);
		for (int i = cur_ind; i <= cur_ind+3 && i <= _n/2; i++) {
			cout << i << endl; fflush(stdout);
			cin >> ar[i];
			cout << _n-i << endl; fflush(stdout);
			cin >> ar[_n-i];
		}
	}
	cur_ind += 4;
	solve();
}

int main () {
	int t, b; cin >> t >> b;
	_n = b+1;

	while (t--) {
		
		memset(type, 0, sizeof(type));
		checker = checker_type = 0;
		for (int i = 1; i <= 5; i++) {
			cout << i << endl; fflush(stdout);
			cin >> ar[i];
			cout << _n-i << endl; fflush(stdout);
			cin >> ar[_n-i];
			if (ar[i] == ar[_n-i]) type[i] = 1;
			else type[i] = 2;
			if (i > 1 && checker == 0) {
				if (type[i] != type[i-1]) {
					checker = i-1;
					checker_type = type[i-1];
				}
			}
		}
		cur_ind = 6;
		solve();
		cout << toStr(_n) << endl;
		fflush(stdout);

		char c; cin >> c;
		if (c == 'N') break;
	}
}