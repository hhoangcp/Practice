/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    int x, y;

    bool operator < (const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
} P[5];

bool CW(Point &A, Point &B, Point &C) {
    return (1LL * B.x - A.x) * (1LL * C.y - A.y) - (1LL * B.y - A.y) * (1LL * C.x - A.x) < 0;
}

bool CCW(Point &A, Point &B, Point &C) {
    return (1LL * B.x - A.x) * (1LL * C.y - A.y) - (1LL * B.y - A.y) * (1LL * C.x - A.x) > 0;
}

bool Convexhull() {
    sort(P+1, P+5);

    vector<Point> T, D;
    T.push_back(P[1]), D.push_back(P[1]);

    for(int i = 2; i <= 4; ++i)
    if (i == 4 || CW(P[1], P[i], P[4])) {
        while ((int) T.size() > 1 && !CW(T[T.size()-2], T[T.size()-1], P[i])) T.pop_back();
        T.push_back(P[i]);
    }

    for(int i = 2; i <= 4; ++i)
    if (i == 4 || CCW(P[1], P[i], P[4])) {
        while ((int) D.size() > 1 && !CCW(D[D.size()-2], D[D.size()-1], P[i])) D.pop_back();
        D.push_back(P[i]);
    }

    return (int) T.size() + D.size() - 2 == 4;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        for(int i = 1; i <= 4; ++i) cin >> P[i].x >> P[i].y;

        bool ok = Convexhull();
        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
