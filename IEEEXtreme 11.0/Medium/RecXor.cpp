/// hhoangcpascal

#include <iostream>
#include <algorithm>
#define llong long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int l, h, n;
        llong d1, d2;
        cin >> l >> h >> n >> d1 >> d2;

        int mod1 = (d1 - n) % l;
        int mod2 = (d2 - n) % l;

        int r = abs(mod2 - mod1) + 1;
        if (mod1 > mod2) d1 -= mod1 - mod2;
        else d2 -= mod2 - mod1;

        int mod = min(mod1, mod2);

        llong sum_xor = 0;
        for(int i = 1; i <= h; ++i) {
            llong L = n + 1LL * l * (i - 1), R = L + l - 1;

            if (R - L + 1 <= 7)
                for(llong j = L; j <= R; ++j) sum_xor ^= j;
            else {
                while (L % 4 != 0) sum_xor ^= L++;
                while (R % 4 != 3) sum_xor ^= R--;
            }
        }

        for(int i = (d1 - n + l - 1) / l; i <= (d2 - n + l - 1) / l; ++i) {
            llong L = n + 1LL * l * (i-1) + mod;
            llong R = L + r - 1;

            if (R - L + 1 <= 7)
                for(llong j = L; j <= R; ++j) sum_xor ^= j;
            else {
                while (L % 4 != 0) sum_xor ^= L++;
                while (R % 4 != 3) sum_xor ^= R--;
            }
        }

        cout << sum_xor << '\n';
    }

    return 0;
}
