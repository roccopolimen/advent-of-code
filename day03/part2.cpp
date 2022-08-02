#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<string> diagnostics(n);
    for(int i = 0; i < n; ++i) {
        string temp; cin >> temp;
        diagnostics[i] = temp;
    }

    auto get_rating = [&](vector<string> diagnostics, bool keep_freq) {
        int n = diagnostics.size(), cols = diagnostics[0].size();
        for(int i = 0; i < cols && n != 1; ++i) {
            int ct = 0;
            for(int j = 0; j < n; ++j) ct += (diagnostics[j][i]-'0');

            char digit;
            if((ct << 1) >= n) digit = (char)('0' + keep_freq);
            else digit = (char)('0' + !keep_freq);
            vector<string> temp;
            copy_if(diagnostics.begin(), diagnostics.end(), std::back_inserter(temp), [&i, &digit](string s){return s[i]==digit;} );
            diagnostics.clear();
            copy(temp.begin(), temp.end(), back_inserter(diagnostics));
            n = diagnostics.size();
        }
        return stoi(diagnostics[0], 0, 2);
    };
    
    cout << get_rating(diagnostics, true) * get_rating(diagnostics, false) << "\n";
    return 0;
}