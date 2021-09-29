/// hhoangcpascal
/// Kingdom of Hamsters
/// https://open.kattis.com/problems/kingdomofhamsters

#include <iostream>
#include <algorithm>
#include <cmath>
#define ldouble long double

using namespace std;

struct Point {
    int x, y;
} P[4006];

ldouble dp[7][4006];
int n;

ldouble Dist(int a, int b) {
    return sqrt((1.0L * P[a].x - P[b].x) * (1.0L * P[a].x - P[b].x) + (1.0L * P[a].y - P[b].y) * (1.0L * P[a].y - P[b].y));
}

void Divide_and_Conquer(int k, int L, int R, int optL, int optR) {
    if (L > R) return;

    int mid = (L + R) >> 1;

    ldouble best = 0; int pos = -1;
    for(int i = optL; i <= min(mid - 1, optR); ++i)
    if (dp[k-1][i] + Dist(i, mid) > best) {
        pos = i;
        best = dp[k-1][i] + Dist(i, mid);
    }

    dp[k][mid] = best;

    Divide_and_Conquer(k, L, mid - 1, optL, pos);
    Divide_and_Conquer(k, mid + 1, R, pos, optR);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int x, y; cin >> x >> y;
        P[i] = P[n+i] = {x, y};
    }

    for(int s = 1; s <= n; ++s) {
        for(int i = 0; i <= 6; ++i)
        for(int j = s+1; j <= n+s-1; ++j) dp[i][j] = 0;

        for(int i = 2; i <= 6; ++i) Divide_and_Conquer(i, s+i-1, n+s-1, s+i-2, n+s-2);


        ldouble best = 0;
        for(int j = s+5; j <= n+s-1; ++j) best = max(best, dp[6][j] + Dist(j, s));

        (cout << fixed).precision(15);
        cout << best << '\n';
    }

    return 0;
}
