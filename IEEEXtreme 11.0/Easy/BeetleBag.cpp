/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int dp[506];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int m, n; cin >> m >> n;

        for(int i = 1; i <= m; ++i) dp[i] = 0;

        for(int i = 1; i <= n; ++i) {
            int t, f; cin >> t >> f;

            for(int j = m; j >= t; --j) dp[j] = max(dp[j], dp[j-t] + f);
        }

        cout << dp[m] << '\n';
    }

    return 0;
}
