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
    unordered_set<int> found_indices;
    vector<vector<vector<int>>> records(n);
    vector<vector<int>> beacons;
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
        for(int j = 0; j < scans; ++j) {
            records[i][j].resize(3);
            cin >> records[i][j][0] >> records[i][j][1] >> records[i][j][2];
        }
    }

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
                    for(int k = 0; k < len2; ++k) {
                        int x3 = records[s2][k][abs(rotations[r][0])-1],
                            y3 = records[s2][k][abs(rotations[r][1])-1],
                            z3 = records[s2][k][abs(rotations[r][2])-1];
                        if(rotations[r][0] < 0) x3 *= -1;
                        if(rotations[r][1] < 0) y3 *= -1;
                        if(rotations[r][2] < 0) z3 *= -1;
                        x3 += dx; y3 += dy; z3 += dz;
                        records[s2][k][0] = x3;
                        records[s2][k][1] = y3;
                        records[s2][k][2] = z3;
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
        for(int j = 0, len = records[i].size(); j < len; ++j) {
            int x = records[i][j][0], y = records[i][j][1], z = records[i][j][2];
            for(int k = 0, blen = beacons.size(); k < blen; ++k)
                if(x == beacons[k][0] && y == beacons[k][1] && z == beacons[k][2])
                    goto no_insert;
            beacons.push_back({x, y, z});
            no_insert:;
        }
    cout << beacons.size() << "\n";
    return 0;
}