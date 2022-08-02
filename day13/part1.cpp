#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    pair<char, int> instruction;
    vector<vector<bool>> paper;
    vector<pair<int, int>> dots(n);
    int maxR = -1, maxC = -1;
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        maxR = max(maxR, y); maxC = max(maxC, x);
        dots[i] = make_pair(y, x);
    }
    char label; int fold_coord; cin >> label >> fold_coord;
    instruction = make_pair(label, fold_coord);
    for(int i = 1; i < m; ++i) cin >> label >> fold_coord;
    paper.resize(maxR+1, vector<bool>(maxC+1));
    for(pair<int, int> &coord : dots) paper[coord.first][coord.second] = true;

    auto horizontal_fold = [&]() {
        int line = instruction.second;
        int nc = paper[0].size();
        for(int i = line-1; i >= 0; --i)
            for(int j = 0; j < nc; ++j)
                paper[i][j] = paper[i][j] || paper[line+(line-i)][j];
        paper.resize(line);
    };

    auto vertical_fold = [&]() {
        int line = instruction.second;
        int nr = paper.size();
        for(int i = 0; i < nr; ++i) {
            for(int j = line-1; j >= 0; --j)
                paper[i][j] = paper[i][j] || paper[i][line+(line-j)];
            paper[i].resize(line);
        } 
    };

    if(instruction.first == 'y') horizontal_fold();
    else vertical_fold();
    int nr = paper.size(), nc = paper[0].size(), ct = 0;
    for(int i = 0; i < nr; ++i)
        for(int j = 0; j < nc; ++j)
            ct += paper[i][j];
    cout << ct << "\n";
    return 0;
}