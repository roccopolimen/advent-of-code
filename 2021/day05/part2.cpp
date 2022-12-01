#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<pair<int, pair<int, int>>> hor_pairs;
    vector<pair<int, pair<int, int>>> ver_pairs;
    vector<pair<pair<int, int>, pair<int, int>>> diag_pairs;
    int n; cin >> n;
    int max_hor = 0, max_ver = 0;
    for(int i = 0; i < n; ++i) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if(x1 == x2) {
            max_hor = max(max_hor, x1);
            max_ver = max(max_ver, max(y1, y2));
            hor_pairs.push_back(make_pair(x1, make_pair(y1, y2)));
        } else if(y1 == y2) {
            max_ver = max(max_ver, y1);
            max_hor = max(max_hor, max(x1, x2));
            ver_pairs.push_back(make_pair(y1, make_pair(x1, x2)));
        } else if(abs(y2-y1) == abs(x2-x1)) { // 45-deg lines
            max_hor = max(max_hor, max(x1, x2));
            max_ver = max(max_ver, max(y1, y2));
            diag_pairs.push_back(make_pair(make_pair(x1, x2), make_pair(y1, y2)));
        }
    }

    vector<vector<int>> matrix(max_ver+1, vector<int>(max_hor+1, 0));
    for(int i = 0, len = hor_pairs.size(); i < len; ++i) {
        int x = hor_pairs[i].first;
        int y_start = min(hor_pairs[i].second.first, hor_pairs[i].second.second);
        int y_finish = max(hor_pairs[i].second.first, hor_pairs[i].second.second);
        for(int j = y_start; j <= y_finish; ++j) ++matrix[j][x];
    }
    for(int i = 0, len = ver_pairs.size(); i < len; ++i) {
        int y = ver_pairs[i].first;
        int x_start = min(ver_pairs[i].second.first, ver_pairs[i].second.second);
        int x_finish = max(ver_pairs[i].second.first, ver_pairs[i].second.second);
        for(int j = x_start; j <= x_finish; ++j) ++matrix[y][j];
    }
    for(int i = 0, len = diag_pairs.size(); i < len; ++i) {
        int x1 = diag_pairs[i].first.first,
            x2 = diag_pairs[i].first.second,
            y1 = diag_pairs[i].second.first,
            y2 = diag_pairs[i].second.second;
        int x = x1, y = y1;
        while(x != x2 && y != y2) {
            ++matrix[y][x];
            if(x < x2) ++x; else --x;
            if(y < y2) ++y; else --y;
        }
        ++matrix[y][x];
    }

    int ct = 0;
    for(int i = 0; i <= max_hor; ++i)
        for(int j = 0; j <= max_ver; ++j)
            if(matrix[i][j] > 1)
                ++ct;
    cout << ct << "\n";
    return 0;
}