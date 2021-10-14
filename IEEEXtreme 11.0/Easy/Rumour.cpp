/// hhoangcpascal

#include <iostream>
#include <algorithm>
#define llong long long

using namespace std;

int q;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> q;

    while (q--) {
        llong a, b; cin >> a >> b;

        int dist = 0;
        while (a != b) {
            ++dist;

            if (a > b) a >>= 1;
            else b >>= 1;
        }

        cout << dist << '\n';
    }

    return 0;
}
