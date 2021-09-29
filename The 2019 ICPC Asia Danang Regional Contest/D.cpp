/// hhoangcpascal
/// Dating time
/// https://open.kattis.com/problems/datingtime

#include <iostream>
#include <algorithm>

using namespace std;

const int limit[3] = {22, 44, 22};

struct Cal {
    int a, N, b;
} P[3];

string S;

int main() {
    P[0] = {720, 1, 0};
    P[1] = {180, 2, 180};
    P[2] = {720, 1, 360};

    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);

    int t = 0; cin >> t;
    while (t--) {
        cin >> S;
        int A = (((S[0]-'0') * 10 + (S[1]-'0')) * 60 + ((S[3]-'0') * 10 + (S[4]-'0'))) * 11;

        cin >> S;
        int B = (((S[0]-'0') * 10 + (S[1]-'0')) * 60 + ((S[3]-'0') * 10 + (S[4]-'0'))) * 11;

        int angle, res = 0; cin >> angle; angle /= 90;

        for(int i=0; i < limit[angle]; ++i) {
            int del = P[angle].a * (i * P[angle].N) + P[angle].b;

            if (A <= del && del <= B) ++res;
        }

        cout << res << '\n';
    }

    return 0;
}
