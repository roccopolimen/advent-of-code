#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    queue<int> window;
    int n, a, b, c; cin >> n >> a >> b >> c;
    window.push(a); window.push(b); window.push(c);
    int ct = 0;
    for(int i = 3; i < n; ++i) {
        int cur; cin >> cur;
        if(cur > window.front()) ++ct;
        window.pop(); window.push(cur);
    }
    cout << ct << "\n";
    return 0;
}