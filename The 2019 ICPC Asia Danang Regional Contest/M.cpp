/// hhoangcpascal
/// Moscow Dream
/// https://open.kattis.com/problems/moscowdream

#include <iostream>
#include <algorithm>
#define llong long long

using namespace std;

llong a, b, c, n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> a >> b >> c >> n;
    if (min(min(a, b), c) > 0 && a + b + c >= n && n >= 3) cout << "YES"; else cout << "NO";

    return 0;
}
