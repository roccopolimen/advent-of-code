#include <iostream>
#include <unordered_map>

using namespace std;

#define BOARD 10
#define WIN 21
#define ull unsigned long long

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    struct State {
        int p1, p2, s1, s2;
        State(int p1, int p2, int s1, int s2) {
            this->p1 = p1;
            this->p2 = p2;
            this->s1 = s1;
            this->s2 = s2;
        }
        bool operator==(const State &s) const {
            return p1 == s.p1 && p2 == s.p2 && s1 == s.s1 && s2 == s.s2;
        }
    };

    struct hash_fn {
        size_t operator() (const State &state) const {
            size_t h1 = hash<int>()(state.p1);
            size_t h2 = hash<int>()(state.p2);
            size_t h3 = hash<int>()(state.s1);
            size_t h4 = hash<int>()(state.s2);
            return ((h1 ^ h2) ^ h3) ^ h4;
        }
    };

    ull p1_wins=0, p2_wins=0;
    int freq[10] = { 0, 0, 0, 1, 3, 6, 7, 6, 3, 1 };
    unordered_map<State, ull, hash_fn> states;
    int p1, p2; cin >> p1 >> p2;
    states[{--p1, --p2, 0, 0}] = 1;
    bool turn = true;
    while(states.size()) {
        unordered_map<State, ull, hash_fn> tmp;
        for(auto &state : states) {
            for(int k = 3; k < BOARD; ++k) {
                if(turn) {
                    int new_position = (state.first.p1+k)%BOARD;
                    int new_score = state.first.s1 + new_position + 1;
                    if(new_score >= WIN) p1_wins += (state.second*freq[k]);
                    else {
                        State next = { new_position, state.first.p2, new_score, state.first.s2 };
                        tmp[next] += (state.second*freq[k]);
                    }
                } else {
                    int new_position = (state.first.p2+k)%BOARD;
                    int new_score = state.first.s2 + new_position + 1;
                    if(new_score >= WIN) p2_wins += (state.second*freq[k]);
                    else {
                        State next = { state.first.p1, new_position, state.first.s1, new_score };
                        tmp[next] += (state.second*freq[k]);
                    }
                }
            }
        }
        states = tmp; turn = !turn;
    }
    if(p1_wins > p2_wins) cout << p1_wins << "\n";
    else cout << p2_wins << "\n";
    return 0;
}