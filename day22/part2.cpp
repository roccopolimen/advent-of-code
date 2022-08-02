#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    struct Operation {
        int s, x1, x2, y1, y2, z1, z2;
        Operation(int s, int x1, int x2, int y1, int y2, int z1, int z2) {
            this->s = s;
            this->x1 = x1; this->x2 = x2;
            this->y1 = y1; this->y2 = y2;
            this->z1 = z1; this->z2 = z2;
        }
    };

    vector<Operation> operations; 
    vector<int> xs, ys, zs;
    int n, len; cin >> n; len = n*2;
    xs.resize(len); ys.resize(len); zs.resize(len);
    for(int i = 0, j = 0; i < n; ++i) {
        int s, x1, x2, y1, y2, z1, z2;
        cin >> s >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        xs[j] = x1;   ys[j] = y1;   zs[j++] = z1;
        xs[j] = x2+1; ys[j] = y2+1; zs[j++] = z2+1;
        operations.push_back({ s, x1, x2, y1, y2, z1, z2 });
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    sort(zs.begin(), zs.end());
    
    auto lower_bound = [&](vector<int> &range, int bound) {
        for(int i = 0; i < len; ++i)
            if(range[i] >= bound) return i;
        return -1; // never reached
    };

    vector<vector<vector<bool>>> discrete_block_cube;
    discrete_block_cube.resize(len, vector<vector<bool>>(len, vector<bool>(len, 0)));
    for(auto &operation : operations) {
        int x1 = lower_bound(xs, operation.x1),
            x2 = lower_bound(xs, operation.x2+1),
            y1 = lower_bound(ys, operation.y1),
            y2 = lower_bound(ys, operation.y2+1),
            z1 = lower_bound(zs, operation.z1),
            z2 = lower_bound(zs, operation.z2+1);
        for(int i = x1; i < x2; ++i)
            for(int j = y1; j < y2; ++j)
                for(int k = z1; k < z2; ++k)
                    discrete_block_cube[i][j][k] = operation.s;
    }

    unsigned long long on_ct = 0;
    len--;
    for(int i = 0; i < len; ++i)
        for(int j = 0; j < len; ++j)
            for(int k = 0; k < len; ++k)
                if(discrete_block_cube[i][j][k])
                    on_ct += (unsigned long long)(xs[i+1]-xs[i]) * (ys[j+1]-ys[j]) * (zs[k+1]-zs[k]);
    cout << on_ct << "\n";
    return 0;
}