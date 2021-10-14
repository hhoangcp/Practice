/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int n, par[20006];

int Find(int u) {
    if (par[u] != u) par[u] = Find(par[u]);
    return par[u];
}

bool Solve(int u, int v) {
    if (u > v) swap(u, v);

    int u1 = Find(2*u-1), u2 = Find(2*u);
    int v1 = Find(2*v-1), v2 = Find(2*v);

    if (u1 == v1 && u2 == v2) return true;

    par[u1] = v2;
    par[v1] = u2;

    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= 2*n; ++i) par[i] = i;

    while (true) {
        int u, v; cin >> u >> v;
        bool ok = Solve(u, v);

        if (ok) {
            cout << "0\n";
            return 0;
        } else {
            cout << "1\n";
            cout.flush();
        }
    }

    return 0;
}
