#include <iostream>
#include <vector>

using namespace std;

#define RIGHT '>'
#define DOWN 'v'
#define EMPTY '.'

int main() {
    int n; cin >> n;
    vector<vector<char>> map(n);
    for(int i = 0; i < n; ++i) {
        string tmp; cin >> tmp;
        map[i].assign(tmp.begin(), tmp.end());
    }
    int m = map[0].size();

    auto move_right = [&]() {
        vector<vector<bool>> can_move(n, vector<bool>(m, false));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(map[i][j] == RIGHT && map[i][(j+1)%m] == EMPTY)
                    can_move[i][j] = true;
        bool moved = false;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(can_move[i][j]) {
                    moved = true;
                    map[i][j] = EMPTY;
                    map[i][(j+1)%m] = RIGHT;
                }
        return moved;
    };

    auto move_down = [&]() {
        vector<vector<bool>> can_move(n, vector<bool>(m, false));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(map[i][j] == DOWN && map[(i+1)%n][j] == EMPTY)
                    can_move[i][j] = true;
        bool moved = false;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(can_move[i][j]) {
                    moved = true;
                    map[i][j] = EMPTY;
                    map[(i+1)%n][j] = DOWN;
                }
        return moved;
    };

    auto move = [&]() {
        bool moved = move_right();
        moved = move_down() || moved;
        return moved;
    };

    int ct = 1;
    while(move()) ++ct;
    cout << ct << "\n";
    return 0;
}