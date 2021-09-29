/// hhoangcpascal
/// Intelligence Exchange
/// https://open.kattis.com/problems/intelligenceexchange

#include <iostream>
#include <algorithm>
#define llong long long

using namespace std;

template <typename _type_>
inline void readInt(_type_ &num) {
    register char c = getchar();
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    bool neg = (c == '-');
    if (neg) c = getchar();
    for(num = 0; '0' <= c && c <= '9'; c = getchar()) num = (num << 1) + (num << 3) + (c - '0');
    if (neg) num = -num;
}

template <typename _type_>
inline void writeInt(_type_ num) {
    if (num < 0) {
        putchar('-');
        writeInt(-num);
        return;
    }
    if (num > 9) writeInt(num / 10);
    putchar(num % 10 + '0');
}

struct TEdge {
    int u, v, c;
} E[1000006];

llong dist[4][500006], Dist[500006];
int h1, h2, s1, s2, n, m, head[500006], link[1000006];
int Heap[500006], nheap, pos[500006];

void Update(int u) {
    if (pos[u] == 0) pos[u] = ++nheap, Heap[nheap] = u;

    for(int child = pos[u], par = (child >> 1); par > 0; child = par, par >>= 1) {
        if (Dist[Heap[child]] >= Dist[Heap[par]]) break;

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
        if (child < nheap && Dist[Heap[child]] > Dist[Heap[child+1]]) ++child;
        if (Dist[Heap[child]] >= Dist[Heap[par]]) break;

        swap(pos[Heap[child]], pos[Heap[par]]);
        swap(Heap[child], Heap[par]);
    }

    return u;
}

void Dijkstra(int s) {
    nheap = 0;
    for(int i = 1; i <= n; ++i) Dist[i] = 1e18, pos[i] = 0;

    Dist[s] = 0; Update(s);
    while (nheap > 0) {
        int u = Pop();

        for(int i = head[u]; i > 0; i = link[i]) {
            int v = E[i].v;

            if (Dist[v] > Dist[u] + E[i].c) {
                Dist[v] = Dist[u] + E[i].c;
                Update(v);
            }
        }
    }
}

bool tick[500006];

int main() {
    while (true) {
        readInt(n), readInt(m);
        if (n == 0 && m == 0) break;

        readInt(h1), readInt(s1), readInt(h2), readInt(s2);

        for(int i = 1; i <= n; ++i) head[i] = 0, tick[i] = false;

        for(int i = 1; i <= m; ++i) {
            int u, v, c; readInt(u), readInt(v), readInt(c);

            E[i] = {u, v, c};
            E[i + m] = {v, u, c};

            link[i] = head[u]; head[u] = i;
            link[i+m] = head[v]; head[v] = i+m;
        }

        Dijkstra(h1);
        for(int i = 1; i <= n; ++i) dist[0][i] = Dist[i];

        Dijkstra(s1);
        for(int i = 1; i <= n; ++i) dist[1][i] = Dist[i];

        Dijkstra(h2);
        for(int i = 1; i <= n; ++i) dist[2][i] = Dist[i];

        Dijkstra(s2);
        for(int i = 1; i <= n; ++i) dist[3][i] = Dist[i];

        for(int u = 1; u <= n; ++u) {
            if (dist[0][u] + dist[1][u] > dist[1][h1]) continue;
            if (dist[2][u] + dist[3][u] > dist[3][h2]) continue;
            if (dist[0][u] == dist[2][u]) tick[u] = true;
        }

        if (h2 == h1) tick[h1] = true;
        if (!tick[s1] && dist[0][s1] <= dist[2][s1] && dist[2][s1] + dist[3][s1] == dist[3][h2]) tick[s1] = true;
        if (!tick[s2] && dist[2][s2] <= dist[0][s2] && dist[0][s2] + dist[1][s2] == dist[1][h1]) tick[s2] = true;

        int res = 0;
        for(int i = 1; i <= n; ++i)
        if (tick[i]) ++res, tick[i] = false;

        for(int i = 1; i <= m; ++i) {
            int u = E[i].u, v = E[i].v;

            if (dist[0][u] + dist[1][v] + E[i].c == dist[1][h1]
                && dist[2][u] + dist[3][v] + E[i].c == dist[3][h2] && dist[0][u] == dist[2][u]) {
                    res = -1;
                    break;
                }

            if (dist[0][v] + dist[1][u] + E[i].c == dist[1][h1]
                && dist[2][v] + dist[3][u] + E[i].c == dist[3][h2] && dist[0][v] == dist[2][v]) {
                    res = -1;
                    break;
                }

            if (dist[0][u] + dist[1][v] + E[i].c == dist[1][h1]
                && dist[2][v] + dist[3][u] + E[i].c == dist[3][h2] && abs(dist[0][u] - dist[2][v]) < E[i].c) tick[i] = true;

            if (dist[0][v] + dist[1][u] + E[i].c == dist[1][h1]
                && dist[2][u] + dist[3][v] + E[i].c == dist[3][h2] && abs(dist[0][u] - dist[2][v]) < E[i].c) tick[i] = true;
        }

        if (res != -1) {
            for(int i = 1; i <= m; ++i)
            if (tick[i]) ++res, tick[i] = false;
        }

        writeInt(res), putchar('\n');
    }

    return 0;
}
