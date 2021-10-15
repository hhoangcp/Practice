/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int a[206][206], dp[206][206], n, m;
bool dead[206][206];

bool Checking(int s) {
    dp[1][1] = s;

    for(int i=1; i<=m; ++i)
    for(int j=1; j<=n; ++j) {
        dead[i][j] = false;
        if (i == 1 && j == 1) continue;

        dp[i][j] = -1e9;
        dead[i][j] = dead[i-1][j] && dead[i][j-1];

        if (dead[i][j]) continue;
        int tmp = max(dp[i][j-1], dp[i-1][j]);

        tmp += a[i][j];
        if (tmp <= 0) dead[i][j] = true;

        if (dead[i][j]) continue;
        dp[i][j] = tmp;
    }

    return !dead[m][n] && dp[m][n] > 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> m >> n;
    for(int i=1; i<=m; ++i)
    for(int j=1; j<=n; ++j) cin >> a[i][j];

    for(int i=1; i<=m; ++i) dead[i][0] = dead[i][n+1] = true;
    for(int i=1; i<=n; ++i) dead[0][i] = dead[m+1][i] = true;

    int l = 1, r = 1e9, ans = 1e9+1;
    while (l <= r) {
        int mid = (l+r) >> 1;
        if (Checking(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }

    cout << ans;

    return 0;
}
