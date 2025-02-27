#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <deque>

using namespace std;

struct Node {
    int x, y, cost;
};

inline int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int astar(const vector<string>& grid, int n, int m, int x1, int y1, int x2, int y2) {
    static const int dx[] = {-1, 1, 0, 0};
    static const int dy[] = {0, 0, -1, 1};

    vector<int> dist(n * m, numeric_limits<int>::max());
    vector<bool> visited(n * m, false);
    deque<Node> dq;

    auto index = [&](int x, int y) { return x * m + y; };

    dq.push_front({x1, y1, 0});
    dist[index(x1, y1)] = 0;

    while (!dq.empty()) {
        Node node = dq.front();
        dq.pop_front();

        if (node.x == x2 && node.y == y2) return node.cost;
        if (visited[index(node.x, node.y)]) continue;
        visited[index(node.x, node.y)] = true;

        for (int i = 0; i < 4; i++) {
            int nx = node.x + dx[i], ny = node.y + dy[i];
            int idx = index(nx, ny);

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.') {
                int new_cost = node.cost + 1;

                if (new_cost < dist[idx]) {
                    dist[idx] = new_cost;
                    if (heuristic(nx, ny, x2, y2) < heuristic(node.x, node.y, x2, y2)) {
                        dq.push_front({nx, ny, new_cost});
                    } else {
                        dq.push_back({nx, ny, new_cost});
                    }
                }
            }
        }
    }
    
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int q;
    cin >> q;
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << astar(grid, n, m, x1 - 1, y1 - 1, x2 - 1, y2 - 1) << "\n";
    }

    return 0;
}
