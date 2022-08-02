#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<string> chunks(n);
    unordered_set<char> closings = {')', '}', ']', '>'};
    unordered_map<char, int> penalties = { {')', 3},   {']', 57},  {'}', 1197}, {'>', 25137} };
    unordered_map<char, char> paired =   { {')', '('}, {']', '['}, {'}', '{'},  {'>', '<'} };
    for(int i = 0; i < n; ++i) cin >> chunks[i];

    auto solver = [&]() {
        unsigned long long ct = 0;
        for(int i = 0; i < n; ++i) {
            stack<char> openings;
            for(char &c : chunks[i]) {
                if(closings.find(c) != closings.end()) {
                    if(openings.top() == paired[c]) openings.pop();
                    else { ct += penalties[c]; break; }
                } else openings.push(c);
            }
        }
        return ct;
    };
    cout << solver() << "\n";
    return 0;
}