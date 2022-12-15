#include <bits/stdc++.h>

using namespace std;

#define TUNING_RATE 4000000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    using coord_pair = pair<pair<int, int>, pair<int, int>>;

    int n, ROW, MAX_COORD;
    cin >> n >> ROW >> MAX_COORD;
    vector<coord_pair> sensors(n);
    for(int i = 0; i < n; ++i) {
        int x, y, bx, by;
        cin >> x >> y >> bx >> by;
        sensors[i] = {{x, y}, {bx, by}};
    }

    for(auto &s1 : sensors) {
        for(auto &s2 : sensors) {
            int r1 = abs(s1.first.first - s1.second.first) + abs(s1.first.second - s1.second.second)+1;
            pair<int, int> p1 = {s1.first.first + s1.first.second + r1, s1.first.first + s1.first.second - r1};
            int r2 = abs(s2.first.first - s2.second.first) + abs(s2.first.second - s2.second.second)+1;
            pair<int, int> p2 = {s2.first.first - s2.first.second + r2, s2.first.first - s2.first.second - r2};
            int x = (p1.first + p2.second) / 2;
            int y = p1.first - x;
            if(x >= 0 && x <= MAX_COORD && y >= 0 && y <= MAX_COORD) {
                bool ok = true;
                for(auto &s : sensors) {
                    int r = abs(s.first.first - s.second.first) + abs(s.first.second - s.second.second);
                    if(abs(s.first.first - x) + abs(s.first.second - y) <= r) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    long long ans = (long long)x * TUNING_RATE + y;
                    cout << ans << '\n';
                    return 0;
                }
            }
        }
    }
    return 0;
}