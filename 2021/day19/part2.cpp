#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

#define ROTATIONS 24
#define OVERLAPS 12

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    int max_manhattan = -1;
    unordered_set<int> found_indices;
    vector<vector<vector<int>>> records(n);
    vector<vector<int>> coords(n);
    vector<vector<int>> rotations = {
        {1,2,3}, {2,-1,3}, {-1,-2,3},
        {-2,1,3}, {1,-2,-3}, {2,1,-3},
        {-1,2,-3}, {-2,-1,-3}, {3,2,-1},
        {2,-3,-1}, {-3,-2,-1}, {-2,3,-1},
        {-3,2,1}, {2,3,1}, {3,-2,1},
        {-2,-3,1}, {1,-3,2}, {-3,-1,2},
        {-1,3,2}, {3,1,2}, {1,3,-2},
        {3,-1,-2}, {-1,-3,-2}, {-3,1,-2}
    };
    for(int i = 0; i < n; ++i) {
        int scans; cin >> scans;
        records[i].resize(scans);
        coords[i].resize(3);
        for(int j = 0; j < scans; ++j) {
            records[i][j].resize(3);
            cin >> records[i][j][0] >> records[i][j][1] >> records[i][j][2];
        }
    }
    coords[0][0] = 0; coords[0][1] = 0; coords[0][2] = 0;

    auto compare = [&](int s1, int s2) {
        for(int i = 0, len1 = records[s1].size(); i < len1; ++i) {
            int x1 = records[s1][i][0], y1 = records[s1][i][1], z1 = records[s1][i][2];
            for(int j = 0, len2 = records[s2].size(); j < len2; ++j) {
                for(int r = 0; r < ROTATIONS; ++r) {
                    int x2 = records[s2][j][abs(rotations[r][0])-1],
                        y2 = records[s2][j][abs(rotations[r][1])-1],
                        z2 = records[s2][j][abs(rotations[r][2])-1];
                    if(rotations[r][0] < 0) x2 *= -1;
                    if(rotations[r][1] < 0) y2 *= -1;
                    if(rotations[r][2] < 0) z2 *= -1;
                    int dx = x1-x2, dy = y1-y2, dz = z1-z2;
                    int ct_alike = 1;
                    for(int k = 0; k < len2; ++k) {
                        if(j == k) continue;
                        int x3 = records[s2][k][abs(rotations[r][0])-1],
                            y3 = records[s2][k][abs(rotations[r][1])-1],
                            z3 = records[s2][k][abs(rotations[r][2])-1];
                        if(rotations[r][0] < 0) x3 *= -1;
                        if(rotations[r][1] < 0) y3 *= -1;
                        if(rotations[r][2] < 0) z3 *= -1;
                        x3 += dx; y3 += dy; z3 += dz;
                        for(int m = 0; m < len1; ++m)
                            if(x3 == records[s1][m][0]
                            && y3 == records[s1][m][1]
                            && z3 == records[s1][m][2]) ++ct_alike;
                    }
                    if(ct_alike < OVERLAPS) continue;
                    coords[s2][0] = dx; coords[s2][1] = dy; coords[s2][2] = dz;
                    for(int k = 0; k < len2; ++k) {
                        int x3 = records[s2][k][abs(rotations[r][0])-1],
                            y3 = records[s2][k][abs(rotations[r][1])-1],
                            z3 = records[s2][k][abs(rotations[r][2])-1];
                        if(rotations[r][0] < 0) x3 *= -1;
                        if(rotations[r][1] < 0) y3 *= -1;
                        if(rotations[r][2] < 0) z3 *= -1;
                        x3 += dx; y3 += dy; z3 += dz;
                        records[s2][k][0] = x3; records[s2][k][1] = y3; records[s2][k][2] = z3;
                    }
                    return true;
                }
            }
        }
        return false;
    };

    for(int i = 1; i < n; ++i) if(compare(0, i)) found_indices.insert(i);
    found_indices.insert(0);
    while(found_indices.size() < n)
        for(int i = 1; i < n; ++i)
            if(found_indices.find(i) == found_indices.end())
                for(auto &j : found_indices)
                    if(compare(j, i))
                        found_indices.insert(i);

    for(int i = 0; i < n; ++i)
        for(int j = i+1; j < n; ++j) {
            int dx = abs(coords[i][0] - coords[j][0]),
                dy = abs(coords[i][1] - coords[j][1]),
                dz = abs(coords[i][2] - coords[j][2]);
            max_manhattan = max(max_manhattan, (dx+dy+dz));
        }
    cout << max_manhattan << "\n";
    return 0;
}