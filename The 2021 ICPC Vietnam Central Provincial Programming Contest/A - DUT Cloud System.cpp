/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#define mt make_tuple

using namespace std;

vector<tuple<int, int, int>> Edges;
vector<pair<int, int>> V[206];
int n, Min[206][206], par[206], Rank[206], C[206][206];
bool visited[206];

void BFS(int s) {
    for(int u = 1; u <= n; ++u) visited[u] = false;

    Min[s][s] = 1e9; visited[s] = true;
    queue<int> Q; Q.push(s);

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();

        for(pair<int, int> e: V[u]) {
            int v = e.first, w = e.second;

            if (!visited[v]) {
                visited[v] = true;
                Min[s][v] = min(Min[s][u], w);
                Q.push(v);
            }
        }
    }
}

int Find(int u) {
    if (par[u] != u) par[u] = Find(par[u]);
    return par[u];
}

bool Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return false;

    if (Rank[u] == Rank[v]) ++Rank[u];
    if (Rank[u] > Rank[v]) par[v] = u;
    else par[u] = v;

    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    for(int test = 1; test <= t; ++test) {
        cin >> n;
        for(int i = 1; i <= n; ++i) {
            par[i] = i, Rank[i] = 0;
            V[i].clear();
        }

        Edges.clear();

        for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            int c; cin >> c;
            C[i][j] = c;

            Edges.push_back(mt(c, i, j));
        }

        sort(Edges.begin(), Edges.end(), greater<tuple<int, int, int>>());

        for(tuple<int, int, int> e: Edges) {
            int w = get<0>(e);
            int u = get<1>(e);
            int v = get<2>(e);

            if (Union(u, v)) {
                V[u].push_back({v, w});
                V[v].push_back({u, w});
            }
        }

        for(int u = 1; u <= n; ++u) BFS(u);

        bool ok = true;
        for(int u = 1; u <= n && ok; ++u) {
            Min[u][u] = 0;

            for(int v = 1; v <= n && ok; ++v)
            if (Min[u][v] != C[u][v]) ok = false;
        }

        cout << "Case #" << test << ": ";
        if (!ok) cout << "NO\n";
        else {
            cout << "YES\n";

            for(int u = 1; u <= n; ++u) {
                for(int v = 1; v <= n; ++v) C[u][v] = 0;
                for(pair<int, int> e: V[u]) C[u][e.first] = e.second;

                for(int v = 1; v <= n; ++v) cout << C[u][v] << ' ';
                cout << '\n';
            }
        }
    }

    return 0;
}
