#include <bits/stdc++.h>
using namespace std;
int n, k, sum;

string findAns(vector<int> &f, int s, vector<char> &ch) {
	if (s == f.size()-1) {
		if (!(sum%k)) {
			if (f[s]%k) return string(f[s]/k+1, ch[s]);
			return string(f[s]/k, ch[s]);
		}
		return string(1, ch[s]);
	}
	if (!(sum%k)) {
		if (sum >= k) {
			string str;
			for (int i = s; i < f.size(); i++) str += string(f[i], ch[i]);
			return str;
		}
		if (f[s] <= k) {
			sum += f[s];
			return string(f[s]/k, ch[s]) + findAns(f, s+1, ch);
		}
		f[s] -= k;
		sum += k;
		return string(1, ch[s]) + findAns(f, s, ch);
	}
	
	sum += f[s];
	if (sum >= k) return string(1, ch[s]);
	return findAns(f, s+1, ch);
	
}

int main () {
	int t; cin >> t;

	while (t--) {
		cin >> n >> k;
		int freq[26];
		fill(freq, freq+26, 0);

		for (int i = 0; i < n; i++) {
			char c; cin >> c;
			freq[c - 'a']++;
		}
		vector<int> f;
		vector<char> ch;
		for (int i = 0; i < 26; i++) {
			if (freq[i]) {
				f.push_back(freq[i]);
				ch.push_back((char)(i+'a'));
			}
		}
		sum = 0;
		cout << findAns(f, 0, ch) << endl;
		
	}
}