/// hhoangcpascal
/// Generating Numbers
/// https://open.kattis.com/problems/generatingnumbers

#include <iostream>
#include <algorithm>

using namespace std;

int delta[11];

bool Full_Zero(string s) {
    for(int i = 1; i < (int) s.size(); ++i)
    if (s[i] > '0') return false;

    return true;
}

string num;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    delta[1] = 0, delta[2] = 9;
    for(int i = 3; i <= 10; ++i) delta[i] = delta[i - 1] + 10 * (i - 2) + 9;

    int t; cin >> t;
    while (t--) {
        cin >> num;
        int len = num.size();

        if (num.size() == 1) {
            cout << num[0] - '1' << '\n';
            continue;
        } else if (Full_Zero(num) && num[0] == '1') {
            cout << delta[len] << '\n';
            continue;
        }

        int res = 0;
        if (Full_Zero(num)) {
            --num[0];
            for(int i = 1; i < len; ++i) num[i] = '9';

            ++res;
        }

        bool one = false;
        if (num[0] != '1') {
            for(int i = 1; i < len - 1; ++i)
            if (num[i] == '1') {
                res += (num[len - 1] - '0') + 1;

                num[len - 1] = num[0];
                num[0] = '1'; num[i] = '0';

                one = true;
                break;
            }

            if (num[len - 1] == '1') {
                ++res;

                swap(num[len - 1], num[0]);
                one = true;
            }
        }

        if (!one) {
            if (num[len - 1] == '0') {
                ++res;

                for(int i = 1; i < len; ++i)
                if (num[i] > '0') {
                    swap(num[i], num[len - 1]);
                    break;
                }
            }

            if (num[0] != '1') {
                res += num[len - 1] - '1' + 1; num[len - 1] = '1';
                swap(num[0], num[len - 1]);
            }
        }

        for(int i = 1; i < len - 1; ++i)
        if (num[i] != '0') {
            res += num[len - 1] - '0' + 1;
            num[len - 1] = num[i];
            num[i] = '0';
        }

        res += num[len - 1] - '0'; num[len - 1] = '0';
        res += delta[len];

        cout << res << '\n';
    }

    return 0;
}
