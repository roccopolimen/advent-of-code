#include <bits/stdc++.h>

using namespace std;

void fixup(vector<vector<bool>>& grid, vector<pair<int, int>> &knots) {
    for(int i = 1; i < knots.size(); ++i) {
        if(abs(knots[i-1].first - knots[i].first) <= 1 && abs(knots[i-1].second - knots[i].second) <= 1) return;

        if(knots[i-1].first == knots[i].first) knots[i].second = (knots[i-1].second + knots[i].second)/2;
        else if(knots[i-1].second == knots[i].second) knots[i].first = (knots[i-1].first + knots[i].first)/2;
        else {
            int x = (knots[i-1].first - knots[i].first)/abs(knots[i-1].first - knots[i].first);
            int y = (knots[i-1].second - knots[i].second)/abs(knots[i-1].second - knots[i].second);
            knots[i].first += x; knots[i].second += y;
        }
    }
    grid[knots.back().first][knots.back().second] = true;
}

void up(vector<vector<bool>>& grid, vector<pair<int, int>> &knots) {
    --knots.front().first;
    fixup(grid, knots);
}

void down(vector<vector<bool>>& grid, vector<pair<int, int>> &knots) {
    ++knots.front().first;
    fixup(grid, knots);
}

void left(vector<vector<bool>>& grid, vector<pair<int, int>> &knots) {
    --knots.front().second;
    fixup(grid, knots);
}

void right(vector<vector<bool>>& grid, vector<pair<int, int>> &knots) {
    ++knots.front().second;
    fixup(grid, knots);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<bool>> grid(1000, vector<bool>(1000, false));
    vector<pair<int, int>> knots(10);
    fill(knots.begin(), knots.end(), make_pair(300, 300));
    grid[knots.back().first][knots.back().second] = true;
    for(int i = 0; i < n; ++i) {
        char c; int j;
        cin >> c >> j;
        switch(c) {
            case 'U':
                for(int k = 0; k < j; ++k) up(grid, knots);
                break;
            case 'D':
                for(int k = 0; k < j; ++k) down(grid, knots);
                break;
            case 'L':
                for(int k = 0; k < j; ++k) left(grid, knots);
                break;
            case 'R':
                for(int k = 0; k < j; ++k) right(grid, knots);
                break;
        }
    }

    int sum = 0;
    for(int i = 0; i < 1000; ++i)
        for(int j = 0; j < 1000; ++j)
            sum += grid[i][j];

    cout << sum << '\n';
    return 0;
}