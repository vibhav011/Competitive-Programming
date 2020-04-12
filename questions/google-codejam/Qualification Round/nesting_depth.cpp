#include <bits/stdc++.h>
using namespace std;
string digits;

string findS(int st, int en, int dep) {
	if (st == en) return "";
	int mn = digits[st] - '0';
	int ind = st;

	for (int i = st+1; i < en; i++) {
		if (digits[i] - '0' < mn) {
			mn = digits[i] - '0';
			ind = i;
		}
	}
	string a(mn-dep, '('); string b(mn-dep, ')');
	return (a + findS(st, ind, mn) + digits[ind] + findS(ind+1, en, mn) + b);
}

int main() {
	int t; cin >> t;
	for (int cn=1; cn <= t; cn++) {
		cin >> digits;
		printf("Case #%d: ", cn);
		cout << findS(0, digits.size(), 0) << endl;
	}
}