#include <bits/stdc++.h>

using namespace std;

bool pour(vector<vector<char>>& grid, pair<int, int> source) {
    pair<int, int> source_copy = source;
    int m = grid.size(), n = grid[0].size();
    while(true) {
        if(source.second + 1 < m && grid[source.second + 1][source.first] == '.')
            ++source.second;
        else if(source.first - 1 >= 0 && grid[source.second + 1][source.first - 1] == '.') {
            ++source.second;
            --source.first;
        } else if(source.first + 1 < n && grid[source.second + 1][source.first + 1] == '.') {
            ++source.second;
            ++source.first;
        } else {
            grid[source.second][source.first] = 'o';
            if (source.first == source_copy.first && source.second == source_copy.second) return false;
            return true;
        }
    }   
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    cin.ignore();


    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < n; ++i) {
        string line, piece;
        int x, y;
        getline(cin, line);
        stringstream ss(line);
        while((ss >> x >> y)) adj[i].push_back({x, y});
    }
    int min_x = 500, min_y = 0, max_x = 500, max_y = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < adj[i].size(); ++j) {
            min_x = min(min_x, adj[i][j].first);
            min_y = min(min_y, adj[i][j].second);
            max_x = max(max_x, adj[i][j].first);
            max_y = max(max_y, adj[i][j].second);
        }
    }
    min_x -= 1000;
    max_x += 1000;
    max_y += 2;


    vector<vector<char>> grid(max_y - min_y + 1, vector<char>(max_x - min_x + 1, '.'));
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < adj[i].size(); ++j) {
            int x1 = adj[i][j - 1].first - min_x, y1 = adj[i][j - 1].second - min_y;
            int x2 = adj[i][j].first - min_x, y2 = adj[i][j].second - min_y;
            if(x1 == x2) for(int y = min(y1, y2); y <= max(y1, y2); ++y) grid[y][x1] = '#';
            else for(int x = min(x1, x2); x <= max(x1, x2); ++x) grid[y1][x] = '#';
        }
    }
    for(int x = 0; x < grid[0].size(); ++x) grid[grid.size() - 1][x] = '#';
    
    pair<int, int> source = {500 - min_x, 0};
    int i = 0;
    while(pour(grid, source)) ++i;
    cout << (i+1) << '\n';
    return 0;
}