/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

const llong mod = 1e9+7;
llong fact[100006];
vector<int> V[100006];
int n, m;
bool visited[100006];

int DFS(int u) {
    int sz = 1;
    visited[u] = true;

    for(int v: V[u])
    if (!visited[v]) sz += DFS(v);

    return sz;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> m;

    fact[0] = 1;
    for(int i = 1; i <= n; ++i) fact[i] = fact[i-1] * i % mod;

    while (m--) {
        int u, v; cin >> u >> v;
        ++u, ++v;

        V[u].push_back(v);
        V[v].push_back(u);
    }

    llong ans = 0;
    for(int u = 1; u <= n; ++u)
    if (!visited[u]) {
        int sz = DFS(u);

        if (sz > 2) (ans += fact[sz]) %= mod;
    }

    cout << ans;
    return 0;
}
