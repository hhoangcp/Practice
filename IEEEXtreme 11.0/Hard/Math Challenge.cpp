/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <deque>
#define llong long long

using namespace std;

const llong mod = 1e9+7;
const llong phi = 1e9+6;
const llong phi_phi = 5e8+2;

llong power(llong A, llong N, llong M) {
    llong res = 1; A %= M, N %= phi;

    while (N > 0) {
        if (N & 1) res = (res * A) % M;
        A = A * A % M;
        N >>= 1;
    }

    return res;
}

llong fact[1000006], inv_fact[1000006], num[1000006];

void Init() {
    fact[0] = inv_fact[0] = 1;
    for(int i = 1; i <= 1e6; ++i) {
        num[i] = i;

        while (num[i] % 2 == 0) num[i] /= 2;

        fact[i] = fact[i-1] * num[i] % phi;
    }

    inv_fact[1000000] = power(fact[1000000], phi_phi - 1, phi);
    for(int i = 999999; i >= 1; --i) inv_fact[i] = inv_fact[i+1] * num[i+1] % phi;
}

int Exp(int n) {
    int sum = 0;

    while (n >= 2) {
        sum += n / 2;
        n /= 2;
    }

    return sum;
}

llong nCr(int n, int r) {
    int exp_0 = Exp(n) - Exp(r) - Exp(n-r);

    llong ans = power(2, exp_0, phi) % phi;
    (ans *= fact[n]) %= phi;
    (ans *= inv_fact[n-r]) %= phi;
    (ans *= inv_fact[r]) %= phi;

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    Init();

    int t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b >> c;
        cout << power(a, nCr(b, c), mod) << '\n';
    }

    return 0;
}
