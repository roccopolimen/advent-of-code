#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

#define STEPS 10
#define ull unsigned long long

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    string tmp; cin >> tmp;
    char last_char = tmp[tmp.size()-1];
    unordered_map<string, ull> polymer;
    unordered_map<string, char> rules;
    for(int i = 0, len = tmp.size()-1; i < len; ++i) ++polymer[tmp.substr(i, 2)];
    for(int i = 0; i < n; ++i) {
        string tmpS; char tmpC; cin >> tmpS >> tmpC;
        rules[tmpS] = tmpC;
    }

    auto step = [&]() {
        unordered_map<string, ull> next_polymer;
        for(auto it : polymer)
            if(rules.find(it.first) != rules.end()) {
                ostringstream left, right;
                left << it.first[0] << rules[it.first];
                right << rules[it.first] << it.first[1];
                next_polymer[left.str()] += it.second;
                next_polymer[right.str()] += it.second;
            }
        polymer = next_polymer;
    };

    for(int i = 0; i < STEPS; ++i) step();
    unordered_map<char, ull> freq;
    for(auto it : polymer) freq[it.first[0]] += it.second;
    ++freq[last_char];
    ull highest = 0, lowest = LONG_MAX;
    for(auto it : freq) {
        if(highest < it.second) highest = it.second;
        if(lowest > it.second) lowest = it.second;
    }
    cout << (highest - lowest) << "\n";
    return 0;
}