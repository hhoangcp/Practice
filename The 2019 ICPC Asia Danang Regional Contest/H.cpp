/// hhoangcpascal
/// Hanjie
/// https://open.kattis.com/problems/hanjie

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

vector<int> R[9], C[9];
int r, c, a[9][9], tmp[9][9];

int Checking() {
    for(int i = 0; i < r; ++i)
    for(int j = 0; j < c; ++j) tmp[i+1][j+1] = a[i][j] + tmp[i+1][j];

    for(int j = 1; j <= c; ++j) {
        int cur = 0;

        for(int i = 1, l = 1; i <= r; ++i)
        if (i == r || tmp[i][j] != tmp[i+1][j]) {
            if (tmp[i][j] == 1) {
                if (cur >= (int) C[j-1].size()) return 0;
                if (i - l + 1 != C[j-1][cur]) return 0;
                ++cur;
            } else if (i - l + 1 == 0) return 0;

            l = i + 1;
        }

        if (cur < (int) C[j-1].size()) return 0;
    }

    return 1;
}

int res = 0;

void Try(int Row) {
    if (Row >= r) {
        res += Checking();
        return;
    }

    if ((int) R[Row].size() >= min(4, (c + 1) / 2 + 1)) return;

    if (R[Row].size() == 0) Try(Row + 1);
    else if (R[Row].size() == 1) {
        for(int i = 0; i <= c - R[Row][0]; ++i) {
            a[Row][i] += 1;
            a[Row][i+R[Row][0]] -= 1;

            Try(Row + 1);

            a[Row][i] -= 1;
            a[Row][i+R[Row][0]] += 1;
        }
    } else if (R[Row].size() == 2) {
        for(int i = 0; i <= c - R[Row][0]; ++i) {
            a[Row][i] += 1;
            a[Row][i+R[Row][0]] -= 1;

            for(int j = i + R[Row][0] + 1; j <=  c - R[Row][1]; ++j) {
                a[Row][j] += 1;
                a[Row][j+R[Row][1]] -= 1;

                Try(Row + 1);

                a[Row][j] -= 1;
                a[Row][j+R[Row][1]] += 1;
            }

            a[Row][i] -= 1;
            a[Row][i+R[Row][0]] += 1;
        }
    } else {
        for(int i = 0; i <= c - R[Row][0]; ++i) {
            a[Row][i] += 1;
            a[Row][i+R[Row][0]] -= 1;

            for(int j = i + R[Row][0] + 1; j <=  c - R[Row][1]; ++j) {
                a[Row][j] += 1;
                a[Row][j+R[Row][1]] -= 1;

                for(int k = j + R[Row][1] + 1; k <= c - R[Row][2]; ++k) {
                    a[Row][k] += 1;
                    a[Row][k+R[Row][2]] -= 1;

                    Try(Row + 1);

                    a[Row][k] -= 1;
                    a[Row][k+R[Row][2]] += 1;
                }

                a[Row][j] -= 1;
                a[Row][j+R[Row][1]] += 1;
            }

            a[Row][i] -= 1;
            a[Row][i+R[Row][0]] += 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> r >> c;

    for(int i = 0; i < r; ++i) {
        int k; cin >> k;

        while (k--) {
            int a; cin >> a;
            R[i].push_back(a);
        }
    }

    for(int i = 0; i < c; ++i) {
        int k; cin >> k;

        while (k--) {
            int a; cin >> a;
            C[i].push_back(a);
        }
    }

    Try(0);

    cout << res;

    return 0;
}
