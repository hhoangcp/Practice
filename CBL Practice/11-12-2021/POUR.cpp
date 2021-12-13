/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

map<pair<int, int>, bool> M;
map<pair<int, int>, bool> visited;

void Print_ans(vector<pair<int, int>> ans) {
    cout << ans.size() << '\n';
    for(pair<int, int> u: ans) cout << u.first << ' ' << u.second << '\n';
}

vector<pair<int, int>> ans;

void Create_ans(int v1, int v2, int v3) {
    if (M[{v2, v3}]) {
        while (v2 != 0 && v3 != 0) {
            if (v2 >= v3) {
                ans.push_back({2, 3});
                v2 -= v3, v3 <<= 1;
            } else {
                ans.push_back({3, 2});
                v3 -= v2, v2 <<= 1;
            }
        }

        Print_ans(ans);
    } else if (M[{v1, v3}]) {
        while (v1 != 0 && v3 != 0) {
            if (v1 >= v3) {
                ans.push_back({1, 3});
                v1 -= v3, v3 <<= 1;
            } else {
                ans.push_back({3, 1});
                v3 -= v1, v1 <<= 1;
            }
        }

        Print_ans(ans);
    } else {
        while (v1 != 0 && v2 != 0) {
            if (v1 >= v2) {
                ans.push_back({1, 2});
                v1 -= v2, v2 <<= 1;
            } else {
                ans.push_back({2, 1});
                v2 -= v1, v1 <<= 1;
            }
        }

        Print_ans(ans);
    }
}

bool Visited(int v1, int v2, int v3) {
    if (v1 < v2) swap(v1, v2);
    if (v1 < v3) swap(v1, v3);
    if (v2 < v3) swap(v2, v3);

    if (visited.count({v1, v2})) return true;

    visited[{v1, v2}] = true;
    return false;
}

void Test(int a, int b) {
    if (M.count({a, b}) || M.count({b, a})) return;

    M[{a, b}] = M[{b, a}] = true;
    if (a & 1) return;

    if (a > b) Test(a >> 1, b + (a >> 1));
    else Test(a + (b >> 1), b >> 1);
}

bool Backtrack(int v1, int v2, int v3) {
    if (M.count({v1, v2}) || M.count({v2, v3}) || M.count({v1, v3})) {
        Create_ans(v1, v2, v3);
        return true;
    }

    int g = __gcd(__gcd(v1, v2), v3);
    v1 /= g, v2 /= g, v3 /= g;

    if (v1 > v2) {
        if (!Visited(v1 - v2, 2 * v2, v3)) {
            ans.push_back({1, 2});
            if (Backtrack(v1 - v2, 2 * v2, v3)) return true;
            ans.pop_back();
        }
    } else if (!Visited(v1 * 2, v2 - v1, v3)) {
        ans.push_back({2, 1});
        if (Backtrack(v1 * 2, v2 - v1, v3)) return true;
        ans.pop_back();
    }

    if (v2 > v3) {
        if (!Visited(v1, v2 - v3, 2 * v3)) {
            ans.push_back({2, 3});
            if (Backtrack(v1, v2 - v3, 2 * v3)) return true;
            ans.pop_back();
        }
    } else if (!Visited(v1, v2 * 2, v3 - v2)) {
        ans.push_back({3, 2});
        if (Backtrack(v1, v2 * 2, v3 - v2)) return true;
        ans.pop_back();
    }

    if (v1 > v3) {
        if (!Visited(v1 - v3, v2, 2 * v3)) {
            ans.push_back({1, 3});
            if (Backtrack(v1 - v3, v2, 2 * v3)) return true;
            ans.pop_back();
        }
    } else if (!Visited(v1 * 2, v2, v3 - v1)) {
        ans.push_back({3, 1});
        if (Backtrack(v1 * 2, v2, v3 - v1)) return true;
        ans.pop_back();
    }

    return false;
}

int main() {
    freopen("POUR.INP", "r", stdin);
    freopen("POUR.OUT", "w", stdout);

    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int v1, v2, v3; cin >> v1 >> v2 >> v3;

    for(int i = 1; i <= (v1 + v2 + v3) / 2; ++i)
    for(int j = 1; (1 << j) * i < v1 + v2 + v3; ++j) Test(i, (1 << j) * i - i);

    Visited(v1, v2, v3);
    Backtrack(v1, v2, v3);

    return 0;
}
