/// hhoangcpascal
/// Latin Square
/// https://open.kattis.com/problems/latinsquare

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> V[106];
int n, k, res[106][106], match[106];
bool visited[106], tick[106];

bool DFS(int u) {
    for(int v: V[u])
    if (!visited[v]) {
        visited[v] = true;

        if (match[v] == 0 || DFS(match[v])) {
            match[v] = u;
            return true;
        }
    }

    return false;
}

int Max_Matching() {
    vector<int> Tmp;
    for(int i = 1; i <= n; ++i) Tmp.push_back(i);

    int max_matching = 0;
    while (true) {
        bool stop = true;
        for(int v = 1; v <= n; ++v) visited[v] = false;

        for(int i = Tmp.size() - 1; i >= 0; --i)
        if (DFS(Tmp[i])) {
            stop = false;
            ++max_matching;
            Tmp[i] = Tmp.back();
            Tmp.pop_back();
        }

        if (stop) break;
    }

    return max_matching;
}

bool Check(int num) {
    if (tick[num]) return true;

    for(int v = 1; v <= n; ++v) match[v] = 0;
    for(int u = 1; u <= n; ++u) {
        V[u].clear();

        for(int v = 1; v <= n; ++v)
        if (res[u][v] == 0) V[u].push_back(v);
    }

    int max_matching = Max_Matching();
    if (max_matching != n) return false;

    for(int v = 1; v <= n; ++v) res[match[v]][v] = num;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> k;
    for(int u = 1; u <= n; ++u)
    for(int v = 1; v <= n; ++v) {
        cin >> res[u][v];
        if (res[u][v] > 0) tick[res[u][v]] = true;
    }

    bool ok = true;
    for(int num = 1; num <= n; ++num) ok &= Check(num);

    if (!ok) cout << "NO";
    else {
        cout << "YES\n";

        for(int u = 1; u <= n; ++u) {
            for(int v = 1; v <= n; ++v) cout << res[u][v] << ' ';
            cout << '\n';
        }
    }

    return 0;
}
