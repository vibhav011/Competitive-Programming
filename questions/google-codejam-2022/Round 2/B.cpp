#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
using namespace std;

bool matrix1[205][205];
bool matrix2[205][205];

int cust_round(double x) {
    int ret = (int)x;
    if (x - ret > 0.5) ret++;
    return ret;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";
		
		int r; cin >> r;

        if (r > 101) {
            cout << "0\n";
            continue;
        }

        for (int i = 0; i < 205; i++)
            for (int j = 0; j < 205; j++)
                matrix1[i][j] = matrix2[i][j] = false;

        for (int x = -r; x <= r; x++) {
            for (int y = -r; y <= r; y++) {
                if (cust_round(sqrt(x*x + y*y)) <= r) {
                    matrix1[x+r][y+r] = true;
                }
            }
        }

        for (int i = 0; i <= r; i++) {
            for (int x = -i; x <= i; x++) {
                int y = cust_round(sqrt(i*i - x*x));
                matrix2[x+r][y+r] = true;
                matrix2[x+r][-y+r] = true;
                matrix2[y+r][x+r] = true;
                matrix2[-y+r][x+r] = true;

            }
        }
        int ans = 0;
        for (int i = 0; i <= 2*r+1; i++) {
            for (int j = 0; j <= 2*r+1; j++) {
                if (matrix1[i][j] != matrix2[i][j]) ans++;
            }
        }
        cout << ans << '\n';
	}
}