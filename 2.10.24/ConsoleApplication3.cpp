#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V; 
    vector<vector<int>> adj; 

    // Вспомогательная функция для поиска самой дальней вершины и её расстояния
    void dfs(int node, int parent, int depth, int& maxDepth, int& farthestNode) {
        if (depth > maxDepth) {
            maxDepth = depth;
            farthestNode = node;
        }
        for (int neighbor : adj[node]) {
            if (neighbor != parent) { 
                dfs(neighbor, node, depth + 1, maxDepth, farthestNode);
            }
        }
    }

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int diameter() {
        int maxDepth = 0;
        int farthestNode = 0;

        // Первый запуск DFS для нахождения самой дальней вершины от начальной
        dfs(0, -1, 0, maxDepth, farthestNode);

        // Сбросим maxDepth для второго обхода
        maxDepth = 0;

        // Второй запуск DFS от найденной вершины
        dfs(farthestNode, -1, 0, maxDepth, farthestNode);
        return maxDepth; 
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    int V = 10;
    Graph g(V);

    // Добавляем рёбра (например, для дерева)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(2, 7);
    g.addEdge(3, 8);

    cout << "Диаметр дерева: " << g.diameter() << endl;

}