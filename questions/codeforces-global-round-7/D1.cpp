#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(string s) {
	int a = 0, b = s.size()-1;

	while (a < b) {
		if (s[a] != s[b]) return false;
		a++; b--;
	}
	return true;
}

string maxPalin(string s) {
	int n2 = s.size();
	if (n2 == 1) return s;
	
	int n = n2-1;
	while (n > 0) {
		if (isPalindrome(s.substr(0, n))) return s.substr(0, n);
		if (isPalindrome(s.substr(n2-n, n))) return s.substr(n2-n, n);
		n--;		
	}
}

int main() {
	int T; cin >> T;

	while (T--) {
		string s; cin >> s;
		int a = 0, b = s.size()-1;

		string c1 = "", c2 = "";

		while (a < b) {
			if (s[a] == s[b]) {
				c1 = c1 + s[a];
				c2 = s[b] + c2;
			}
			else break;
			a++; b--;
		}
		if (a > b) cout << (c1+c2) << endl;
		else cout << (c1 + maxPalin(s.substr(a, b-a+1)) + c2) << endl;
	}
}