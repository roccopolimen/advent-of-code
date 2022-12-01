#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define PATTERNS 10
#define DIGITS 4

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<vector<string>> signal_patterns(n, vector<string>(PATTERNS));
    vector<vector<string>> output_values(n, vector<string>(DIGITS));
    unordered_map<int, int> unique_lengths = { {2, 1}, {3, 7}, {4, 4}, {7, 8} };
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < PATTERNS; ++j) {
            cin >> signal_patterns[i][j];
            sort(signal_patterns[i][j].begin(), signal_patterns[i][j].end());
        }
        for(int j = 0; j < DIGITS; ++j) {
            cin >> output_values[i][j];
            sort(output_values[i][j].begin(), output_values[i][j].end());
        }
    }

    auto fill_unique = [&](int index, vector<string> &mapping) {
        for(int i = 0; i < PATTERNS; ++i) {
            int siz = signal_patterns[index][i].size();
            if(unique_lengths.find(siz) != unique_lengths.end())
                mapping[unique_lengths[siz]] = signal_patterns[index][i];
        }
    };

    auto fill3 = [&](int index, vector<string> &mapping) {
        for(int i = 0; i < PATTERNS; ++i)
            if(signal_patterns[index][i].size() == 5) {
                for(char &c : mapping[1])
                    if(signal_patterns[index][i].find(c) == std::string::npos) goto not3;
                mapping[3] = signal_patterns[index][i];
                return;
                not3:;
            }
    };

    auto fill2 = [&](int index, vector<string> &mapping) {
        for(int i = 0; i < PATTERNS; ++i)
            if(signal_patterns[index][i].size() == 5) {
                int alike = 0;
                for(char &c : mapping[4])
                    if(signal_patterns[index][i].find(c) != std::string::npos) ++alike;
                if(alike == 2) {
                    mapping[2] = signal_patterns[index][i];
                    return;
                }
            }
    };

    auto fill5 = [&](int index, vector<string> &mapping) {
        for(int i = 0; i < PATTERNS; ++i)
            if(signal_patterns[index][i].size() == 5) {
                if(signal_patterns[index][i] == mapping[3]) continue;
                if(signal_patterns[index][i] == mapping[2]) continue;
                mapping[5] = signal_patterns[index][i];
                return;
            }
    };

    auto fill6 = [&](int index, vector<string> &mapping) {
        for(int i = 0; i < PATTERNS; ++i)
            if(signal_patterns[index][i].size() == 6)
                for(char &c : mapping[1])
                    if(signal_patterns[index][i].find(c) == std::string::npos) {
                        mapping[6] = signal_patterns[index][i];
                        return;
                    }
    };

    auto fill9 = [&](int index, vector<string> &mapping) {
        for(int i = 0; i < PATTERNS; ++i)
            if(signal_patterns[index][i].size() == 6) {
                for(char &c : mapping[4])
                    if(signal_patterns[index][i].find(c) == std::string::npos) goto not9;
                mapping[9] = signal_patterns[index][i];
                return;
                not9:;
            }
    };

    auto fill0 = [&](int index, vector<string> &mapping) {
        for(int i = 0; i < PATTERNS; ++i)
            if(signal_patterns[index][i].size() == 6) {
                if(mapping[6] == signal_patterns[index][i]) continue;
                if(mapping[9] == signal_patterns[index][i]) continue;
                mapping[0] = signal_patterns[index][i];
                return;
            }
    };

    auto solver = [&](int index) {
        vector<string> mapping(PATTERNS);
        fill_unique(index, mapping);
        fill3(index, mapping);
        fill2(index, mapping);
        fill5(index, mapping);
        fill6(index, mapping);
        fill9(index, mapping);
        fill0(index, mapping);
        int ct = 0;
        for(int i = 0; i < DIGITS; ++i) {
            ct *= 10;
            for(int j = 0; j < PATTERNS; ++j)
                if(output_values[index][i] == mapping[j]) {
                    ct += j; break;
                }
        }
        return ct;
    };

    int sumn = 0;
    for(int i = 0; i < n; ++i) sumn += solver(i);
    cout << sumn << "\n";
    return 0;
}