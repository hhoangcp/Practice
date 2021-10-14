/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <deque>
#define llong long long

using namespace std;

struct Point {
    int x, y;
} P[1000006];

int dp[4006][5006];
int n, m, k;

bool Check(int x, int y) {
    return 1 <= x && x <= 4000 && 1 <= y && y <= 5000;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> m >> n >> k;
    for(int i = 1; i <= k; ++i) {
        int x, y, d; cin >> x >> y >> d;

        x += 1000, y += 1000;

        if (Check(x+y-d-1, 3000-x+y-d)) ++dp[x+y-d-1][3000-x+y-d]; /// x, y - d
        if (Check(x+y-d-1, 3001-x+d+y)) --dp[x+y-d-1][3001-x+d+y]; /// x - d, y
        if (Check(x+y+d, 3000-x-d+y)) --dp[x+y+d][3000-x-d+y];    /// x + d, y
        if (Check(x+y+d, 3001-x+y+d)) ++dp[x+y+d][3001-x+y+d];    /// x, y + d

        P[i] = {x+y-1, 3000-x+y};
    }

    for(int i = 1; i <= 4000; ++i)
    for(int j = 1; j <= 5000; ++j)
        dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];

    int id = 1;
    for(int i = 2; i <= k; ++i)
    if (dp[P[i].x][P[i].y] > dp[P[id].x][P[id].y]) id = i;

    cout << id << ' ' << dp[P[id].x][P[id].y] - 1;

    return 0;
}
