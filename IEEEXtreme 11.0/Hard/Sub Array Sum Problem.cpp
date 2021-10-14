/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

typedef vector<llong> vec1;
typedef vector<vec1 > vec2;
typedef vector<vec2 > vec3;
typedef vector<vec3 > vec4;
typedef vector<vec4 > vec5;

void Case1() {
    int n; cin >> n;
    vec1 prefix(n+1, 0);

    for(int i = 1; i <= n; ++i) {
        cin >> prefix[i];
        prefix[i] += prefix[i-1];
    }

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << prefix[r] - prefix[l-1] << '\n';
    }
}

void Case2() {
    int m, n; cin >> m >> n;
    vec2 prefix(m+1, vec1(n+1, 0));

    for(int i = 1; i <= m; ++i)
    for(int j = 1; j <= n; ++j) {
        cin >> prefix[i][j];
        prefix[i][j] += prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
    }

    int q; cin >> q;
    while (q--) {
        int x, y, u, v; cin >> x >> y >> u >> v;
        cout << prefix[u][v] - prefix[x-1][v] - prefix[u][y-1] + prefix[x-1][y-1] << '\n';
    }
}

void Case3() {
    vector<int> n(3, 0);
    for(int i = 0; i < 3; ++i) cin >> n[i];

    vec3 prefix(n[0]+1, vec2(n[1]+1, vec1(n[2]+1, 0)));

    for(int i = 1; i <= n[0]; ++i)
    for(int j = 1; j <= n[1]; ++j)
    for(int k = 1; k <= n[2]; ++k) {
        cin >> prefix[i][j][k];

        prefix[i][j][k] += prefix[i-1][j][k] + prefix[i][j-1][k] + prefix[i][j][k-1];
        prefix[i][j][k] -= prefix[i-1][j-1][k] + prefix[i-1][j][k-1] + prefix[i][j-1][k-1];
        prefix[i][j][k] += prefix[i-1][j-1][k-1];
    }

    int q; cin >> q;
    while (q--) {
        int x1, x2, x3, y1, y2, y3;
        cin >> x1 >> x2 >> x3 >> y1 >> y2 >> y3;

        llong ans = prefix[y1][y2][y3]; --x1, --x2, --x3;
        ans -= prefix[x1][y2][y3] + prefix[y1][x2][y3] + prefix[y1][y2][x3];
        ans += prefix[x1][x2][y3] + prefix[y1][x2][x3] + prefix[x1][y2][x3];
        ans -= prefix[x1][x2][x3];

        cout << ans << '\n';
    }
}

void Case4() {
    vector<int> n(4, 0);
    for(int i = 0; i < 4; ++i) cin >> n[i];

    vec4 prefix(n[0]+1, vec3(n[1]+1, vec2(n[2]+1, vec1(n[3]+1, 0))));

    for(int i = 1; i <= n[0]; ++i)
    for(int j = 1; j <= n[1]; ++j)
    for(int k = 1; k <= n[2]; ++k)
    for(int l = 1; l <= n[3]; ++l) {
        cin >> prefix[i][j][k][l];

        prefix[i][j][k][l] += prefix[i-1][j][k][l] + prefix[i][j-1][k][l] + prefix[i][j][k-1][l] + prefix[i][j][k][l-1];
        prefix[i][j][k][l] -= prefix[i-1][j-1][k][l] + prefix[i-1][j][k-1][l] + prefix[i][j-1][k-1][l]
                            + prefix[i-1][j][k][l-1] + prefix[i][j-1][k][l-1] + prefix[i][j][k-1][l-1];
        prefix[i][j][k][l] += prefix[i-1][j-1][k-1][l] + prefix[i-1][j-1][k][l-1] + prefix[i-1][j][k-1][l-1] + prefix[i][j-1][k-1][l-1];
        prefix[i][j][k][l] -= prefix[i-1][j-1][k-1][l-1];
    }

    int q; cin >> q;
    while (q--) {
        int x1, x2, x3, x4, y1, y2, y3, y4;
        cin >> x1 >> x2 >> x3 >> x4 >> y1 >> y2 >> y3 >> y4;

        llong ans = prefix[y1][y2][y3][y4]; --x1, --x2, --x3, --x4;
        ans -= prefix[x1][y2][y3][y4] + prefix[y1][x2][y3][y4] + prefix[y1][y2][x3][y4] + prefix[y1][y2][y3][x4];
        ans += prefix[x1][x2][y3][y4] + prefix[x1][y2][x3][y4] + prefix[x1][y2][y3][x4]
                + prefix[y1][x2][x3][y4] + prefix[y1][x2][y3][x4] + prefix[y1][y2][x3][x4];
        ans -= prefix[x1][x2][x3][y4] + prefix[x1][x2][y3][x4] + prefix[x1][y2][x3][x4] + prefix[y1][x2][x3][x4];
        ans += prefix[x1][x2][x3][x4];

        cout << ans << '\n';
    }
}

