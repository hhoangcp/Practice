/// hhoangcpascal
/// Abstract Painting
/// https://open.kattis.com/problems/abstractpainting

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

const llong mod = 1e9+7;
int r, c;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int r, c; cin >> r >> c;

        llong res = 1;
        for(int i = 1; i <= r; ++i) (res *= 3) %= mod;
        for(int i = 1; i <= c; ++i) (res *= 3) %= mod;
        for(int i = 1; i <= r*c; ++i) (res *= 2) %= mod;

        cout << res << '\n';
    }

    return 0;
}
