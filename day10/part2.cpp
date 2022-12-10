#include <bits/stdc++.h>

using namespace std;

#define WIDTH 40
#define HEIGHT 6

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

    vector<vector<bool>> grid(HEIGHT, vector<bool>(WIDTH, false));
    for(int i = 0; i < WIDTH*HEIGHT; ++i) {
        int x = i % WIDTH, y = i / WIDTH;
        if(abs(psum[i] - x) <= 1) grid[y][x] = true;
    }
    
    for(int i = 0; i < HEIGHT; ++i) {
        for(int j = 0; j < WIDTH; ++j)
            cout << (grid[i][j] ? '#' : ' ');
        cout << '\n';
    }
    return 0;
}