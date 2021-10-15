/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define ldouble long double
#define M_E 2.7182818284590452354

using namespace std;

struct TEdge {
    int u, v;
    double c;
} E[1440006];

ldouble dist[360006];
double r[606][606], h[606][606];
int n, m, M, p, head[360006], link[1440006], P[36];
int nheap = 0, Heap[360006], pos[360006];

void UpHeap(int u) {
    if (pos[u] == 0) pos[u] = ++nheap, Heap[nheap] = u;

    for(int c = pos[u], p = c >> 1; p > 0; c = p, p >>= 1) {
        if(dist[Heap[p]] <= dist[Heap[c]]) break;

        swap(pos[Heap[p]], pos[Heap[c]]);
        swap(Heap[p], Heap[c]);
    }
}

int Pop_DownHeap() {
    int u = Heap[1]; pos[u] = 0;
    Heap[1] = Heap[nheap--];

    if (nheap == 0) return u;

    pos[Heap[1]] = 1;
    for(int p = 1, c = 2; c <= nheap; p = c, c <<= 1) {
        if (c < nheap && dist[Heap[c+1]] < dist[Heap[c]]) ++c;
        if(dist[Heap[p]] <= dist[Heap[c]]) break;

        swap(pos[Heap[p]], pos[Heap[c]]);
        swap(Heap[p], Heap[c]);
    }

    return u;
}

ldouble Dijkstra(int s, int t) {
    nheap = 0;
    for(int i = 0; i < n*m; ++i) pos[i] = 0, dist[i] = 1e18;

    dist[s] = 0;
    UpHeap(s);

    while (nheap > 0) {
        int u = Pop_DownHeap();

        for(int i = head[u]; i > 0; i = link[i]) {
            int v = E[i].v; double c = E[i].c;

            if (dist[v] > dist[u] + c) {
                dist[v] = dist[u] + c;
                UpHeap(v);
            }
        }
    }

    return dist[t];
}

void Add_Edge(int u, int v, double c) {
    E[++M] = {u, v, c};

    link[M] = head[u];
    head[u] = M;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> m >> p;
    for(int i = 0; i <= p; ++i) {
        int x, y; cin >> x >> y;
        P[i] = x*m+y;
    }

    for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j) cin >> r[i][j];

    for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j) {
        cin >> h[i][j];

        if (i > 0) {
            Add_Edge(i*m+j, (i-1)*m+j, (r[i][j] + r[i-1][j]) / 2.0 * pow(M_E, 3.5 * abs((h[i][j] - h[i-1][j]) / 10.0 + 0.05)));
            Add_Edge((i-1)*m+j, i*m+j, (r[i-1][j] + r[i][j]) / 2.0 * pow(M_E, 3.5 * abs((h[i-1][j] - h[i][j]) / 10.0 + 0.05)));
        }

        if (j > 0) {
            Add_Edge(i*m+j, i*m+j-1, (r[i][j] + r[i][j-1]) / 2.0 * pow(M_E, 3.5 * abs((h[i][j] - h[i][j-1]) / 10.0 + 0.05)));
            Add_Edge(i*m+j-1, i*m+j, (r[i][j-1] + r[i][j]) / 2.0 * pow(M_E, 3.5 * abs((h[i][j-1] - h[i][j]) / 10.0 + 0.05)));
        }
    }

    ldouble ans = 0;
    for(int i = 1; i <= p; ++i) ans += Dijkstra(P[i-1], P[i]);

    cout << (long long) ceil(ans);

    return 0;
}
