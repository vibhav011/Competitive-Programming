#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define fio fflush(stdout)

using namespace std;

ll MOD = 998244353;

ll pwr(ll x, ll y, ll mod = MOD)
{
    ll res = 1;
    x = x % mod;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % mod;

        y = y >> 1;
        x = (x * x) % mod;
    }
    return res;
}

inline ll addmod(ll a, ll b)
{
    return ((a + b) % MOD);
}

inline ll mulmod(ll a, ll b)
{
    return ((a * b) % MOD);
}

bool check_composite(int n, int a, int d, int s)
{
    int x = pwr(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++)
    {
        x = x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

const int first12prime[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

bool isPrime(int n)
{ // O(log n) time complexity
    if (n < 2)
        return false;

    int r = 0;
    int d = n - 1;
    while ((d & 1) == 0)
    {
        d >>= 1;
        r++;
    }

    for (int i = 0; i < 12; i++)
    {
        int a = first12prime[i];
        if (n == a)
            return true;

        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

const int PM = 2e5 + 5;

vector<int> primes;
vector<bool> is_comp;

void sieve()
{
    is_comp.resize(PM, false);
    for (int i = 2; i < PM; i++)
    {
        if (!is_comp[i])
            primes.pb(i);
        for (int j = 0; j < primes.size() && primes[j] * i < PM; j++)
        {
            is_comp[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

inline int sfunc(int a, int b)
{
    return a + b;
}

int n;      // array size
int *stree; // stree = new int[2 * n]

void build()
{ // build the tree
    for (int i = n - 1; i > 0; --i)
        stree[i] = sfunc(stree[i << 1], stree[i << 1 | 1]);
}

void modify(int p, int value)
{ // set value at position p
    for (stree[p += n] = value; p > 1; p >>= 1)
        stree[p >> 1] = sfunc(stree[p], stree[p ^ 1]);
}

int query(int l, int r)
{                // query on interval [l, r)
    int res = 0; // DEFAULT
    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res = sfunc(res, stree[l++]);
        if (r & 1)
            res = sfunc(res, stree[--r]);
    }
    return res;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    for (int cn = 1; cn <= t; cn++)
    {
        int state = 0;
        /*
        0 - default

        1 - adj
        2 - leave 1
        3 - leave 2
        4 - opp
        */

        int state2 = 0;
        /*
        0 - default

        1 - 4
        2 - 3-1
        3 - 3--1
        4 - 2-2
        5 - 2--2
        6 - 2-1-1
        7 - 2--1-1
        8 - 1-1-1-1
        */
        cout << "00000000" << endl;
        fio;
        int n;
        cin >> n;
        while (n != 0)
        {
            if (n == -1)
                return 0;
            if (n > 4)
            {
                cout << "11111111" << endl;
                fio;
                cin >> n;
            }
            else if (n == 1)
            {
                cout << "10000000" << endl;
                fio; cin >> n;
            }
            else if (n == 2)
            {   
                state = 0;
                while (n == 2) {
                    if (state == 0) {
                        cout << "10001000" << endl;
                        fio; cin >> n;
                        state = 2;
                    }
                    else if (state == 2) {
                        cout << "10100000" << endl;
                        fio; cin >> n;
                        state = 4;
                    }
                    else if (state == 4) {
                        cout << "10001000" << endl;
                        fio; cin >> n;
                        state = 1;
                    }
                    else if (state == 1) {
                        cout << "10010000" << endl;
                        fio; cin >> n;
                        state = 2;
                    }
                }
            }
            else if (n == 3)
            {
                cout << "11100000" << endl;
                fio; cin >> n;
            }
            else if (n == 4)
            {   
                int cnt = 0;
                state2 = 0;
                while (n == 4) {
                    cnt++;
                    if (state2 == 0) {
                        cout << "10101010" << endl;
                        fio; cin >> n;
                        if (cnt >= 5) {
                            state2 = 5;
                            cnt = 0;
                        }
                    }
                    else if (state2 == 5) {
                        cout << "11001100" << endl;
                        fio; cin >> n;
                        state2 = 8;
                    }
                    else if (state2 == 8) {
                        cout << "10101010" << endl;
                        fio; cin >> n;
                        state2 = 1;
                    }
                    else if (state2 == 1) {
                        cout << "11110000" << endl;
                        fio; cin >> n;
                        state2 = 5;
                    }
                }
            }
        }
    }
}