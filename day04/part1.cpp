#include <iostream>
#include <vector>

using namespace std;

#define MARKED -1

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<int> entries;
    vector<vector<vector<int>>> boards;
    int ne, nb; cin >> ne >> nb;
    entries.resize(ne);
    for(int i = 0; i < ne; ++i) cin >> entries[i];

    boards.resize(nb, vector<vector<int>>(5, vector<int>(5, 0)));
    for(int i = 0; i < nb; ++i)
        for(int j = 0; j < 5; ++j)
            for(int k = 0; k < 5; ++k)
                cin >> boards[i][j][k];

    auto mark_boards = [&](int selected) {
        for(int i = 0; i < nb; ++i)
            for(int j = 0; j < 5; ++j)
                for(int k = 0; k < 5; ++k)
                    if(boards[i][j][k] == selected)
                        boards[i][j][k] = MARKED;
    };

    auto check = [&](bool horizontal=true) {
        for(int i = 0; i < nb; ++i)
            for(int j = 0; j < 5; ++j) {
                for(int k = 0; k < 5; ++k) {
                    if(horizontal) {
                           if(boards[i][j][k] != MARKED) goto invalid;
                    } else if(boards[i][k][j] != MARKED) goto invalid;
                }
                return i;
                invalid:;
            }
        return -1;
    };

    auto sum_unmarked = [&](int bi) {
        int sum = 0;
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                if(boards[bi][i][j] != MARKED)
                    sum += boards[bi][i][j];
        return sum;
    };

    auto bingo = [&]() {
        for(auto &selected: entries) {
            mark_boards(selected);
            int winning_board;
            if((winning_board = check(true)) != -1)
                return selected * sum_unmarked(winning_board);
            else if((winning_board = check(false)) != -1)
                return selected * sum_unmarked(winning_board);
        }
        return -1;
    };
    cout << bingo() << "\n";
    return 0;
}