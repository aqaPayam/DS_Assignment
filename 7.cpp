#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> iPair;

class Graph {
    int V;
    list<pair<int, int> > *adj;
public:
    list<pair<int, int>> *getAdj() const {
        return adj;
    }

public:
    explicit Graph(int V) {
        this->V = V;
        adj = new list<iPair>[V];   //array of list adj[u] mishe list tamam yal haye u ke be shekl pair v,weight oomade
    }

    void addEdge(int u, int v, int w) {
        u--;
        v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> shortestPath(int src, int target) {
        src--;
        target--;
        priority_queue<iPair, vector<iPair>, greater<> > Q; //make min heap be esm pq az Ipair ha be shekl d[],u
        vector<int> dist(V, INFINITY);  //make array dist[V]
        dist[src] = 0;
        Q.push(make_pair(dist[src], src));
        while (!Q.empty()) {
            int u = Q.top().second;
            Q.pop();
            for (const auto &item: adj[u]) {
                int v = item.first;
                int weight = item.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    Q.push(make_pair(dist[v], v));
                }
            }
        }
        return dist;

    }
};


int main() {
    int v, e, x, y;
    cin >> v;
    cin >> e;
    cin >> x;
    cin >> y;
    Graph G(2 * v);
    int *c = new int[v];
    for (int i = 0; i < v; ++i) {
        cin >> c[i];
        if (c[i] != -1)
            G.addEdge(i + 1, i + 1 + v, c[i]);
    }
    for (int i = 0; i < e; ++i) {
        int tmp1, tmp2, tmp3;
        cin >> tmp1;
        cin >> tmp2;
        cin >> tmp3;
        G.addEdge(tmp1, tmp2, tmp3);
        G.addEdge(tmp1 + v, tmp2 + v, tmp3);
    }

    vector<int> d = G.shortestPath(y + v, x);
    cout << d[x - 1] << endl;
    int u = x - 1;
    int q = y + v - 1;
    list<pair<int, int>> *adj = G.getAdj();
    bool goh = true;
    while (u != q) {
        if (goh)
            cout << u % v + 1 << " ";
        goh = true;
        int min = INFINITY;
        for (const auto &ver: adj[u]) {
            if (d[u] - d[ver.first] == ver.second) {
                if (ver.first - u == v) {
                    min = ver.first;
                    cout << 0 << " ";
                    goh = false;
                    break;
                }
                if (ver.first == q) {
                    min = ver.first;
                    cout << q % v + 1;
                    break;
                }
                if (ver.first < min)
                    min = ver.first;
            }
        }
        for (const auto &item: adj[min]) {
            if (item.first == u) {
                adj[min].remove(item);
                break;
            }
        }
        u = min;
    }

    return 0;
}

