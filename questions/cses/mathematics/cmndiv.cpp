#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

const ll mod = 1e9+7;

int main () {
	vector<int> cnt(1000001);

	int n; cin >> n;
	int a, sq;
	for (int i = 0; i < n; i++) {
		cin >> a;
		if (a==1) cnt[1]++;
		else {
			sq = sqrt(a);
			for (int j = 1; j <= sq; j++) {
				if (a%j == 0) {
					cnt[j]++;
					cnt[a/j]++;
				}
			}
			if (sq*sq == a) cnt[sq]--;
		}
	}
	for (int j = 1000000; j > 0; j--) {
		if (cnt[j] > 1) {
			cout << j << endl;
			break;
		}
	}
}