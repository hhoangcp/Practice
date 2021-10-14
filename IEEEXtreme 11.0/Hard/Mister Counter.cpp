/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

int n, q, a[250006], pre[250006];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (i == 1) pre[i] = 0;
        else if (a[i-1] < a[i]) pre[i] = i - 1;
        else pre[i] = pre[i-1];
    }

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;

        if (pre[r] < l) {
            cout << "0\n";
            continue;
        }

        l = pre[r];
        int p = l+1, L = l+1, R = r;
        while (L <= R) {
            int mid = (L + R) >> 1;

            if (a[mid] > a[l]) {
                p = mid;
                L = mid + 1;
            } else R = mid - 1;
        }

        int ans = r - l + 1;
        if (ans % 2 == 0 && p != (l + r + 1) / 2) --ans;

        cout << ans << '\n';
    }

    return 0;
}