void Case5() {
    vector<int> n(5, 0);
    for(int i = 0; i < 5; ++i) cin >> n[i];

    vec5 prefix(n[0]+1, vec4(n[1]+1, vec3(n[2]+1, vec2(n[3]+1, vec1(n[4]+1, 0)))));

    for(int i = 1; i <= n[0]; ++i)
    for(int j = 1; j <= n[1]; ++j)
    for(int k = 1; k <= n[2]; ++k)
    for(int l = 1; l <= n[3]; ++l)
    for(int m = 1; m <= n[4]; ++m) {
        cin >> prefix[i][j][k][l][m];

        prefix[i][j][k][l][m] += prefix[i-1][j][k][l][m] + prefix[i][j-1][k][l][m]
                            + prefix[i][j][k-1][l][m] + prefix[i][j][k][l-1][m] + prefix[i][j][k][l][m-1];

        prefix[i][j][k][l][m] -= prefix[i-1][j-1][k][l][m] + prefix[i-1][j][k-1][l][m] + prefix[i][j-1][k-1][l][m]
                            + prefix[i-1][j][k][l-1][m] + prefix[i][j-1][k][l-1][m] + prefix[i][j][k-1][l-1][m]
                            + prefix[i-1][j][k][l][m-1] + prefix[i][j-1][k][l][m-1] + prefix[i][j][k-1][l][m-1]
                            + prefix[i][j][k][l-1][m-1];

        prefix[i][j][k][l][m] += prefix[i-1][j-1][k-1][l][m] + prefix[i-1][j-1][k][l-1][m] + prefix[i-1][j][k-1][l-1][m]
                            + prefix[i][j-1][k-1][l-1][m] + prefix[i-1][j-1][k][l][m-1] + prefix[i-1][j][k-1][l][m-1]
                            + prefix[i-1][j][k][l-1][m-1] + prefix[i][j-1][k-1][l][m-1] + prefix[i][j-1][k][l-1][m-1]
                            + prefix[i][j][k-1][l-1][m-1];

        prefix[i][j][k][l][m] -= prefix[i-1][j-1][k-1][l-1][m] + prefix[i-1][j-1][k-1][l][m-1] + prefix[i-1][j-1][k][l-1][m-1]
                                + prefix[i-1][j][k-1][l-1][m-1] + prefix[i][j-1][k-1][l-1][m-1];

        prefix[i][j][k][l][m] += prefix[i-1][j-1][k-1][l-1][m-1];
    }

    int q; cin >> q;
    while (q--) {
        int x1, x2, x3, x4, x5, y1, y2, y3, y4, y5;
        cin >> x1 >> x2 >> x3 >> x4 >> x5 >> y1 >> y2 >> y3 >> y4 >> y5;

        llong ans = prefix[y1][y2][y3][y4][y5]; --x1, --x2, --x3, --x4, --x5;

        ans -= prefix[x1][y2][y3][y4][y5] + prefix[y1][x2][y3][y4][y5] + prefix[y1][y2][x3][y4][y5]
                + prefix[y1][y2][y3][x4][y5] + prefix[y1][y2][y3][y4][x5];

        ans += prefix[x1][x2][y3][y4][y5] + prefix[x1][y2][x3][y4][y5] + prefix[x1][y2][y3][x4][y5]
                + prefix[x1][y2][y3][y4][x5] + prefix[y1][x2][x3][y4][y5] + prefix[y1][x2][y3][x4][y5]
                + prefix[y1][x2][y3][y4][x5] + prefix[y1][y2][x3][x4][y5] + prefix[y1][y2][x3][y4][x5]
                + prefix[y1][y2][y3][x4][x5];

        ans -= prefix[x1][x2][x3][y4][y5] + prefix[x1][x2][y3][x4][y5] + prefix[x1][x2][y3][y4][x5]
                + prefix[x1][y2][x3][x4][y5] + prefix[x1][y2][x3][y4][x5] + prefix[x1][y2][y3][x4][x5]
                + prefix[y1][x2][x3][x4][y5] + prefix[y1][x2][x3][y4][x5] + prefix[y1][x2][y3][x4][x5]
                + prefix[y1][y2][x3][x4][x5];

        ans += prefix[x1][x2][x3][x4][y5] + prefix[x1][x2][x3][y4][x5] + prefix[x1][x2][y3][x4][x5]
                + prefix[x1][y2][x3][x4][x5] + prefix[y1][x2][x3][x4][x5];

        ans -= prefix[x1][x2][x3][x4][x5];

        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int d; cin >> d;
    switch (d) {
        case 1: return Case1(), 0;
        case 2: return Case2(), 0;
        case 3: return Case3(), 0;
        case 4: return Case4(), 0;
        case 5: return Case5(), 0;
    }

    return 0;
}
