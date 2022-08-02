#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>

using namespace std;

#define SIZE 10

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int matrix[SIZE][SIZE];
    for(int i = 0; i < SIZE; ++i) {
        string tmp; cin >> tmp;
        for(int j = 0; j < SIZE; ++j) matrix[i][j] = tmp[j] - '0';
    }

    auto increment_neighbors = [&](queue<pair<int, int>> &flashers, int r, int c) {
        if(r && c) {
            ++matrix[r-1][c-1];
            if(matrix[r-1][c-1] == 10) flashers.push(make_pair(r-1, c-1));
        }
        if(r) {
            ++matrix[r-1][c];
            if(matrix[r-1][c] == 10) flashers.push(make_pair(r-1, c));
        }
        if(r && c != SIZE-1) {
            ++matrix[r-1][c+1];
            if(matrix[r-1][c+1] == 10) flashers.push(make_pair(r-1, c+1));
        }
        if(c) {
            ++matrix[r][c-1];
            if(matrix[r][c-1] == 10) flashers.push(make_pair(r, c-1));
        }
        if(c != SIZE-1) {
            ++matrix[r][c+1];
            if(matrix[r][c+1] == 10) flashers.push(make_pair(r, c+1));
        }
        if(r != SIZE-1 && c) {
            ++matrix[r+1][c-1];
            if(matrix[r+1][c-1] == 10) flashers.push(make_pair(r+1, c-1));
        }
        if(r != SIZE-1) {
            ++matrix[r+1][c];
            if(matrix[r+1][c] == 10) flashers.push(make_pair(r+1, c));
        }
        if(r != SIZE-1 && c != SIZE-1) {
            ++matrix[r+1][c+1];
            if(matrix[r+1][c+1] == 10) flashers.push(make_pair(r+1, c+1));
        }
    };

    auto step = [&]() {
        int ct = 0;
        queue<pair<int, int>> flashers;
        stack<pair<int, int>> reset;
        for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
                ++matrix[i][j];
                if(matrix[i][j] == 10) flashers.push(make_pair(i, j));
            }
        }
        while(!flashers.empty()) {
            int r = flashers.front().first, c = flashers.front().second;
            increment_neighbors(flashers, r, c);
            reset.push(flashers.front()); flashers.pop();
        }
        while(!reset.empty()) {
            ++ct;
            matrix[reset.top().first][reset.top().second] = 0;
            reset.pop();
        }
        return ct;
    };

    int ct = 1;
    while(SIZE*SIZE != step()) ++ct;
    cout << ct << "\n";
    return 0;
}