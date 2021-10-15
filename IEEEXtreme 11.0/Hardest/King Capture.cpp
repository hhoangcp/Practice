/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> V[106];
bool dp[106][106][106][2];
int n, m;

void Init() {
    for(int i = 1; i <= n; ++i) dp[i][i][0][0] = dp[i][i][0][1] = true;

    for(int step = 1; step <= n; ++step) {
        for(int u = 1; u <= n; ++u)
        for(int v = 1; v <= n; ++v) {
            dp[u][v][step][0] = dp[u][v][step-1][1];
            for(int ver: V[u])
                dp[u][v][step][0] |= dp[ver][v][step-1][1];
        }

        for(int u = 1; u <= n; ++u)
        for(int v = 1; v <= n; ++v) {
            dp[u][v][step][1] = dp[u][v][step-1][0];

            for(int ver: V[v])
                dp[u][v][step][1] &= dp[u][ver][step-1][0];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;

        V[u].push_back(v);
        V[v].push_back(u);
    }

    Init();

    int minsteps = 1e9, ver_white = -1;
    for(int u = 1; u <= n; ++u) {
        int mmax = -1;

        for(int v = 1; v <= n; ++v) {
            int mmin = 1e9;

            for(int i = 0; i <= n; ++i)
            if (dp[u][v][i][0] == true) {
                mmin = i;
                break;
            }

            mmax = max(mmax, mmin);
        }

        if (mmax < minsteps) {
            minsteps = mmax;
            ver_white = u;
        }
    }

    cout << ver_white << '\n';
    cout.flush();
    int ver_black; cin >> ver_black;

    while (true) {
        --minsteps;

        for(int u: V[ver_white]) {
            if (dp[u][ver_black][minsteps][1]) {
                ver_white = u;
                break;
            }
        }

        cout << ver_white << '\n';
        if (ver_white == ver_black) return 0;

        cout.flush();
        cin >> ver_black; --minsteps;
        if (ver_white == ver_black) return 0;
    }

    return 0;
}
