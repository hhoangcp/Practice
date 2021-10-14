/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

char s[1000006], p[106];
int n, m, q, Pre[26][1000006];

void Init() {
    for(int i = 0; i < 26; ++i) {
        int cur = -1;

        for(int j = 1; j <= n; ++j) {
            Pre[i][j] = cur;
            if (s[j] - 'a' == i) cur = j;
        }

        Pre[i][n+1] = cur;
    }
}

int main() {
    scanf("%s", s+1); n = strlen(s+1);
    Init();

    scanf("%d", &q);
    while (q--) {
        scanf("%s", p+1); m = strlen(p+1);

        int cur = n+1, ans = 0;
        for(int i = m; i >= 1; --i) {
            int c = p[i] - 'a';

            if (Pre[c][cur] < 1) break;

            cur = Pre[c][cur];
            ++ans;
        }

        cout << ans << '\n';
    }

    return 0;
}
