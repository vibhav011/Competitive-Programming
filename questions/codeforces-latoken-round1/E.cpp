#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define fio fflush(stdout)
#define Tulip signed main

using namespace std;

int ran(int a, int b, int k) {
	int ans = 0;
	int n = b-a+1;
	for (int i = 0; i < n/k; i++) {
		cout << "?";
		for (int j = 0; j < k; j++) {
			cout << " " << i*k+j+a;
		}
		cout << endl; fio;
		int temp; cin >> temp;
		ans ^= temp;
	}
	return ans;
}

int ran2(int a, int sz, int n, int k) {
	int ans = 0, temp;
	if (a > n) return 0;
	cout << "?";
	for (int i = a; i <= a+sz/2-1; i++) cout << " " << i;
	int i = 1, times = 0;
	while (times < k-sz/2) {
		if (i < a || i >= a+sz) {
			times++;
			cout << " " << i;
		}
		i++;
	}
	cout << endl; fio;
	cin >> temp;
	ans ^= temp;

	cout << "?";
	for (int i = a; i <= a+sz/2-1; i++) cout << " " << i+sz/2;
	i = 1, times = 0;
	while (times < k-sz/2) {
		if (i < a || i >= a+sz) {
			times++;
			cout << " " << i;
		}
		i++;
	}
	cout << endl; fio;
	cin >> temp;
	ans ^= temp;

	return ans;
}

void Tulip0(int n, int k, int def = 0) {
	if (n > 2*k) {
		int u = 2*k;
		int ans = def^ran(1, u*(n/u), k);
		ans ^= ran2(u*(n/u)+1, n%u, n, k);
		
		cout << "! " << ans << endl; fio;
		return;
	}
	int temp, ans = def;
	if (k%2 == 0) {
		ans = ran(1, k, k);
		ans ^= ran2(k+1, n-k, n, k);

		cout << "! " << ans << endl; fio;
		return;
	}

	int ev = 2*n-2*k;
	for (int i = 1; i <= n/ev; i++) ans ^= ran2((i-1)*ev+1, ev, n, k);
	ans ^= ran2(ev*(n/ev)+1, n%ev, n, k);
	cout << "! " << ans << endl; fio;
	return;
}

void Tulip1(int n, int k) {
	int ans = 0, temp;
	if ((n%k)%2 == 0) {
		int n2 = n;
		n = k + (n%k);

		ans ^= ran(1, k, k);
		ans ^= ran2(k+1, n-k, n, k);
		ans ^= ran(n+1, n2, k);
		cout << "! " << ans << endl; fio;

		return;
	}

	ans = ran(n-k+1, n, k);

	if (n > 2*k) {
		Tulip0(n-k, k, ans);
		return;
	}

	int ev = min(2*k, 2*n-2*k);

	for (int i = 1; i <= (n-k)/ev; i++) ans ^= ran2((i-1)*ev+1, ev, n, k);
	ans ^= ran2(ev*((n-k)/ev)+1, (n-k)%ev, n, k);
	cout << "! " << ans << endl; fio;
	return;
}

Tulip () {
	int n, k;
	cin >> n >> k;
	if (n%k == 0) {
		int ans = ran(1, n, k);
		cout << "! " << ans << endl; fio;
		return 0;
	}
	if (n%2 == 1 && k%2 == 0) {
		cout << -1 << endl; fio;
		return 0;
	}
	if (!(n&1)) Tulip0(n, k);
	else Tulip1(n, k);
}

