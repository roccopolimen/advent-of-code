#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// x0's [{first i | i(i+1)/2 >= xl} .. xr]
// y0's [yl .. (yl+1)*-1]
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    typedef pair<int, int> pairint;
    struct pair_hash {
        size_t operator() (const pair<int, int> &pair) const {
            return hash<int>()(pair.first) ^ hash<int>()(pair.second);
        }
    };

    int xl, xr, yl, yr; cin >> xl >> xr >> yl >> yr;
    vector<int>count_steps(1e9);
    unordered_map<pairint, int, pair_hash> dups;
    for(int y0=yl, upper=(yl+1)*-1; y0 <= upper; ++y0) {
        bool flag = false;
        int steps=0, pos=0, cur_yv=y0;
        while(pos >= yl) {
            pos += cur_yv--; ++steps;
            if(pos >= yl && pos <= yr) {
                ++count_steps[steps];
                if(flag) ++dups[make_pair(steps, steps-1)];
                flag = true;
            }
        }
    }
    for(int i = 1e9-1; i >= 0; --i)
        if(count_steps[i]) { count_steps.resize(i+1); break; }

    int total = 0, len = count_steps.size();
    for(int x0 = 1; x0 <= xr; ++x0) {
        int steps=0, pos=0, cur_xv=x0;
        bool flag = false;
        while(pos <= xr && cur_xv != 0 && steps < len) {
            pos += cur_xv--; ++steps;
            if(pos >= xl && pos <= xr) {
                total += count_steps[steps];
                if(flag && dups.find(make_pair(steps, steps-1)) != dups.end())
                    total -= dups[make_pair(steps, steps-1)];
                flag = true;
            }
        }
        if(cur_xv == 0 && pos >= xl && pos <= xr)
            for(int i=steps+1; i < len; ++i) {
                total += count_steps[i];
                if(dups.find(make_pair(i, i-1)) != dups.end())
                    total -= dups[make_pair(i, i-1)];
            }
    }
    cout << total << "\n";
    return 0;
}