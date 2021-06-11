#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;

struct Edge {
    Edge(long long to, long long cost): to(to), cost(cost) {}

    long long to;
    long long cost;
};

using Graph = vector<vector<Edge>>;
using P = pair<long, int>;
const long long INF = 1LL << 60;

/* dijkstra(G, s, dis)
 * 副作用：disが書き換えられる。*/
void dijkstra(const Graph &g, int start, int end, vector<long long> &dis, vector<int> &prev) {
    int n = g.size();
    dis.resize(n, INF);
    prev.resize(n, -1);
    priority_queue<P, vector<P>, greater<P>> pq;
    dis[start] = 0;
    pq.emplace(dis[start], start);
    while(!pq.empty()) {
        P p = pq.top();
        pq.pop();
        int v = p.second;
        if (dis[v] < p.first) {
            continue;
        }

        if (v == end) {
            return;
        }

        for (auto &e: g[v]) {
            if (dis[e.to] > dis[v] + e.cost) {
                dis[e.to] = dis[v] + e.cost;
                prev[e.to] = v;
                pq.emplace(dis[e.to], e.to);
            }
        }
    }
}

vector<int> get_path(const vector<int> &prev, int t) {
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    Graph g;
    vector<Edge> v0 {Edge(2,10), Edge(1, 1)};
    vector<Edge> v1 {Edge(3, 2)};
    vector<Edge> v2 {Edge(1, 1), Edge(3, 3), Edge(4,1)};
    vector<Edge> v3 {Edge(0, 7), Edge(4, 4), Edge(2, 1)};
    vector<Edge> v4;

    g.push_back(v0);
    g.push_back(v1);
    g.push_back(v2);
    g.push_back(v3);
    g.push_back(v4);

    int start = 0;
    int end = 4;

    vector<long long> dis;
    vector<int> path;
    dijkstra(g, start, end,  dis, path);
    vector<int> ansPath = get_path(path, end);
    for (auto &p: ansPath) {
        cout << p << "->";
    }
    cout << "goal" << endl;

    return 0;
}
