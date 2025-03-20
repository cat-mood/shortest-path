#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>

using Graph = std::unordered_map<uint64_t, std::vector<uint64_t>>;
const std::string FILENAME = "graph.txt";

std::vector<uint64_t> BFS(Graph& graph, uint64_t start) {
    std::queue<std::pair<uint64_t, uint64_t>> q;
    std::vector<uint64_t> visited(graph.size(), 0);
    q.emplace(start, 0);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (visited[cur.first] == 0) {
            visited[cur.first] = cur.second;
        }
        for (uint64_t v : graph[cur.first]) {
            if (visited[v] == 0 && v != start) {
                q.emplace(v, cur.second + 1);
            }
        }
    }

    return visited;
}

int main() {
    std::ifstream file(FILENAME);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << FILENAME << std::endl;
        return -1;
    }

    uint64_t V, E;
    file >> V >> E;
    Graph graph;
    for (uint64_t i = 0; i < E; i++) {
        uint64_t u, v;
        file >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    uint64_t start;
    file >> start;
    file.close();

    auto result = BFS(graph, start);
    for (uint64_t element : result) {
        std::cout << element << std::endl;
    }

    return 0;
}
