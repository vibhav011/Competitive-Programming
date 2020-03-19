#include <bits/stdc++.h>
using namespace std;
const int p = 998244353;
long long int fac[100001];
long long int facPwr[100001]; 
int k;

int pwr(long long int x, int y) {
	long long int res = 1;	  // Initialize result 
  
	x = x % p;  // Update x if it is more than or 
				// equal to p 
  
	while (y > 0) { 
		// If y is odd, multiply x with result 
		if (y & 1) 
			res = (res*x) % p; 
  
		// y must be even now 
		y = y>>1; // y = y/2 
		x = (x*x) % p; 
	} 
	return res; 
}

int C(const int &n, const int &r)  {
	if (r == 0) return 1;
  	if (r > n) return 0; 
  
	return (((fac[n] * facPwr[r]) % p) * 
				facPwr[n-r]) % p;
}

struct Query {
	int l, r, qn;
	Query (int &a, int &b, int &c) {
		l = a; r = b; qn = c;
	}
};

bool sortQ(Query *q1, Query *q2) {
	return ((q1->l)/k == (q2->l)/k) ? ((q1->r)/k < (q2->r)/k) : (q1->l)/k < (q2->l)/k;
}

int main() {

	fac[0] = 1;
	for (int i=1 ; i<=100000; i++) fac[i] = (fac[i-1]*i)%p;

	facPwr[0] = 1;
	for (int i=1 ; i<=100000; i++) facPwr[i] = pwr(fac[i], p-2);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		int a[n];
		set<int> elems;

		for (int i = 0 ; i < n; i++) {
			scanf("%d", &a[i]);
			elems.insert(a[i]);
		}

		int sz = elems.size();

		map <int, int> nmap;
		int vn = 1;
		for (set<int>::iterator it = elems.begin(); it != elems.end(); it++) {
			nmap[*it] = vn;
			vn++;
		}
		for (int i = 0; i < n; i++) a[i] = nmap[a[i]];

		// vector<vector<int> > f(k+3, vector<int>(sz+1, 0));
		// for (int i = 0; i < n; i++) f[i/k][nmap[a[i]]]++;
		int freq[sz+1];
		for (int i = 1; i <= sz; i++) freq[i] = 0;

		vector<Query*> queries;

		int q; cin >> q;
		k = n/sqrt(q);
		if (!k) k = 1;

		for (int i = 1; i <= q; i++) {
			int l, r;
			scanf("%d %d", &l, &r);
			Query *qr = new Query(l, r, i);
			queries.push_back(qr);
		}

		sort(queries.begin(), queries.end(), sortQ);

 		int ans[q+1];
		int l = queries[0]->l;
		int r = queries[0]->r;
		for (int j = l; j <= r; j++) freq[a[j-1]]++;

		int s = 0;
		for (int j = 1; j <= sz; j++) s ^= freq[j];

		if (s == 0) ans[queries[0]->qn] = 0;
		else {
			long long int sum = 0;
			for (int j = 1; j <= sz; j++) {
				if (freq[j]) {
					int val = s^freq[j];
					sum = (sum + C(freq[j], val))%p;
				}
			}
			ans[queries[0]->qn] = sum;
		}

		for (int i = 1; i < q; i++) {
			int l1 = queries[i]->l;
			int r1 = queries[i]->r;

			if (l1 > l) for (int j = l; j != l1; j++) freq[a[j-1]]--;
			else for (int j = l-1; j != l1-1; j--) freq[a[j-1]]++;

			if (r1 > r) for (int j = r+1; j != r1+1; j++) freq[a[j-1]]++;
			else for (int j = r; j != r1; j--) freq[a[j-1]]--;

			int s = 0;
			for (int j = 1; j <= sz; j++) s ^= freq[j];

			if (s == 0) ans[queries[i]->qn] = 0;
			else {
				long long int sum = 0;
				for (int j = 1; j <= sz; j++) {
					if (freq[j]) {
						int val = s^freq[j];
						sum += C(freq[j], val);
						sum = sum % p;
					}
				}
				ans[queries[i]->qn] = sum;
			}
			l = l1; r = r1;
		}

		for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);

	}
}