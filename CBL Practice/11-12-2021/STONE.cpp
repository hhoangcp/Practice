/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int n, k, a[106];
bool dp[2000006];

int main() {
    freopen("STONE.INP", "r", stdin);
    freopen("STONE.OUT", "w", stdout);

    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;

        for(int i = 1; i <= k; ++i) cin >> a[i];

        sort(a+1, a+k+1);

        for(int i = 1; i <= n; ++i) {
            dp[i] = false;

            for(int j = 1; j <= k && !dp[i]; ++j)
            if (i >= a[j]) dp[i] |= !dp[i-a[j]];
            else break;
        }

        if (dp[n] & 1) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
