#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    using coord_pair = pair<pair<int, int>, pair<int, int>>;

    int n, ROW, MAX_COORD;
    cin >> n >> ROW >> MAX_COORD;
    int min_coord = INT_MAX, max_coord = INT_MIN;
    for(int i = 0; i < n; ++i) {
        int x, y, bx, by;
        cin >> x >> y >> bx >> by;
        int b_dist = abs(x-bx) + abs(y-by);
        int y_dist = abs(y-ROW);
        if(y_dist < b_dist) {
            min_coord = min(min_coord, x-b_dist+y_dist);
            max_coord = max(max_coord, x+b_dist-y_dist);
        }
    }
    cout << (max_coord - min_coord) << '\n';
    return 0;
}