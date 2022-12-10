#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, X = 1, idx = 0;
    cin >> n;

    int psum[250] = {0};
    psum[0] = 1;
    for(int i = 0; i < n; ++i) {
        string inst; int V;
        cin >> inst;
        if(inst == "noop") {
            ++idx;
        } else if(inst == "addx") {
            cin >> V;
            idx += 2;
            psum[idx] = V;
        }
    }

    // perform prefix summing
    for(int i = 1; i < 250; ++i)
        psum[i] += psum[i - 1];

    int ans = 0;
    for(int i = 20; i <= 220; i += 40) // cout << psum[i-1] << ' ';
        ans += psum[i-1] * i;
    cout << ans << '\n';
    return 0;
}