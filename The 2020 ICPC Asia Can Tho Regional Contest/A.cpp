/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

queue<int> Q;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int m; cin >> m;

        int res = 0;
        for(int i = 1; i <= m; ++i) res ^= i;

        if (res == m) cout << m << '\n';
        else cout << m - 1 << '\n';

        for(int i = 1; i <= m; ++i)
        if ((res ^ m) != i) cout << i << ' ';

        cout << '\n';
    }

    return 0;
}
