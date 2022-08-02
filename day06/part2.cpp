#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define DAYS 256
#define CYCLE 7
#define ull unsigned long long

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<ull> breeders(CYCLE);
    queue<ull> new_breeds;
    int current = 0;

    int n; cin >> n;
    for(int i = 0; i < n; ++i) {
        int tmp; cin >> tmp;
        ++breeders[tmp];
    }

    new_breeds.push(0); new_breeds.push(0);
    for(int day = 0; day < DAYS; ++day) {
        new_breeds.push(breeders[current]);
        breeders[current] += new_breeds.front();
        new_breeds.pop();
        current = (current + 1) % CYCLE;
    }

    ull total = 0;
    for(int i = 0; i < CYCLE; ++i) total += breeders[i];
    while(!new_breeds.empty()) {
        total += new_breeds.front();
        new_breeds.pop();
    }
    cout << total << "\n";
    return 0;
}