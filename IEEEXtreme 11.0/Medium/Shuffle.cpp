/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<int> V[206];
int n, match[206];
char inp[100006];
bool tick[206];

bool DFS(int u) {
    for(int v: V[u])
    if (!tick[v]) {
        tick[v] = true;

        if (match[v] == 0 || DFS(match[v])) {
            match[v] = u;
            return true;
        }
    }

    return false;
}

int main() {
    scanf("%d\n", &n);
    for(int u = 1; u <= n; ++u) {
        for(int v = 1; v <= n; ++v) tick[v] = false;
        tick[u] = true;

        fgets(inp, 100000, stdin);
        int len = strlen(inp);

        int num = 0;
        for(int i = 0; i < len; ++i)
        if ('0' <= inp[i] && inp[i] <= '9') {
            num = (num << 1) + (num << 3) + (inp[i] - '0');

            if (i == len - 1 || inp[i+1] < '0' || inp[i+1] > '9') {
                tick[num+1] = true;
                num = 0;
            }
        }

        for(int v = 1; v <= n; ++v)
        if (!tick[v]) V[u].push_back(v);
    }

    vector<int> tmp;
    for(int i = 1; i <= n; ++i) tmp.push_back(i);

    int max_matching = 0;
    while(true) {
        bool stop = true;

        for(int i = 1; i <= n; ++i) tick[i] = false;

        for(int i = tmp.size() - 1; i >= 0; --i)
        if (DFS(tmp[i])) {
            stop = false;
            ++max_matching;
            tmp[i] = tmp.back();
            tmp.pop_back();
        }

        if (stop) break;
    }

    cout << n - max_matching;

    return 0;
}
