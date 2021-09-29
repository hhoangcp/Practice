/// hhoangcpascal
/// Juggling Sequence
/// https://open.kattis.com/problems/jugglingsequence

#include <iostream>
#include <algorithm>
#include <queue>
#define llong long long

using namespace std;

queue<int> Q;
llong P[206], Length[206];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        llong m, n; cin >> n >> m;

        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }

        llong length = 0, cur = 2, pivot = 0;
        while (length < n) {
            P[++pivot] = cur;

            length += (cur - 1) * 2LL + 1;
            Length[pivot] = length;
            cur = length + 2;
        }

        llong L = 1, R = 3e18, x = -1;
        while (L <= R) {
            llong mid = (L + R) >> 1LL;

            llong num = 0;
            for(int i = 1; i < pivot; ++i) {
                if (mid >= 1) ++num;

                llong N = P[i];
                num += min(mid, N) - 1;
                if (mid >= 2*N) num += min(mid, 3 * N - 2) - 2 * N + 1;
            }

            llong N = P[pivot];

            if (length > n) {
                llong sub = n - Length[pivot - 1];

                if (sub >= 1) num += (mid >= 1);
                --sub;

                llong tmp = sub / 2;
                llong r = N - tmp + 1;

                if (sub & 1) --r;
                if (mid >= r) num += min(mid, N) - r + 1;

                if (mid >= 2 * N) {
                    r = 2 * N + tmp - 1;
                    num += min(mid, r) - 2 * N + 1;
                }
            } else {
                if (mid >= 1) ++num;
                num += min(mid, N) - 1;
                if (mid >= 2*N) num += min(mid, 3 * N - 2) - 2 * N + 1;
            }

            if (num < m) L = mid + 1;
            else {
                x = mid;
                R = mid - 1;
            }
        }

        cout << x << '\n';
    }

    return 0;
}
