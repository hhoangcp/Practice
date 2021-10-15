/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct Point {
    int x, y;
};

vector<string> V;
map<string, int> S;

int m, n, t, len;

int Pos(int x, int y) {
    return x * n + y;
}

string Solve(string old) {
    string cur = "";

    for(int id = 0; id < len; ++id) {
        char c; int i = id / n, j = id % n;

        int num = old[Pos((i - 1 + m) % m, (j - 1 + n) % n)] + old[Pos((i - 1 + m) % m, j)] + old[Pos((i - 1 + m) % m, (j + 1) % n)];
        num += old[Pos(i, (j - 1 + n) % n)] + old[Pos(i, (j + 1) % n)];
        num += old[Pos((i + 1) % m, (j - 1 + n) % n)] + old[Pos((i + 1) % m, j)] + old[Pos((i + 1) % m, (j + 1) % n)];

        if ((num == 2 || num == 3) && old[id] == 1) c = 1;
        else if (num == 3 && old[id] == 0) c = 1;
        else c = 0;

        cur = cur + c;
    }

    return cur;
}

int main() {
    freopen("input.txt", "r", stdin);

    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> m >> n >> t; len = n*m;

    string cur = "";
    for(int i = 1; i <= m; ++i) {
        string tmp; cin >> tmp;
        cur = cur + tmp;
    }

    for(int i = 0; i < len; ++i)
    if (cur[i] == '*') cur[i] = 1; else cur[i] = 0;

    V.push_back(cur);
    S[cur] = 0;

    bool cycle = false; int tcycle = -1;
    for(int i = 1; i <= t; ++i) {
        string old = cur;
        cur = Solve(old);
        V.push_back(cur);

        if (S.count(cur)) {
            tcycle = i;
            cycle = true;
            break;
        }

        S.insert({cur, i});
    }

    if (!cycle) {
        /// cout << "NOOOOOOOOOOOOOOOOOOOOOOO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if (cur[i * n + j] == 1) cout << '*';
                else cout << '-';
            }

            cout << '\n';
        }
    } else {
        ///if (tcycle >= 1e5) cout << "??????????????????????????????????????";

        int p = S[cur], len_cycle = tcycle - p;
        t -= p; t %= len_cycle;
        if (t == 0) t = len_cycle;

        cur = V[p + t];
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if (cur[i * n + j] == 1) cout << '*';
                else cout << '-';
            }

            cout << '\n';
        }
    }

    return 0;
}
