#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int m, n;
    cin >> m >> n;

    pair<int, int> start, end;
    vector<vector<int>> grid(m, vector<int>(n));
    for(int i = 0; i < m; ++i) {
        string line;
        cin >> line;
        for(int j = 0; j < n; ++j) {
            if(line[j] == 'S') {
                grid[i][j] = 0;
                start = {i, j};
            } else if(line[j] == 'E') {
                grid[i][j] = 'z' - 'a';
                end = {i, j};
            } else grid[i][j] = line[j] - 'a';
        }
    }

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

    cout << dist[end.first][end.second] << '\n';
    return 0;
}