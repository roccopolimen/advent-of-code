#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ull unsigned long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<string> chunks(n);
    unordered_set<char> closings = {')', '}', ']', '>'};
    unordered_map<char, int> scores = { {')', 1}, {']', 2}, {'}', 3}, {'>', 4} };
    unordered_map<char, char> cToO = { {')', '('}, {']', '['}, {'}', '{'}, {'>', '<'} };
    unordered_map<char, char> oToC = { {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'} };
    for(int i = 0; i < n; ++i) cin >> chunks[i];

    auto solver = [&]() {
        ull ct = 0;
        vector<ull> completions;
        for(int i = 0; i < n; ++i) {
            stack<char> openings;
            ull score = 0;
            for(char &c : chunks[i]) {
                if(closings.find(c) != closings.end()) {
                    if(openings.top() == cToO[c]) openings.pop();
                    else goto badChunk;
                } else openings.push(c);
            }
            while(!openings.empty()) {
                score *= 5;
                score += scores[oToC[openings.top()]];
                openings.pop();
            }
            completions.push_back(score);
            badChunk:;
        }
        sort(completions.begin(), completions.end());
        return completions[(completions.size() >> 1)];
    };
    cout << solver() << "\n";
    return 0;
}