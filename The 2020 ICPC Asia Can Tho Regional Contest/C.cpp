/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

struct Data {
    llong x, y;
} P[7];

llong a, b, c1, c2;
int n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        cin >> a >> b >> c1 >> c2;

        cin >> n;
        for(int i = 1; i <= n; ++i) cin >> P[i].x >> P[i].y;

        vector <llong> S;

        for(int i = 1; i <= n; ++i) {
            S.push_back(a * P[i].x + b * P[i].y - c1);
            S.push_back(a * P[i].x + b * P[i].y - c2);
        }

        sort(S.begin(), S.end());
        if (S[0] * S[2 * n - 1] < 0) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
