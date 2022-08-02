#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, prev, ct = 0;
    cin >> n >> prev;
    for(int i = 1; i < n; ++i) {
        int cur; cin >> cur;
        if(cur > prev) ++ct;
        prev = cur;
    }
    cout << ct << "\n";
    return 0;
}