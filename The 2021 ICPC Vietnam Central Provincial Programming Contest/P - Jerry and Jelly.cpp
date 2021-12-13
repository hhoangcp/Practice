/// hhoangcpascal

#include <iostream>
#include <algorithm>
#define llong long long

using namespace std;

llong Solve(int x, int y, int z, int u) {
    if (min(min(x, y), z) < u) return 0;

    llong sum = 0;

    int cx = max(0, x / u - 1); x -= cx * u;
    int cy = max(0, y / u - 1); y -= cy * u;
    int cz = max(0, z / u - 1); z -= cz * u;

    sum += cx * y * z + cy * x * z + cz * x * y;
    sum += cx * cy * z * u + cx * cz * y * u + cy * cz * x * u;
    sum += cx * cy * cz * u * u;

    if (x < y) swap(x, y);
    if (x < z) swap(x, z);
    if (y < z) swap(y, z);

    sum += x * y;
    return sum;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int x, y, z, u; cin >> x >> y >> z >> u;
        cout << Solve(x, y, z, u) << '\n';
    }

    return 0;
}
