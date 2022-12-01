#include <iostream>

using namespace std;

#define BOARD 10
#define DIE 100
#define ROLLS 3
#define WIN 1000

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int p1, p2; cin >> p1 >> p2;
    int s1=0, s2=0, d=1, tr=0;
    while(true) {
        int roll = 0;
        for(int i = 0; i < ROLLS; ++i) {
            roll += d;
            d = (d == DIE) ? 1 : d+1;
        }
        tr += ROLLS;
        p1 = (p1 + roll) % BOARD;
        if(!p1) p1 = BOARD;
        s1 += p1;
        if(s1 >= WIN) { cout << (s2 * tr) << "\n"; break; }
        roll = 0;
        for(int i = 0; i < ROLLS; ++i) {
            roll += d;
            d = (d == DIE) ? 1 : d+1;
        }
        tr += ROLLS;
        p2 = (p2 + roll) % BOARD;
        if(!p2) p2 = BOARD;
        s2 += p2;
        if(p2 >= WIN) { cout << (s1 * tr) << "\n"; break; }
    }
    return 0;
}