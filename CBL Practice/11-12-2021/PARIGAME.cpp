/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int dp[506][506], sum[506][506];
int dp_row[2][506][506], dp_column[2][506][506];

int main() {
    freopen("PARIGAME.INP", "r", stdin);
    freopen("PARIGAME.OUT", "w", stdout);

    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int m, n; cin >> m >> n;

        for(int i = 0; i <= max(n, m); ++i) {
            dp_row[1][0][i] = 1;
            dp_column[1][i][0] = 1;
        }

        for(int i = 1; i <= m; ++i)
        for(int j = 1; j <= n; ++j) {
            int a; cin >> a;

            sum[i][j] = sum[i-1][j] ^ sum[i][j-1] ^ sum[i-1][j-1] ^ (a & 1);
            dp[i][j] = (dp_row[sum[i][j]][i-1][j] ^ 1) | (dp_column[sum[i][j]][i][j-1] ^ 1);

            dp_row[sum[i][j]][i][j] = dp_row[sum[i][j]][i-1][j] & dp[i][j];
            dp_row[sum[i][j]^1][i][j] = dp_row[sum[i][j]^1][i-1][j];

            dp_column[sum[i][j]][i][j] = dp_column[sum[i][j]][i][j-1] & dp[i][j];
            dp_column[sum[i][j]^1][i][j] = dp_column[sum[i][j]^1][i][j-1];
        }

        if (dp[m][n] & 1) cout << "TRUE\n";
        else cout << "FALSE\n";
    }

    return 0;
}
