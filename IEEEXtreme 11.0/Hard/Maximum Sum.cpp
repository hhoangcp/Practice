/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <deque>
#define llong long long

using namespace std;

int n, a[100006], num[100006], dp[100006];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        cin >> n;
        for(int i = 1; i <= n; ++i) cin >> a[i];

        sort(a+1, a+n+1);

        deque<int> DQ; int cnt = 0;
        for(int i = 1, j = 1; i <= n; ++i)
        if (i == n || a[i] != a[i+1]) {
            a[++cnt] = a[i];
            num[cnt] = i - j + 1;
            j = i + 1;
            dp[cnt] = 0;
        }

        for(int i = 1; i <= cnt; ++i)
        if (a[i] == 0) continue;
        else if (num[i] == 1) dp[i] = dp[i-1] + 1;
        else dp[i] = 0;

        for(int i = 1; i <= num[cnt]; ++i) DQ.push_back(a[cnt]);

        for(int i = cnt-1; i >= 1;)
        if (num[i] == 1) {
            if (a[i] == 0) DQ.push_front(a[i--]);
            else if (DQ.front() != DQ.back()) {
                if (DQ.front() > DQ.back()) DQ.push_front(a[i--]);
                else DQ.push_back(a[i--]);
            } else {
                bool Right = true;
                if (dp[i] % 2) Right = false;

                int Time = dp[i];
                while (i >= 1 && num[i] == 1 && Time > 0) {
                    if (!Right) DQ.push_front(a[i]);
                    else DQ.push_back(a[i]);

                    Right = !Right;
                    --i; --Time;
                }
            }
        } else {
            if (a[i] == 0) for(int j = 1; j <= num[i]; ++j) DQ.push_front(a[i]);
            else {
                DQ.push_back(a[i]);
                for(int j = 1; j < num[i]; ++j) DQ.push_front(a[i]);
            }

            --i;
        }

        llong ans = 0; int cur = 0;
        while (!DQ.empty()) {
            ans += 1LL * a[cur] * DQ.front();

            a[++cur] = DQ.front();
            DQ.pop_front();
        }

        cout << ans << '\n';
        for(int i = 1; i <= n; ++i) cout << a[i] << ' ';
        cout << '\n';
    }

    return 0;
}
