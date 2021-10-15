/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int n, m, A[16][16], a[16][16], num[4];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= m; ++j) cin >> A[i][j];

    int power = 1;
    for(int i = 1; i <= n; ++i) power *= 3;

    int res = 0;
    for(int mask = 0; mask < power; ++mask) {
        for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) a[i][j] = A[i][j];

        int tmp_mask = mask;
        for(int i = 1; i <= n; ++i) {
            int add = tmp_mask % 3;
            tmp_mask /= 3;
            for(int j = 1; j <= m; ++j) (a[i][j] += add) %= 3;
        }

        int ret = 0;
        for(int j = 1; j <= m; ++j) {
            num[0] = num[1] = num[2] = 0;
            for(int i = 1; i <= n; ++i) ++num[a[i][j]];

            ret += max(max(num[0], num[1]), num[2]);
        }

        res = max(res, ret);
    }

    cout << res;

    return 0;
}
