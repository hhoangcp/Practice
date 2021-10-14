/// hhoangcpascal

#include <iostream>
#include <algorithm>
#define llong long long

using namespace std;

const llong mod = 1e9+7;
llong dp[100006], prefix[100006];
int n, c[19][19];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    c[0][0] = 1;
    for(int i = 1; i <= 16; ++i)
    for(int j = 0; j <= i; ++j) {
        if (j == 0) c[i][j] = 1;
        else c[i][j] = c[i-1][j] + c[i-1][j-1];
    }

    int n; cin >> n;

    llong ans = 1;
    for(int h = 2; (1 << (h - 1)) <= n; ++h) {
        for(int i = 1; i <= n; ++i) dp[i] = 0;
        dp[0] = 1;

        int sum = 0;
        for(int i = 1; i <= h; ++i) {
            int delta = c[h-1][i-1];

            for(int j = sum; j <= n-delta; ++j) {
                prefix[j] = dp[j];
                if (j >= sum + delta) (prefix[j] += prefix[j-delta]) %= mod;
            }

            sum += delta;
            for(int j = sum; j <= n; ++j) dp[j] = prefix[j-delta];
        }

        (ans += dp[n]) %= mod;
    }

    cout << ans << '\n';
    return 0;
}
