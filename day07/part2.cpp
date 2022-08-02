#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<int> positions(n);
    for(int i = 0; i < n; ++i) cin >> positions[i];
    int mean = 0;
    for(int i = 0; i < n; ++i) mean += positions[i];
    mean = ceil(1.0*mean/n);

    auto cost = [&](int convergence) {
        vector<int> dist(1e5);
        int max_dist = -1;
        for(int i = 0; i < n; ++i) {
            int tmp_dist = abs(convergence-positions[i]);
            max_dist = max(max_dist, tmp_dist);
            ++dist[tmp_dist];
        }
        int ct = 0, cost_to_move = 0;
        for(int i = 1; i <= max_dist; ++i) {
            cost_to_move += i;
            ct += dist[i]*cost_to_move;
        }
        return ct;
    };
    cout << min(cost(mean-1), cost(mean)) << "\n";
    return 0;
}