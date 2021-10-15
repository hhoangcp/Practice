/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const char csymbol[3] = {'+', 'x', '*'};

struct Point {
    int x, y;
};

int m, n;
char a[1006][1006], A[1006][1006];

vector<Point> Neighbors(int x, int y, char Symbol) {
    vector<Point> ans;

    if (Symbol == '+') {
        if (x - 1 >= 1) ans.push_back({x - 1, y});
        if (x + 1 <= m) ans.push_back({x + 1, y});
        if (y - 1 >= 1) ans.push_back({x, y - 1});
        if (y + 1 <= n) ans.push_back({x, y + 1});

        return ans;
    }

    if (Symbol == 'x') {
        if (x - 1 >= 1 && y - 1 >= 1) ans.push_back({x - 1, y - 1});
        if (x - 1 >= 1 && y + 1 <= n) ans.push_back({x - 1, y + 1});
        if (x + 1 <= m && y - 1 >= 1) ans.push_back({x + 1, y - 1});
        if (x + 1 <= m && y + 1 <= n) ans.push_back({x + 1, y + 1});

        return ans;
    }

    vector<Point> tmp1;

    tmp1 = Neighbors(x, y, '+');
    for(Point p: tmp1) ans.push_back(p);

    tmp1 = Neighbors(x, y, 'x');
    for(Point p: tmp1) ans.push_back(p);

    return ans;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);

        for(int i = 1; i <= m; ++i) scanf("%s", A[i] + 1);

        for(int c = 0; c < 3; ++c) {
            int ans = 0;

            for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j) a[i][j] = A[i][j];

            for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j) {
                if (a[i][j] == '0') continue;

                queue<Point> Q; Q.push({i, j}); a[i][j] = '0'; ++ans;
                while (!Q.empty()) {
                    Point u = Q.front(); Q.pop();

                    vector<Point> neighbors = Neighbors(u.x, u.y, csymbol[c]);
                    for(Point v: neighbors) {
                        if (a[v.x][v.y] == '0') continue;

                        a[v.x][v.y] = '0';
                        Q.push(v);
                    }
                }
            }

            cout << ans << ' ';
        }

        cout << '\n';
    }

    return 0;
}
