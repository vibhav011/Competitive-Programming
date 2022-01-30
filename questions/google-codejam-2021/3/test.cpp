#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<int> freq(10);

int solve(int k, bool fst) {
	if (k == 1) {
		for (int i = 0; i < 10; i++) if (freq[i] > 1) return 0;
		int a = -1, b = -1;
		for (int i = 0; i < 10; i++) {
			if (freq[i]) {
				if (a == -1) a = i;
				else b = i;
			}
		}
		return b-a;
	}
	int ans = 1000000000000000000LL;
	int i = (fst) ? 1 : 0;
	for (; i < 10; i++) {
		if (freq[i] > 1) {
			freq[i] -= 2;
			ans = min(ans, solve(k-1, false));
			freq[i] += 2;
		}
	}
	i = (fst) ? 1 : 0;
	vector<int> freq2 = freq;
	int x = 0, y = 0;
	for (; i < 9; i++) {
		for (int j = i+1; j < 10; j++) {
			if (freq2[i] && freq2[j]) {
				x = j;
				y = i;
				freq2[i]--;
				freq2[j]--;
				int ctr = 0, ind = 0;
				while (ctr < k-1) {
					while (freq2[ind] == 0) ind++;
					x = 10*x + ind;
					freq2[ind]--;
					ctr++;
				}
				ctr = 0; ind = 9;
				while (ctr < k-1) {
					while (freq2[ind] == 0) ind--;
					y = 10*y + ind;
					freq2[ind]--;
					ctr++;
				}
				// cout << "i: " << i << " j: " << j << " dif: " << (x-y) << '\n';
				ans = min(ans, x-y);
				freq2 = freq;
			}
		}
	}
	return ans;
}

int test2 (string d) {

	for (int i = 0; i < 10; i++) freq[i] = 0;
	int n = d.size();
	for (int i = 0; i < n; i++) freq[d[i]-'0']++;
	int ev = true;
	for (int i = 0; i < 10; i++) {
		if (freq[i]&1) {
			ev = false;
			break;
		}
	}
	if (ev) {
		return 0;
	}
	int x = 0, y = 0;
	if (n&1) {
		for (int i = 1; i < 10; i++) {
			if (freq[i]) {
				x = i;
				freq[i]--;
				break;
			}
		}
		int ctr = 0, ind = 0;
		while (ctr < n/2) {
			while (freq[ind] == 0) ind++;
			x = 10*x + ind;
			freq[ind]--;
			ctr++;
		}
		ctr = 0; ind = 9;
		while (ctr < n/2) {
			while (freq[ind] == 0) ind--;
			y = 10*y + ind;
			freq[ind]--;
			ctr++;
		}
		return x-y;
	}
	return solve(n/2, true);

}

int test1(string d) {
	for (int i = 0; i < 10; i++) freq[i] = 0;
	int n = d.size();
	for (int i = 0; i < n; i++) freq[d[i]-'0']++;
	int ev = true;
	for (int i = 0; i < 10; i++) {
		if (freq[i]&1) {
			ev = false;
			break;
		}
	}
	if (ev) {
		// cout << "0\n";
		// continue;
		return 0;
	}
	int x = 0, y = 0;
	if (n&1) {
		for (int i = 1; i < 10; i++) {
			if (freq[i]) {
				x = i;
				freq[i]--;
				break;
			}
		}
		int ctr = 0, ind = 0;
		while (ctr < n/2) {
			while (freq[ind] == 0) ind++;
			x = 10*x + ind;
			freq[ind]--;
			ctr++;
		}
		ctr = 0; ind = 9;
		while (ctr < n/2) {
			while (freq[ind] == 0) ind--;
			y = 10*y + ind;
			freq[ind]--;
			ctr++;
		}
		// cout << x-y << '\n';
		// continue;
		return x-y;
	}
	int ans = 1000000000000000000LL;
	vector<int> freq2 = freq;
	for (int i = 0; i < 9; i++) {
		for (int j = i+1; j < 10; j++) {
			if (freq2[i] && freq2[j]) {
				x = j;
				y = i;
				freq2[i]--;
				freq2[j]--;
				bool yay = false;
				for (int i = 1; i < 10; i++) {
					if (freq2[i] > 1) {
						freq2[i] = freq2[i]%2;
						yay = true;
					}
				}
				if (!yay && i==0) {
					freq2 = freq;
					continue;
				}
				if (yay) freq2[0] = freq2[0]%2;
				int lft = 0;
				for (int i = 0; i < 10; i++) lft += freq2[i];
				int ctr = 0, ind = 0;
				while (ctr < lft/2) {
					while (freq2[ind] == 0) ind++;
					x = 10*x + ind;
					freq2[ind]--;
					ctr++;
				}
				ctr = 0; ind = 9;
				while (ctr < lft/2) {
					while (freq2[ind] == 0) ind--;
					y = 10*y + ind;
					freq2[ind]--;
					ctr++;
				}
				// bool fsteq = false;
				// while (x%10 == y%10) {
				// 	if (x%10) {
				// 		fsteq = true;
				// 		x /= 10;
				// 		y /= 10;
				// 	}
				// 	else if (fsteq) {
				// 		x /= 10;
				// 		y /= 10;
				// 	}
				// 	else break;
				// }
				ans = min(ans, x-y);
				freq2 = freq;
			}
		}
	}
	freq2 = freq;
	for (int i = 0; i < 9; i++) {
		for (int j = i+1; j < 10; j++) {
			if (freq2[i] && freq2[j]) {
				x = j;
				y = i;
				freq2[i]--;
				freq2[j]--;
				int ctr = 0, ind = 0;
				while (ctr < n/2-1) {
					while (freq2[ind] == 0) ind++;
					x = 10*x + ind;
					freq2[ind]--;
					ctr++;
				}
				ctr = 0; ind = 9;
				while (ctr < n/2-1) {
					while (freq2[ind] == 0) ind--;
					y = 10*y + ind;
					freq2[ind]--;
					ctr++;
				}
				bool fsteq = false;
				while (x%10 == y%10) {
					if (x%10) {
						fsteq = true;
						x /= 10;
						y /= 10;
					}
					else if (fsteq) {
						x /= 10;
						y /= 10;
					}
					else break;
				}
				if (i != 0 || fsteq) ans = min(ans, x-y);
				freq2 = freq;
			}
		}
	}
	return ans;
}

signed main () {
	srand(time(0));
	string s(8, '#');
	while (true) {
		for (int i = 0; i < 8; i++) s[i] = (char) ((rand()%10) + '0');
		if (test1(s) != test2(s)) {
			cout << s << endl;
			break;
		}
	}
}