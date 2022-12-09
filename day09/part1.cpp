#include <bits/stdc++.h>

using namespace std;

void fixup(vector<vector<bool>>& grid, pair<int, int>& head, pair<int, int>& tail) {
    if(abs(head.first - tail.first) <= 1 && abs(head.second - tail.second) <= 1) return;

    if(head.first == tail.first) tail.second = (head.second + tail.second)/2;
    else if(head.second == tail.second) tail.first = (head.first + tail.first)/2;
    else {
        int x = (head.first - tail.first)/abs(head.first - tail.first);
        int y = (head.second - tail.second)/abs(head.second - tail.second);
        tail.first += x; tail.second += y;
    }
    grid[tail.first][tail.second] = true;
}

void up(vector<vector<bool>>& grid, pair<int, int>& head, pair<int, int>& tail) {
    --head.first;
    fixup(grid, head, tail);
}

void down(vector<vector<bool>>& grid, pair<int, int>& head, pair<int, int>& tail) {
    ++head.first;
    fixup(grid, head, tail);
}

void left(vector<vector<bool>>& grid, pair<int, int>& head, pair<int, int>& tail) {
    --head.second;
    fixup(grid, head, tail);
}

void right(vector<vector<bool>>& grid, pair<int, int>& head, pair<int, int>& tail) {
    ++head.second;
    fixup(grid, head, tail);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<bool>> grid(1000, vector<bool>(1000, false));
    pair<int, int> head = { 300, 300 }, tail = { 300, 300 };
    grid[tail.first][tail.second] = true;
    for(int i = 0; i < n; ++i) {
        char c; int j;
        cin >> c >> j;
        switch(c) {
            case 'U':
                for(int k = 0; k < j; ++k) up(grid, head, tail);
                break;
            case 'D':
                for(int k = 0; k < j; ++k) down(grid, head, tail);
                break;
            case 'L':
                for(int k = 0; k < j; ++k) left(grid, head, tail);
                break;
            case 'R':
                for(int k = 0; k < j; ++k) right(grid, head, tail);
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