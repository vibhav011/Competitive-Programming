#include <iostream>
#include <string>
using namespace std;

int main() {
	string txt = "AAABBAABBBBAABBAAAAAABBBAAB";
	string pat = "BBAA";

	int n = txt.size(), m = pat.size();

	//creating lps array

	int lps[m];
	lps[0] = 0;

	int k = 1, len = 0;

	while (k < m) {
		if (pat[len] == pat[k]) {
			len++;
			lps[k] = len;
			k++;
		}
		else {
			if (len > 0) len = lps[len - 1];
			else {
				lps[k] = 0;
				k++;
			}
		}
	}

	// for (int i = 1; i < m; i++) {
	// 	int j = i;
	// 	for (; j > -1; j--) {
	// 		if (pat.substr(0, j) == pat.substr(i+1-j, j)) break;
	// 	}
	// 	lps[i] = j;
	// }

	// Pattern Searching
	int i = 0, j = 0;

	while (i < n) {
		if (j == m) {
			cout << i-j << endl;
			j = lps[j-1];
		}
		else if (txt[i] == pat[j]) {
			i++; j++;
		}
		else {
			if (j > 0) j = lps[j-1];
			else i++;
		}
	}
}