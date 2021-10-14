/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

struct Data {
    string s;
    int val;

    bool operator < (const Data &other) const {
        if (val != other.val) return val < other.val;
        return s < other.s;
    }
} D[1006];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int n; cin >> n;
    for(int i = 1; i <= n; ++i) {
        string s; int val; cin >> s >> val;
        D[i] = {s, val};
    }

    sort(D+1, D+n+1);

    for(int i = 1, j = 1; i <= n; ++i) {
        cout << D[i].s << ' ';

        if (i == n || D[i].val < D[i+1].val) {
            cout << j << ' ' << i << '\n';
            j = i + 1;
        }
    }

    return 0;
}
