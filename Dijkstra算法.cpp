#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

// 定义无穷大值
const int INF = numeric_limits<int>::max();

// 图的邻接表表示
class Graph
{
private:
    int vertices;
    vector<vector<pair<int, int>>> adj; // 邻接表：目标顶点，权重

public:
    Graph(int v) : vertices(v), adj(v) {}

    // 添加边
    void addEdge(int u, int v, int weight)
    {
        adj[u].emplace_back(v, weight);
        // 如果是无向图，取消下面这行的注释
        // adj[v].emplace_back(u, weight);
    }

    // Dijkstra算法实现
    vector<int> dijkstra(int source)
    {
        // 初始化距离数组
        vector<int> dist(vertices, INF);
        dist[source] = 0;

        // 使用优先队列（最小堆），存储：距离，顶点
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, source);

        while (!pq.empty())
        {
            auto [currentDist, u] = pq.top(); // C++17结构化绑定
            pq.pop();

            // 如果当前距离不是最短距离，跳过
            if (currentDist > dist[u])
            {
                continue;
            }

            for (const auto &[v, weight] : adj[u])
            {
                int newDist = dist[u] + weight;

                if (newDist < dist[v])
                {
                    dist[v] = newDist;
                    pq.emplace(newDist, v);
                }
            }
        }

        return dist;
    }

    void printShortestPaths(const vector<int> &dist, int source)
    {
        cout << "从顶点 " << source << " 到各顶点的最短距离：" << endl;
        for (int i = 0; i < vertices; ++i)
        {
            if (dist[i] == INF)
            {
                cout << "顶点 " << i << ": 不可达" << endl;
            }
            else
            {
                cout << "顶点 " << i << ": " << dist[i] << endl;
            }
        }
    }
};

// 另一种实现：返回路径信息的Dijkstra算法
vector<pair<int, vector<int>>> dijkstraWithPath(Graph &graph, int source)
{
    int vertices = 0; // 这里需要根据实际情况设置顶点数
    vector<int> dist(vertices, INF);
    vector<int> prev(vertices, -1);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, source);

    while (!pq.empty())
    {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist > dist[u])
        {
            continue;
        }

        // 这里需要访问图的邻接表，简化实现
        // 实际使用时需要修改以适应具体的图结构
    }

    // 构建路径
    vector<pair<int, vector<int>>> result;
    for (int i = 0; i < vertices; ++i)
    {
        vector<int> path;
        if (dist[i] != INF)
        {
            // 回溯构建路径
            for (int at = i; at != -1; at = prev[at])
            {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
        }
        result.emplace_back(dist[i], path);
    }

    return result;
}

int main()
{
    // 创建图示例
    Graph graph(6);

    // 添加边
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);

    // 计算从顶点0开始的最短路径
    int source = 0;
    vector<int> distances = graph.dijkstra(source);

    // 打印结果
    graph.printShortestPaths(distances, source);

    return 0;
}
