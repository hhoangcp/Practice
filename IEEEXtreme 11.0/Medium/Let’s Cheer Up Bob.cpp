/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define llong long long

using namespace std;

int pos[9], power[9];
queue<pair<vector<int>, int> > Q;
bool tick[19683];

vector<int> Convert(int u) {
    vector<int> U(9, 0);

    for(int i = 0; i < 9; ++i) {
        U[i] = u % 3;
        u /= 3;
    }

    return U;
}

bool Bob_Win(vector<int> U) {
    if (U[0] == U[4] && U[4] == U[8] && U[8] == 1) return true;
    if (U[2] == U[4] && U[4] == U[6] && U[6] == 1) return true;

    for(int i = 0; i < 3; ++i)
    if (U[i] == U[i+3] && U[i+3] == U[i+6] && U[i] == 1) return true;

    for(int i = 0; i < 9; i += 3)
    if (U[i] == U[i+1] && U[i+1] == U[i+2] && U[i] == 1) return true;

    return false;
}

bool Bob_Loss(vector<int> U) {
    if (U[0] == U[4] && U[4] == U[8] && U[8] == 2) return true;
    if (U[2] == U[4] && U[4] == U[6] && U[6] == 2) return true;

    for(int i = 0; i < 3; ++i)
    if (U[i] == U[i+3] && U[i+3] == U[i+6] && U[i] == 2) return true;

    for(int i = 0; i < 9; i += 3)
    if (U[i] == U[i+1] && U[i+1] == U[i+2] && U[i] == 2) return true;

    return false;
}

bool Check_Win(vector<int> U) {
    if (Bob_Loss(U)) return false;
    
    if (U[0] != 2 && U[4] != 2 && U[8] != 2) return true;
    if (U[2] != 2 && U[4] != 2 && U[6] != 2) return true;

    for(int i = 0; i < 3; ++i)
    if (U[i] != 2 && U[i+3] != 2 && U[i+6] != 2) return true;

    for(int i = 0; i < 9; i += 3)
    if (U[i] != 2 && U[i+1] != 2 && U[i+2] != 2) return true;

    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    power[0] = 1;
    for(int i = 1; i < 9; ++i) power[i] = power[i-1] * 3;

    for(int i = 0; i < 9; ++i) {
        int x, y; cin >> x >> y;

        --x, --y;
        pos[i] = x * 3 + y;
    }

    Q.push({vector<int>(0, 0), power[pos[0]]}); tick[power[pos[0]]] = true;
    while (!Q.empty()) {
        vector<int> steps = Q.front().first;
        int u = Q.front().second;
        Q.pop();
        vector<int> U = Convert(u);

        if (Bob_Win(U)) {
            for(int step: steps) cout << (step / 3) + 1 << ' ' << (step % 3) + 1 << '\n';
            return 0;
        }

        vector<int> new_steps = steps;
        vector<int> V = U;
        int v = u;

        for(int i = 0; i < 9; ++i)
        if (V[i] == 0) {
            V[i] = 2; v += 2 * power[i];
            new_steps.push_back(i);

            if (Check_Win(V)) {
                for(int j = 0; j < 9; ++j)
                if (V[pos[j]] == 0) {
                    v += power[pos[j]];

                    if (!tick[v]) {
                        tick[v] = true;
                        Q.push({new_steps, v});
                    }

                    v -= power[pos[j]];

                    break;
                }
            }

            V[i] = 0; v -= 2 * power[i];
            new_steps.pop_back();
        }
    }

    cout << "ERROR";

    return 0;
}
