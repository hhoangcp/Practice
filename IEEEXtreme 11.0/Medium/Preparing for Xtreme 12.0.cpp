/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dp[(1<<20) + 6];
vector<string> S, V[106];
int bit[106], w[106], n = 0;
string s;

bool Check(char c) {
    if ('A' <= c && c <= 'Z') return true;
    if ('a' <= c && c <= 'z') return true;
    if ('0' <= c && c <= '9') return true;
    return c == '_';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    while (true) {
        if (!getline(cin, s)) break;
        int len = s.size();

        int cur = 0; ++n;
        while (cur < len && '0' <= s[cur] && s[cur] <= '9')
            w[n] = (w[n] << 1) + (w[n] << 3) + (s[cur++] - '0');

        while (cur < len) {
            string t = "";
            if (!Check(s[cur])) {
                ++cur;
                continue;
            }

            while (cur < len && Check(s[cur])) t = t + s[cur++];
            V[n].push_back(t);
            S.push_back(t);
        }
    }

    sort(S.begin(), S.end());
    S.resize(unique(S.begin(), S.end()) - S.begin());

    for(int i = 1; i <= n; ++i)
    for(string j: V[i]) {
        int p = lower_bound(S.begin(), S.end(), j) - S.begin();

        bit[i] |= (1 << p);
    }

    int m = S.size();
    for(int i = 0; i < (1 << m); ++i) dp[i] = 1e9;
    dp[0] = 0;

    for(int i = 1; i <= n; ++i)
    for(int j = 0; j < (1 << m); ++j) dp[j|bit[i]] = min(dp[j|bit[i]], dp[j] + w[i]);

    cout << dp[(1 << m) - 1];
    return 0;
}
