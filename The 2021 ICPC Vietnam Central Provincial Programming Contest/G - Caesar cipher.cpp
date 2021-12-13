/// hhoangcpascal

#include <iostream>
#include <algorithm>

using namespace std;

int dp[5000006], n, m;
string s;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> s; n = s.size();
    cin >> m;
    while(m--) {
        int v, a, b; cin >> v >> a >> b;

        dp[a] += v;
        dp[b+1] -= v;
    }

    for(int i = 1; i <= n; ++i) {
        dp[i] += dp[i-1];

        s[i-1] += dp[i] % 26;
        if (s[i-1] > 'Z') s[i-1] -= 26;
    }

    cout << s;
    return 0;
}
