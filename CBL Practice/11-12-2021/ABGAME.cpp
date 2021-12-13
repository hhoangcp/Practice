/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>
#define mt make_tuple
#define llong long long

using namespace std;

map<tuple<llong, llong, bool>, bool> dp;

bool Find_ans(llong a, llong b, bool turn) {
    if (b <= 1) return dp[mt(a, b, turn)] = !turn;
    if (a % b == 0) return dp[mt(a, b, turn)] = turn;
    if (dp.count(mt(a, b, turn))) return dp[mt(a, b, turn)];

    if (a >= 2 * b) {
        if (turn) return dp[mt(a, b, turn)] = !(Find_ans(b, a % b, !turn) && Find_ans(a % b + b, b, !turn));
        return dp[mt(a, b, turn)] = !(Find_ans(b, a % b, !turn) || Find_ans(a % b + b, b, !turn));
    }

    return dp[mt(a, b, turn)] = Find_ans(b, a % b, !turn);
}

int main() {
    freopen("ABGAME.INP", "r", stdin);
    freopen("ABGAME.OUT", "w", stdout);

    ios_base::sync_with_stdio(0); cin.tie(NULL);

    while (true) {
        llong a, b;
        if (!(cin >> a >> b)) return 0;
        cout << (Find_ans(max(a, b), min(a, b), true) ? "YES\n" : "NO\n");
    }

    return 0;
}
