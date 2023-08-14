#include <bits/stdc++.h>

#include <utility>

using namespace std;
typedef pair<int, int> iPair;

class Graph {
    vector<int> value;
    vector<bool> visited;
    int V;
    list<int> *adj;
    vector<int> max;
public:
    [[nodiscard]] const vector<int> &getMax() const {
        return max;
    }

public:
    [[nodiscard]] const vector<int> &getValue() const {
        return value;
    }

public:
    [[nodiscard]] list<int> *getAdj() const {
        return adj;
    }

public:
    explicit Graph(int V, vector<int> val) {
        this->value = val;
        this->max = val;
        this->V = V;
        adj = new list<int>[V];   //array of list adj[u] mishe list tamam yal haye u ke be shekl pair v,weight oomade
    }

    void addEdge(int u, int v) {
        u--;
        v--;
        if (max[u] > max[v])
            setmax(v, max[u]);
        if (max[u] < max[v])
            setmax(u, max[v]);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void setmax(int u, int p) {
        visited = vector<bool>(V, false);
        visited[u] = true;
        visit(u, p);
    }

    void visit(int u, int p) {
        //  cout << "max seted " << value[u] << endl;
        max[u] = p;
        for (const int &item: adj[u]) {
            //      cout << " hamsaye is :" << value[item] << endl;
            if (!visited[item]) {
                visited[item] = true;
                visit(item, p);
            }
        }
    }
};


int main() {
    int v, q;
    cin >> v >> q;
    vector<int> arr;
    for (int i = 0; i < v; ++i) {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }
    Graph G(v, arr);

    for (int i = 0; i < q; ++i) {
        int tmp;
        cin >> tmp;
        if (tmp == 2) {
            int v1, v2;
            cin >> v1 >> v2;
            G.addEdge(v1, v2);
        }
        if (tmp == 1) {
            int v3;
            cin >> v3;
            cout << G.getMax()[v3 - 1] << endl;
        }
    }
    return 0;
}


