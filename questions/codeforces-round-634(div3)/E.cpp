#include <bits/stdc++.h>
using namespace std;

int getMid(int s, int e) { 
	return s + (e - s) / 2; 
} 

int MaxUtil(int* st, int ss, int se, int l, int r, int node) { 
	if (l <= ss && r >= se) 
		return st[node]; 

	if (se < l || ss > r) 
		return -1; 

	int mid = getMid(ss, se); 
	
	return max(MaxUtil(st, ss, mid, l, r, 2 * node + 1), 
	MaxUtil(st, mid + 1, se, l, r, 2 * node + 2)); 
} 

void updateValue(int arr[], int* st, int ss, int se, int index, int value, int node) { 
	
	if (ss == se) { 
		arr[index] = value; 
		st[node] = value; 
	} 
	else { 
		int mid = getMid(ss, se); 
		
		if (index >= ss && index <= mid) 
			updateValue(arr, st, ss, mid, index, 
						value, 2 * node + 1); 
		else
			updateValue(arr, st, mid + 1, se, 
						index, value, 2 * node + 2); 
		
		st[node] = max(st[2 * node + 1], 
				st[2 * node + 2]); 
	} 
	return; 
} 
 
int getMax(int* st, int n, int l, int r) { 
	return MaxUtil(st, 0, n - 1, l, r, 0); 
} 

int constructSTUtil(int arr[], int ss, int se, int* st, int si) { 
	if (ss == se)  { 
		st[si] = arr[ss]; 
		return arr[ss]; 
	}

	int mid = getMid(ss, se); 
	
	st[si] = max(constructSTUtil(arr, ss, mid, st, si * 2 + 1), 
	constructSTUtil(arr, mid + 1, se, st, si * 2 + 2)); 
	
	return st[si]; 
} 

int* constructST(int arr[], int n)  { 
	int x = (int)(ceil(log2(n))); 
	int max_size = 2 * (int)pow(2, x) - 1; 
	int* st = new int[max_size]; 
	constructSTUtil(arr, 0, n - 1, st, 0); 
	return st; 
} 

int main () {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		int a[n];
		int freq[200]; memset(freq, 0, sizeof(freq));
		int mx = 0;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			freq[a[i]-1]++;
			mx = max(mx, freq[a[i]-1]);
		}
		for (int x = 1; x <= 200; x++) {
			if (!freq[x-1] || freq[x-1] == 1) continue;

			int* freq2 = constructST(freq, 200);
			updateValue(freq, freq2, 0, 199, x-1, 0, 0);

			int st = 0, en = n-1, cnt = 0;
			while (st < en) {
				while (a[st] != x && st < n) {
					updateValue(freq, freq2, 0, 199, a[st]-1, getMax(freq2, 200, a[st]-1, a[st]-1)-1, 0);
					st++;
				}
				
				while (a[en] != x && en >= 0) {
					updateValue(freq, freq2, 0, 199, a[en]-1, getMax(freq2, 200, a[en]-1, a[en]-1)-1, 0);
					en--;
				}
				if (st >= en) break;
				cnt++;
				mx = max(mx, 2*cnt + getMax(freq2, 200, 0, 199));
				st++; en--;
			}
			delete[] freq2;
		}
		cout << mx << endl;
	}
}