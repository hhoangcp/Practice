/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> V[100006], S, bcc[100006];
int n, m, low[100006], num[100006];
int nbcc = 0;
bool tick[100006];

void DFS(int u, bool isRoot) {
    low[u] = 1e9, num[u] = ++num[0];
    S.push_back(u);

    for(int v: V[u]) {
        if (num[v] > 0) low[u] = min(low[u], num[v]);
        else {
            DFS(v, false);
            low[u] = min(low[u], low[v]);

            if (isRoot || low[v] >= num[u]) {
                ++nbcc; bcc[nbcc].push_back(u);

                do {
                    int ver = S.back(); S.pop_back();
                    bcc[nbcc].push_back(ver);
                    if (ver == v) break;
                } while (!S.empty());
            }
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

    for(int u = 1; u <= n; ++u)
    if (num[u] == 0) DFS(u, true);

    for(int i = 1; i <= nbcc; ++i)
    if (bcc[i].size() > 2)
        for(int u: bcc[i]) tick[u] = true;


    for(int u = 1; u <= n; ++u)
    if (!tick[u]) cout << u << '\n';

    return 0;
}
