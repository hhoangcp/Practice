/// hhoangcpascal
/// Inspecting Illumination
/// https://open.kattis.com/problems/inspectingillumination

#include <iostream>
#include <algorithm>
#include <stack>
#include <set>
#include <queue>
#include <assert.h>

using namespace std;

set<int> V[2006];
int n;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cout.flush();
    cin >> n;

    if (n == 1) {
        cout << "ANSWER 1";
        return 0;
    }

    for(int i = 1; i <= n; ++i)
    for(int j = i+1; j <= 2*n; ++j) {
        V[i].insert(j);
        V[j].insert(i);
    }

    queue<pair<int, int> > Q;
    Q.push({1, n});

    while (!Q.empty()) {
        int cur = Q.size();

        set<int> Ask;
        while (cur--) {
            int l = Q.front().first, r = Q.front().second; Q.pop();
            if (l == r) continue;

            int mid = (l + r) >> 1;
            for(int i = l; i <= mid; ++i) Ask.insert(i);

            if (l < mid) Q.push({l, mid});
            if (mid + 1 < r) Q.push({mid + 1, r});
        }

        assert(!Ask.empty());

        cout << "ASK " << Ask.size() << ' ';
        for(int v: Ask) cout << v << ' ';

        cout.flush();

        set<int> Check;
        for(int i = 0; i < (int) Ask.size(); ++i) {
            int v; cin >> v; v += n;
            Check.insert(v);
        }

        for(int u: Ask) {
            stack<int> tmp;

            for(int v: V[u])
            if (!Check.count(v)) tmp.push(v);

            while (!tmp.empty()) {
                int v = tmp.top(); tmp.pop();

                V[u].erase(V[u].find(v));
                V[v].erase(V[v].find(u));
            }
        }

        for(int u: Check) {
            stack<int> tmp;

            for(int v: V[u])
            if (!Ask.count(v)) tmp.push(v);

            while (!tmp.empty()) {
                int v = tmp.top(); tmp.pop();

                V[u].erase(V[u].find(v));
                V[v].erase(V[v].find(u));
            }
        }
    }

    cout << "ANSWER ";
    for(int u = n + 1; u <= 2 * n; ++u) cout << (*V[u].begin()) << ' ';

    return 0;
}
