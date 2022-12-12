#include <bits/stdc++.h>

using namespace std;

int shortest_path(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> &end) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, 1e9));
    dist[start.first][start.second] = 0;
    queue<pair<int, int>> q;
    q.push(start);
    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = -1; i <= 1; ++i) {
            for(int j = -1; j <= 1; ++j) {
                if(abs(i) + abs(j) != 1) continue;
                int nx = x + i, ny = y + j;
                if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                if(grid[nx][ny] - grid[x][y] > 1) continue;
                if(dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    return dist[end.first][end.second];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int m, n;
    cin >> m >> n;

    pair<int, int> end;
    vector<vector<int>> grid(m, vector<int>(n));
    for(int i = 0; i < m; ++i) {
        string line;
        cin >> line;
        for(int j = 0; j < n; ++j) {
            if(line[j] == 'S') grid[i][j] = 0;
            else if(line[j] == 'E') {
                grid[i][j] = 'z' - 'a';
                end = {i, j};
            } else grid[i][j] = line[j] - 'a';
        }
    }

    int best_path = INT_MAX;
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            if(grid[i][j] == 0)
                best_path = min(best_path, shortest_path(grid, {i, j}, end));

    cout << best_path << '\n';
    return 0;
}