/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define PI 3.14159265358979323846L
#define ldouble long double

using namespace std;

struct Point {
    ldouble x, y;
} P[26];

char s[1000006];
bool tick[26];

Point Get_Point(ldouble l, ldouble angle) {
    return {l * cos(angle), l * sin(angle)};
}

ldouble Get_Dist(Point A, Point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int main() {
    ldouble l; scanf("%Lf\n", &l);
    for(int i = 0; i < 26; ++i) {
        char c; ldouble angle; scanf("%c%Lf\n", &c, &angle);

        angle *= PI;
        angle /= 180.0L;

        if (!tick[c-'A']) {
            tick[c-'A'] = true;
            P[c-'A'] = Get_Point(l, angle);
        }
    }

    fgets(s, 1000000, stdin); int n = strlen(s);

    Point cur = {0.0L, 0.0L}; ldouble ans = 0;
    for(int i = 0; i < n; ++i) {
        if (s[i] < 'A' || s[i] > 'z' || ('Z' < s[i] && s[i] < 'a')) continue;

        char c = s[i];
        if (c >= 'a') c -= 32;

        ans += Get_Dist(cur, P[c-'A']);
        cur = P[c-'A'];
    }

    cout << (long long) ceil(ans);

    return 0;
}
