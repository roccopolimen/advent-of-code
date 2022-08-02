#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        string tmp; cin >> tmp;
        for(int j = 0; j < n; ++j) matrix[i][j] = tmp[j] - '0';
    }

    vector<vector<int>> F(n, vector<int>(n, INT_MAX));
    priority_queue<pair<int, pair<int, int>>, // data type
                   vector<pair<int, pair<int, int>>>, // how to store data
                   greater<pair<int, pair<int, int>>>> dist_heap; // how to order data
    F[0][0] = 0;
    dist_heap.push(make_pair(0, make_pair(0, 0)));
    while(!dist_heap.empty()) {
        pair<int, int> coords = dist_heap.top().second; dist_heap.pop();
        int r = coords.first, c = coords.second;
        if(r && F[r-1][c] > (F[r][c] + matrix[r-1][c])) {
            F[r-1][c] = F[r][c] + matrix[r-1][c];
            dist_heap.push(make_pair(F[r-1][c], make_pair(r-1, c)));
        }
        if(c && F[r][c-1] > (F[r][c] + matrix[r][c-1])) {
            F[r][c-1] = F[r][c] + matrix[r][c-1];
            dist_heap.push(make_pair(F[r][c-1], make_pair(r, c-1)));
        }
        if((c != n-1) && F[r][c+1] > (F[r][c] + matrix[r][c+1])) {
            F[r][c+1] = F[r][c] + matrix[r][c+1];
            dist_heap.push(make_pair(F[r][c+1], make_pair(r, c+1)));
        }
        if((r != n-1) && F[r+1][c] > (F[r][c] + matrix[r+1][c])) {
            F[r+1][c] = F[r][c] + matrix[r+1][c];
            dist_heap.push(make_pair(F[r+1][c], make_pair(r+1, c)));
        }
    }
    cout << F[n-1][n-1] << "\n";
    return 0;
}