#include <iostream>
#include <vector>

using namespace std;

#define ull unsigned long long
#define SIZE 101
#define OFFSET (SIZE-1)/2

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<vector<vector<bool>>> cube(SIZE, vector<vector<bool>>(SIZE, vector<bool>(SIZE, 0)));
    auto reboot = [&](bool s, int x1, int x2, int y1, int y2, int z1, int z2) {
        for(int *lhs : { &x1, &y1, &z1 }) if(*lhs < -1*OFFSET) return;
        for(int *rhs : { &x2, &y2, &z2 }) if(*rhs > OFFSET) return;
        for(int *coord : { &x1, &x2, &y1, &y2, &z1, &z2}) *coord += OFFSET;
        for(int i = x1; i <= x2; ++i)
            for(int j = y1; j <= y2; ++j)
                for(int k = z1; k <= z2; ++k)
                    cube[i][j][k] = s;
    };

    int n; cin >> n;
    for(int i = 0; i < n; ++i) {
        bool switcher;
        int x1, x2, y1, y2, z1, z2;
        cin >> switcher >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        reboot(switcher, x1, x2, y1, y2, z1, z2);
    }

    ull ct = 0;
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j)
            for(int k = 0; k < SIZE; ++k)
                if(cube[i][j][k]) ++ct;
    cout << ct << "\n";
    return 0;
}