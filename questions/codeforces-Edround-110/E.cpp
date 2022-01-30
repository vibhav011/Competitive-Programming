#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 998244353;

struct Node {
	int my_num, my_ind;
	vector<Node*> child;
	Node* par;
	vector<int> a, c;

	Node(int num, int aa, int cc, Node* p) {
		this->my_num = num;
		this->a = vector<int>(1, aa);
		this->c = vector<int>(1, cc);
		this->par = p;
	}
};

Node* nodes[300005];

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int q, a0, c0;
	// cin >> q >> a0 >> c0;

}

