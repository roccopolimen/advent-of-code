#include <bits/stdc++.h>

using namespace std;

int main() {

    int line_num = 0;
    string line;
    getline(cin, line);
    vector<vector<int>> grid(line.size(), vector<int>(line.size()));

    do {
        for (int i = 0; i < line.size(); i++)
            grid[line_num][i] = line[i] - '0';
        ++line_num;
    } while(getline(cin, line));

    int sum = 2*grid.size() + 2*grid[0].size() - 4;
    for(int i = 1; i < grid.size()-1; ++i) {
        for(int j = 1; j < grid[0].size()-1; ++j) {
            for(int l = i-1; l >= 0; --l) if(grid[l][j] >= grid[i][j]) goto right;
            ++sum;
            goto next;
            right:;
            for(int r = i+1; r < grid.size(); ++r) if(grid[r][j] >= grid[i][j]) goto up;
            ++sum;
            goto next;
            up:;
            for(int u = j-1; u >= 0; --u) if(grid[i][u] >= grid[i][j]) goto down;
            ++sum;
            goto next;
            down:;
            for(int d = j+1; d < grid[0].size(); ++d) if(grid[i][d] >= grid[i][j]) goto next;
            ++sum;
            next:;
        }
    }

    cout << sum << '\n';
    return 0;
}