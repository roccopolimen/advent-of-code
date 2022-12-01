#include <climits>
#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int xl, xr, yl, yr; cin >> xl >> xr >> yl >> yr;
    unordered_set<int> valid_steps;
    int lower_bound_catch_all = INT_MAX;
    for(int i = 1; i <= xr; ++i) {
        int steps = 0, pos = 0, cur_v = i;
        while(pos <= xr && cur_v != 0 && steps < lower_bound_catch_all) {
            pos += cur_v--; steps++;
            if(pos >= xl && pos <= xr) valid_steps.insert(steps);
        }
        if(cur_v == 0 && pos >= xl && pos <= xr)
            lower_bound_catch_all = min(lower_bound_catch_all, steps);
    }
    for(auto &val : valid_steps)
        if(val >= lower_bound_catch_all)
            valid_steps.erase(val);
    while(valid_steps.find(lower_bound_catch_all-1) != valid_steps.end())
        valid_steps.erase(--lower_bound_catch_all);

    auto valid_num_steps = [&](int steps) {
        if(steps >= lower_bound_catch_all) return true;
        if(valid_steps.find(steps) != valid_steps.end()) return true;
        return false;
    };

    int y0 = (yl*-1)+17, height = 0;
    while(true) {
        int steps=y0*2+1, pos=0, cur_v=(y0+1)*-1;
        while(pos >= yl) {
            pos += cur_v--; ++steps;
            if(pos >= yl && pos <= yr && valid_num_steps(steps)) goto find_height;
        }
        --y0;
    }
    find_height:;
    for(int i = 1; i <= y0; ++i) height += i;
    cout << height << "\n";
    return 0;
}