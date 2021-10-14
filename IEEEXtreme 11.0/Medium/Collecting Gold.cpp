/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

const llong mul[15] = {2, 6, 30, 210, 2310, 30030, 510510, 9699690, 223092870, 6469693230, 200560490130,
                        7420738134810, 304250263527210, 13082761331670030, 614889782588491410};

struct TEdge {
    int v, c;
};

struct Data {
    llong dist;
    int kilos;

    bool operator <= (const Data &other) const {
        if (dist != other.dist) return dist < other.dist;
        return kilos >= other.kilos;
    }

    bool operator > (const Data &other) const {
        if (dist != other.dist) return dist > other.dist;
        return kilos < other.kilos;
    }
};

vector<TEdge> V[20006];
Data d[20006];
llong id[20006], sorted[20006];
int n, m, nheap = 0, Heap[20006], pos[20006], delta[20006];

void Update(int u) {
    if (pos[u] == 0) pos[u] = ++nheap, Heap[nheap] = u;

    for(int child = pos[u], par = (child >> 1); par > 0; child = par, par >>= 1) {
        if (d[Heap[par]] <= d[Heap[child]]) break;

        swap(pos[Heap[child]], pos[Heap[par]]);
        swap(Heap[child], Heap[par]);
    }
}

int Pop() {
    int u = Heap[1]; pos[u] = 0;
    Heap[1] = Heap[nheap--];

    if (nheap == 0) return u;

    pos[Heap[1]] = 1;
    for(int child = 2, par = 1; child <= nheap; par = child, child <<= 1) {
        if (child < nheap && d[Heap[child]] > d[Heap[child+1]]) ++child;
        if (d[Heap[par]] <= d[Heap[child]]) break;

        swap(pos[Heap[child]], pos[Heap[par]]);
        swap(Heap[child], Heap[par]);
    }

    return u;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        cin >> id[i];
        sorted[i] = id[i];
    }

    sort(sorted+1, sorted+n+1);
    for(int i = 1; i <= n; ++i) {
        d[i] = {(llong) 1e18, -1};
        delta[i] = upper_bound(mul, mul+15, id[i]) - mul;
    }

    for(int i = 1; i <= m; ++i) {
        int u, v, c; cin >> u >> v >> c;

        u = lower_bound(sorted + 1, sorted + n + 1, u) - sorted;
        v = lower_bound(sorted + 1, sorted + n + 1, v) - sorted;

        V[u].push_back({v, c});
        V[v].push_back({u, c});
    }

    d[1] = {0LL, delta[1]};
    Update(1);

    while (nheap > 0) {
        int u = Pop();

        for(int i = 0; i < (int) V[u].size(); ++i) {
            int v = V[u][i].v, c = V[u][i].c;

            Data New = {d[u].dist + c, d[u].kilos + delta[v]};
            if (d[v] > New) {
                d[v] = New;
                Update(v);
            }
        }
    }

    cout << d[n].kilos;

    return 0;
}
