/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

struct TEdge {
    int u, v;
} E[10006];

int n, m, par[1006], Rank[1006];

int Find(int u) {
    if (par[u] != u) par[u] = Find(par[u]);
    return par[u];
}

bool DSU(int u, int v) {
    u = Find(u), v = Find(v);

    if (u == v) return false;

    if (Rank[u] == Rank[v]) ++Rank[u];
    if (Rank[u] > Rank[v]) par[v] = u; else par[u] = v;

    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for(int i = 1; i <= m; ++i) cin >> E[i].u >> E[i].v;

        if (m >= n) {
            cout << "1\n";
            continue;
        }

        bool ok = false;
        for(int i = 0; i < n; ++i) par[i] = i, Rank[i] = 0;
        for(int i = 1; i <= m; ++i)
        if (!DSU(E[i].u, E[i].v)) {
            ok = true;
            break;
        }

        if (ok) cout << "1\n"; else cout << "0\n";
    }

    return 0;
}
