/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <cstring>
#define llong long long

using namespace std;

llong dp[100006];
int Pre[100006][26], cur[26], n;
char s[100006];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%s", s+1); n = strlen(s+1);

        for(int i = 0; i <= n+1; ++i) dp[i] = 0;
        for(int i = 0; i < 26; ++i) cur[i] = 0;

        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j < 26; ++j) Pre[i][j] = cur[j];
            cur[s[i] - 'a'] = i;

            for(int j = 0; j < 26; ++j)
            if (s[i] - 'a' != j) {
                ++dp[Pre[i][j]];
                --dp[Pre[Pre[i][j]][j]];
            }

            ++dp[i]; --dp[Pre[i][s[i]-'a']];
        }

        llong ans = 0;
        for(int i = n; i >= 1; --i) {
            dp[i] += dp[i+1];
            ans += dp[i];
        }

        cout << ans << '\n';
    }

    return 0;
}
