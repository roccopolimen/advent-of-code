#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    int rows = 0, cols = 0;
    vector<pair<char, int>> instructions(m);
    vector<vector<bool>> paper;
    vector<pair<int, int>> dots(n);
    int maxR = -1, maxC = -1;
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        maxR = max(maxR, y); maxC = max(maxC, x);
        dots[i] = make_pair(y, x);
    }
    for(int i = 0; i < m; ++i) {
        char label;
        int fold_coord;
        cin >> label >> fold_coord;
        instructions[i] = make_pair(label, fold_coord);
        if(!rows && label=='y') rows = fold_coord*2+1;
        if(!cols && label == 'x') cols = fold_coord*2+1;
    }
    paper.resize(rows, vector<bool>(cols));
    for(pair<int, int> &coord : dots) paper[coord.first][coord.second] = true;

    auto horizontal_fold = [&](int index) {
        int line = instructions[index].second;
        int nc = paper[0].size();
        for(int i = line-1; i >= 0; --i)
            for(int j = 0; j < nc; ++j)
                paper[i][j] = paper[i][j] || paper[line+(line-i)][j];
        paper.resize(line);
    };

    auto vertical_fold = [&](int index) {
        int line = instructions[index].second;
        int nr = paper.size();
        for(int i = 0; i < nr; ++i) {
            for(int j = line-1; j >= 0; --j)
                paper[i][j] = paper[i][j] || paper[i][line+(line-j)];
            paper[i].resize(line);
        } 
    };

    for(int i = 0; i < m; ++i) {
        if(instructions[i].first == 'y') horizontal_fold(i);
        else vertical_fold(i);
    }
    int nr = paper.size(), nc = paper[0].size();
    for(int i = 0; i < nr; ++i) {
        for(int j = 0; j < nc; ++j) cout << (paper[i][j] ? "■" : " ");
        cout << "\n";
    }
    return 0;
}