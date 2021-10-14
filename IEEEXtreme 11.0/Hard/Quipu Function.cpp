/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

llong a, b, del[100006], Div[100006];
int t;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> t >> a >> b;
    for(llong i = a; i <= b; ++i) del[i-a] = i, Div[i-a] = 1;

    for(int i = 2; 1LL * i * i <= b; ++i)
    for(llong j = max(1LL * i * i, (a + i - 1) / i * i); j <= b; j += i) {
        int num = 0;
        while (del[j-a] % i == 0) {
            del[j-a] /= i;
            ++num;
        }

        Div[j-a] *= (num + 1);
    }

    for(llong i = a; i <= b; ++i)
    if (del[i-a] > 1) Div[i-a] *= 2;

    while (t--) {
        int d; cin >> d;

        llong ans = 0;
        for(llong i = a; i <= b; ++i) {
            int num = 0; llong x = i;

            while (x % d == 0) {
                x /= d;
                ++num;
            }

            ans += Div[i-a] / (num + 1);
        }

        cout << ans << '\n';
    }

    return 0;
}
