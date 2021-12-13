/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> V[200006];
int BLi[2][200006][19], chain[200006], End[200006], Log2[200006];
int n, q, par[200006], Start[200006], cnt = 0, pos[200006], depth[200006];
int nChild[200006], W[200006], hld[200006], RMQ[200006][19];

void DFS(int u) {
    int p = -1; nChild[u] = 1;

    for(int i = 0; i < (int) V[u].size(); ++i) {
        int v = V[u][i];
        if (par[u] == v) continue;

        par[v] = u;
        depth[v] = depth[u] + 1;
        DFS(v);

        nChild[u] += nChild[v];
        if (p == -1 || nChild[V[u][p]] < nChild[v]) p = i;
    }

    if (p != -1) swap(V[u][0], V[u][p]);
}

void HLD(int u, int c) {
    chain[u] = c; End[c] = u; pos[u] = ++pos[0]; hld[pos[u]] = u;
    if (par[u] != V[u][0]) HLD(V[u][0], c);

    for(int i = 1; i < (int) V[u].size(); ++i) {
        int v = V[u][i];
        if (par[u] != v) {
            Start[++cnt] = v;
            HLD(v, v);
        }
    }
}

void Init() {
    Log2[0] = -1;
    for(int i = 0; (1 << i) <= n; ++i) Log2[(1 << i)] = i;
    for(int i = 2; i <= n; ++i)
    if (Log2[i] == 0) Log2[i] = Log2[i-1];

    DFS(1);

    Start[++cnt] = 1;
    HLD(1, 1);

    for(int i = 1; i <= cnt; ++i) {
        int u = Start[i], v = End[u];
        u = pos[u], v = pos[v];

        vector<int> s;
        for(int j = u; j <= v; ++j) {
            RMQ[j][0] = W[hld[j]];

            while (!s.empty() && W[hld[s.back()]] <= W[hld[j]]) s.pop_back();
            if (!s.empty()) BLi[1][j][0] = s.back();
            else BLi[1][j][0] = 0;

            s.push_back(j);

            for(int k = 1; k <= Log2[v - u + 1]; ++k) BLi[1][j][k] = BLi[1][BLi[1][j][k-1]][k-1];
        }

        s.clear();
        for(int j = v; j >= u; --j) {
            while (!s.empty() && W[hld[s.back()]] <= W[hld[j]]) s.pop_back();
            if (!s.empty()) BLi[0][j][0] = s.back();
            else BLi[0][j][0] = 0;

            s.push_back(j);

            for(int k = 1; k <= Log2[v - u + 1]; ++k) BLi[0][j][k] = BLi[0][BLi[0][j][k-1]][k-1];
        }
    }

    for(int i = 1; (1 << i) <= n; ++i)
    for(int j = 1; j + (1 << i) - 1 <= n; ++j)
        RMQ[j][i] = max(RMQ[j][i-1], RMQ[j + (1 << (i - 1))][i - 1]);
}

int Query(int s, int t) {
    vector<pair<int, int>> Path1, Path2;

    while (chain[s] != chain[t]) {
        if (depth[chain[s]] > depth[chain[t]]) {
            Path1.push_back({pos[s], pos[chain[s]]});
            s = par[chain[s]];
        } else {
            Path2.push_back({pos[chain[t]], pos[t]});
            t = par[chain[t]];
        }
    }

    if (depth[s] > depth[t]) Path1.push_back({pos[s], pos[t]});
    else Path2.push_back({pos[s], pos[t]});

    reverse(Path2.begin(), Path2.end());

    int Max = -1e9, num = 0;
    for(pair<int, int> p: Path1) {
        int v = p.first, u = p.second;

        int l = v, r = u, cur = -1;
        while (l >= r) {
            int mid = (l + r) >> 1;

            int k = Log2[l - mid + 1];
            if (max(RMQ[mid][k], RMQ[l - (1 << k) + 1][k]) > Max) {
                cur = mid;
                r = mid + 1;
            } else l = mid - 1;
        }

        if (cur == -1) continue;
        ++num;

        for(int i = Log2[cur - u]; i >= 0; --i) {
            if (BLi[1][cur][i] == 0 || BLi[1][cur][i] < u) continue;

            num += (1 << i);
            cur = BLi[1][cur][i];
        }

        Max = RMQ[cur][0];
    }

    for(pair<int, int> p: Path2) {
        int u = p.first, v = p.second;

        int l = u, r = v, cur = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;

            int k = Log2[mid - l + 1];
            if (max(RMQ[l][k], RMQ[mid - (1 << k) + 1][k]) > Max) {
                cur = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        if (cur == -1) continue;
        ++num;

        for(int i = Log2[v - cur]; i >= 0; --i) {
            if (BLi[0][cur][i] == 0 || BLi[0][cur][i] > v) continue;

            num += (1 << i);
            cur = BLi[0][cur][i];
        }

        Max = RMQ[cur][0];
    }

    return num;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> W[i];
    for(int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;

        V[u].push_back(v);
        V[v].push_back(u);
    }

    Init();

    int pre = 0;
    while (q--) {
        int x, y; cin >> x >> y;

        int s = (x + pre) % n + 1;
        int t = (y + pre) % n + 1;

        int cur = Query(s, t);
        cout << cur << '\n';
        pre = cur;
    }

    return 0;
}
