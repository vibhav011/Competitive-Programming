#include <iostream>
#include <algorithm>
#define ll long long int
using namespace std;

int compare(const void* ap, const void* bp) 
{ 
    // Typecasting 
    const ll* a = (ll*)ap; 
    const ll* b = (ll*)bp; 
  
    if (*a < *b) 
        return -1; 
    else if (*a > *b) 
        return 1; 
    else
        return 0; 
} 

int main () {
	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		int n,d, ans;
		cin >> n >> d;
		ll a[n];

		for (int i = 0; i < n; i++) cin >> a[i];

		sort(a, a+n);
		if (d > 3) ans  = 1;
		else {
			int ARR_SIZE = n;
			if (d == 2) {
				bool found = false;
				for (int i = 1; i < n; i++) {
					if (a[i] == a[i-1]) {found = true; break;}
				}
				if (found) ans = 0;
				else ans = 1;
			}
			if (d == 3) {
				bool found = false;
				for (int i = 2; i < n; i++) {
					if (a[i] == a[i-1] && a[i] == a[i-2]) {found = true; break;}
				}
				if (found) ans = 0;
				else {
					for (int i = 0; i < n && 2*a[i] <= a[n-1]; i++) {
						ll key = 2*a[i];
						ll* p1 = (ll*)bsearch(&key, a, ARR_SIZE, sizeof(a[0]), compare);
						if (p1) {
							found = true;
							break;
						}
					}
					if (found) ans = 1;
					else {
						for (int i = 1; i < n-1; i++) {
							if (a[i] == a[i-1]) {found = true; break;}
						}
						if (found) ans = 1;
						else ans = 2;
					}
				}
			}
		}
		
		printf("Case #%d: %d\n", cn, ans);
	}
}