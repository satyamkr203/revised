#include<iostream>
#include<vector>
#include<unordered_set>
#include<queue>
#include<algorithm>
using namespace std;

void bfs(int start, vector<vector<int>>& adj, vector<int>& parent, vector<int>& depth) {
    queue<int> q;
    q.push(start);
    parent[start] = -1;
    depth[start] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (parent[neighbor] == -1 && neighbor != start) {
                parent[neighbor] = node;
                depth[neighbor] = depth[node] + 1;
                q.push(neighbor);
            }
        }
    }
}
vector<int> getPath(int start, int end, vector<int>& parent) {
    vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return path;
}
int minTimeToVisit(int n, vector<int>& u, vector<int>& v, int start, int end, vector<int>& tasks) {
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < u.size(); i++) {
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }

    vector<int> parent(n+1, -1);
    vector<int>depth(n+1, 0);
    bfs(start, adj, parent, depth);

    vector<int> main_path = getPath(start, end, parent);
    unordered_set<int> main_path_nodes(main_path.begin(), main_path.end());

    int main_path_length = main_path.size() - 1, extra_steps = 0;
    for (int task : tasks) {
        if (!main_path_nodes.count(task)) {
            int dist = 0, cur = task;
            while (!main_path_nodes.count(cur)) {
                cur = parent[cur];
                dist++;
            }
            extra_steps += 2 * dist;
        }
    }
    return main_path_length + extra_steps;
}

