#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> iPair;

class Graph {
    int V;
    list<pair<int, int> > *adj;
public:
    explicit Graph(int V) {
        this->V = V;
        adj = new list<iPair>[V];   //array of list adj[u] mishe list tamam yal haye u ke be shekl pair v,weight oomade
    }

    void addEdge(int u, int v, int w) {
        u--;
        v--;
        adj[u].emplace_back(v, w);
    }

    int shortestPath(int src, int target) {
        src--;
        target--;
        priority_queue<iPair, vector<iPair>, greater<> > Q; //make min heap be esm pq az Ipair ha be shekl d[],u
        vector<int> dist(V, INFINITY);  //make array dist[V]
        dist[src] = 0;
        Q.push(make_pair(dist[src], src));
//        for (int i = 0; i < V; ++i)
//            pq.push(make_pair(dist[i], i));

        while (!Q.empty()) {
            int u = Q.top().second;
            if (u == target)
                break;
            Q.pop();
            for (const auto &item: adj[u]) {
                int v = item.first;
                int weight = item.second;

                //relaxing
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    Q.push(make_pair(dist[v], v));
                }
            }
        }
        return dist[target];

    }
};

int main() {
    int v, e, x, y;
    cin >> v;
    cin >> e;
    cin >> x;
    cin >> y;
    Graph G(v);
    for (int i = 0; i < e; ++i) {
        int tmp1, tmp2;
        cin >> tmp1;
        cin >> tmp2;
        G.addEdge(tmp1, tmp2, 0);
        G.addEdge(tmp2, tmp1, 1);
    }
    cout << G.shortestPath(x, y);
    return 0;
}