/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> BigInt;

BigInt Plus(BigInt A, BigInt B) {
    while (A.size() < B.size()) A.push_back(0);
    while (A.size() > B.size()) B.push_back(0);

    int tmp = 0; BigInt C(0);
    for(int i=0; i<(int) A.size(); ++i) {
        C.push_back(A[i] + B[i] + tmp);
        tmp = C[i] / 10;
        C[i] %= 10;
    }

    if (tmp) C.push_back(tmp);

    return C;
}

vector<int> pos[22006];
BigInt ans[6];
int q, Q[6];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> q;
    for(int i = 1; i <= q; ++i) {
        cin >> Q[i];
        pos[Q[i]].push_back(i);
    }

    BigInt val0, val1; val0.assign(1, 1), val1.assign(1, 1);
    for(int id: pos[0]) ans[id] = val0;
    for(int id: pos[1]) ans[id] = val1;

    for(int i = 2; i <= 22000; ++i) {
        BigInt val2 = Plus(val1, val0);
        for(int id: pos[i]) ans[id] = val2;
        val0 = val1, val1 = val2;
    }

    for(int i = 1; i <= q; ++i) {
        for(int j = ans[i].size()-1; j >= 0; --j) cout << ans[i][j];
        cout << '\n';
    }

    return 0;
}
