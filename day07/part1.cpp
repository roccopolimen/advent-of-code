#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<int> positions(n);
    for(int i = 0; i < n; ++i) cin >> positions[i];
    sort(positions.begin(), positions.end());
    int median = positions[n>>1];
    int ct = 0;
    for(int i = 0; i < n; ++i) ct += abs(median-positions[i]);
    cout << ct << "\n";
    return 0;
}