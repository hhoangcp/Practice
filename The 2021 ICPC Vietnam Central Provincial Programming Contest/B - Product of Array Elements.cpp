/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

const llong mod = 1e9+7;
vector<int> Neg;
int Zero, n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n;

    llong ans = 1;
    for(int i = 1; i <= n; ++i) {
        int a; cin >> a;

        if (a == 0) ++Zero;
        else if (a < 0) Neg.push_back(a);
        else (ans *= a) %= mod;
    }

    if (Zero >= 2 || (Zero == 1 && (Neg.size() & 1))) {
        cout << 0;
        return 0;
    } else if (Zero == 1) {
        for(int a: Neg) (ans *= (-a)) %= mod;
    } else {
        if (Neg.size() & 1) {
            for(int i = 0; i < (int) Neg.size() - 1; ++i)
            if (Neg[i] > Neg[Neg.size() - 1]) swap(Neg[i], Neg[Neg.size() - 1]);

            Neg.pop_back();
        }

        for(int a: Neg) (ans *= (-a)) %= mod;
    }

    cout << ans;
    return 0;
}
