#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#define PATTERNS 10
#define DIGITS 4

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    unordered_set<int> unique_lengths = { 2, 4, 3, 7 };
    vector<vector<string>> output_values(n, vector<string>(DIGITS));
    for(int i = 0; i < n; ++i) {
        string tmp;
        for(int j = 0; j < PATTERNS; ++j)
            cin >> tmp;
        for(int j = 0; j < DIGITS; ++j)
            cin >> output_values[i][j];
    }

    int ct = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < DIGITS; ++j)
            if(unique_lengths.find(output_values[i][j].size()) != unique_lengths.end())
                ++ct;
    cout << ct << "\n";
    return 0;
}