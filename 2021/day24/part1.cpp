#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    unsigned long long MODEL_NUM = 11111111111111;

    auto make_input = [&](vector<int> &input) {
        unsigned long long tmp = MODEL_NUM;
        while(tmp) { input.push_back(tmp%10); tmp/=10; }
        reverse(input.begin(), input.end());
    };

    auto monad = [&]() {
        stack<int> z;
        vector<int> input; make_input(input);
        auto segment = [&](int in_index, int xc, int yc) {
            if(xc > 0) {
                z.push(input[in_index] + yc);
            } else {
                int popped = z.top(); z.pop();
                if(popped + xc != input[in_index])
                    z.push(input[in_index] + yc);
            }
        };

        segment(0, 12, 4);
        segment(1, 15, 11);
        segment(2, 11, 7);
        segment(3, -14, 2);
        segment(4, 12, 11);
        segment(5, -10, 13);
        segment(6, 11, 9);
        segment(7, 13, 12);
        segment(8, -7, 6);
        segment(9, 10, 2);
        segment(10, -2, 11);
        segment(11, -1, 12);
        segment(12, -4, 3);
        segment(13, -12, 13);
        return z.empty();
    };

    vector<unsigned long long> zero_tracker(13, 0);
    while(!monad()) {
        ++MODEL_NUM;
        for(int i = 0; i < 13; ++i) {
            ++zero_tracker[i];
            if(zero_tracker[i] == 9*(int)pow(9, i)) {
                zero_tracker[i] = 0;
                MODEL_NUM += (int)pow(10, i);
            }
        }
        cout << MODEL_NUM << "\n";
    }
    cout << MODEL_NUM << "\n";
    return 0;
}