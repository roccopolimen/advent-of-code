#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> mat(n);
    vector<pair<int, int>> low_points;
    for(int i = 0; i < n; ++i) {
        string tmp; cin >> tmp;
        mat[i].resize(tmp.size());
        for(int j = 0, len = tmp.size(); j < len; ++j) mat[i][j] = tmp[j]-'0';
    }

    auto find_low_points = [&]() {
        for(int i = 0; i < n; ++i)
            for(int j = 0, len=mat[i].size(); j < len; ++j) {
                if(j && mat[i][j] >= mat[i][j-1]) continue;
                if(j != (len-1) && mat[i][j] >= mat[i][j+1]) continue;
                if(i && mat[i][j] >= mat[i-1][j]) continue;
                if(i != (n-1) && mat[i][j] >= mat[i+1][j]) continue;
                low_points.push_back(make_pair(i, j));
            }
    };

    auto solver = [&]() {
        find_low_points();
        vector<int> basin_sizes(low_points.size());
        int collen = mat[0].size();
        for(pair<int, int> &low : low_points) {
            vector<vector<bool>> visited(n, vector<bool>(collen, false));
            int siz = 0;
            queue<pair<int, int>> loc; loc.push(low);
            while(!loc.empty()) {
                pair<int, int> coords = loc.front(); loc.pop();
                if(visited[coords.first][coords.second] || mat[coords.first][coords.second] == 9) continue;
                ++siz;
                visited[coords.first][coords.second] = true;
                if(coords.first) loc.push(make_pair(coords.first-1, coords.second));
                if(coords.first != n-1) loc.push(make_pair(coords.first+1, coords.second));
                if(coords.second) loc.push(make_pair(coords.first, coords.second-1));
                if(coords.second != collen-1) loc.push(make_pair(coords.first, coords.second+1));
            }
            basin_sizes.push_back(siz);
        }
        sort(basin_sizes.begin(), basin_sizes.end(), greater<int>());
        return basin_sizes[0]*basin_sizes[1]*basin_sizes[2];
    };
    cout << solver() << "\n";
    return 0;
}