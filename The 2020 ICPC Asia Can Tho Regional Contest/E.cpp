/// hhoangcpascal
/// Edge Removal
/// https://open.kattis.com/problems/edgeremoval

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct TEdge {
    int u, v, c, pos;

    bool operator < (const TEdge &other) const {
        return c < other.c;
    }
} E[300006];

int n, m, lab[200006], Rank[200006];

int Find(int u) {
    if (lab[u] != u) lab[u] = Find(lab[u]);
    return lab[u];
}

bool Same(int u, int v) {
    u = Find(u), v = Find(v);
    return u == v;
}

void Merge(int u, int v) {
    u = Find(u), v = Find(v);

    if (u == v) return;
    if (Rank[u] == Rank[v]) ++Rank[u];
    if (Rank[u] > Rank[v]) lab[v] = u;
    else lab[u] = v;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        cin >> n >> m;

        for(int i = 1; i <= n; ++i) lab[i] = i, Rank[i] = 0;

        for(int i = 1; i <= m; ++i) {
            int u, v, c; cin >> u >> v >> c;
            E[i] = {u, v, c, i};
        }

        sort(E+1, E+m+1);

        vector<int> Res; int ok = 0;
        for(int r = 1, l = 1; r <= m; ++r)
        if (r == m || (E[r].c != E[r+1].c)) {
            vector<int> Checking;

            for(; l <= r; ++l) {
                int u = E[l].u, v = E[l].v;

                if (!Same(u, v)) Checking.push_back(l);
            }

            for(int e: Checking) {
                int u = E[e].u, v = E[e].v;

                if (Same(u, v)) Res.push_back(E[e].pos);
                else Merge(u, v), ++ok;
            }
        }


        if (ok != n - 1) {
            cout << -1 << '\n';
            continue;
        }

        cout << Res.size() << ' ';
        for(int e: Res) cout << e << ' ';
        cout << '\n';
    }

    return 0;
}
