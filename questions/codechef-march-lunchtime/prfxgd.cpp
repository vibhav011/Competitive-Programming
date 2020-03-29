#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while(t--) {
		string s; cin >> s;
		int k, x; cin >> k >> x;
		int freq[26];
		for (int i = 0; i < 26; i++) freq[i] = 0;
		int maxPref = 0;

		for (int i = 0; i < s.size(); i++) {
			freq[s[i]-'a']++;
			if (freq[s[i]-'a'] > x) {
				if (k > 0) {k--; maxPref--;}
				else break;
			}
			maxPref++;
		}
		cout << maxPref << endl;
	}
}