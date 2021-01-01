#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int x, n;
	cin >> x >> n;
	int q;
	set<int>p;
	set<int>::iterator it;
	p.insert(0); p.insert(x);
	map<int, int> freq;
	map<int, int>::iterator it2;
	freq[x] = 1;

	while (n--) {
		cin >> q;
		it = p.lower_bound(q);
		int b = *it, a = *(--it);
		p.insert(q);
		if ((--freq[b-a]) == 0) freq.erase(b-a);
		freq[b-q]++;
		freq[q-a]++;
		it2 = freq.end(); it2--;
		cout << it2->ff << ' ';
	}
	cout << endl;
}

