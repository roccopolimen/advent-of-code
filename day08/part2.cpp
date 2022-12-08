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

    long long max_score = 0;
    for(int i = 1; i < grid.size()-1; ++i) {
        for(int j = 1; j < grid[0].size()-1; ++j) {
            long long score = 1;
            int l, r, u, d;
            for(l = i-1; l > 0; --l) if(grid[l][j] >= grid[i][j]) break; 
            score *= i-l;
            for(r = i+1; r < grid.size()-1; ++r) if(grid[r][j] >= grid[i][j]) break; 
            score *= r-i;
            for(u = j-1; u > 0; --u) if(grid[i][u] >= grid[i][j]) break; 
            score *= j-u;
            for(d = j+1; d < grid[0].size()-1; ++d) if(grid[i][d] >= grid[i][j]) break; 
            score *= d-j;
            max_score = max(max_score, score);
        }
    }

    cout << max_score << '\n';
    return 0;
}