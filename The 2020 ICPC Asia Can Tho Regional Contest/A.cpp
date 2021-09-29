/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int n, res = 0;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n;

    char pre = '0';
    for(int i = 1; i <= n; ++i) {
        char c; cin >> c;

        if (c == pre) ++res;
        pre = c;
    }

    cout << res;

    return 0;
}
