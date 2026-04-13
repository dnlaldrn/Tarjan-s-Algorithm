#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
private:
    int V; // Number of vertices
    vector<vector<int>> adj;
    vector<int> disc, low;
    stack<int> st;
    vector<bool> inStack;
    int timer;

public:
    TarjanSCC(int V) {
        this->V = V;
        adj.resize(V);
        disc.resize(V, -1);
        low.resize(V, -1);
        inStack.resize(V, false);
        timer = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        st.push(u);
        inStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                // If v is not visited
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (inStack[v]) {
                // Back edge
                low[u] = min(low[u], disc[v]);
            }
        }

        // If u is head of SCC
        if (disc[u] == low[u]) {
            cout << "SCC: ";
            while (true) {
                int v = st.top();
                st.pop();
                inStack[v] = false;
                cout << v << " ";
                if (v == u) break;
            }
            cout << endl;
        }
    }

    void findSCCs() {
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                dfs(i);
            }
        }
    }
};

int main() {
    TarjanSCC g(5);

    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    g.findSCCs();

    return 0;
}