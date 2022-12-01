#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    int hor=0, dep=0, units;
    for(int i = 0; i < n; ++i) {
        string cmd; cin >> cmd >> units;
        if(cmd == "forward") hor += units;
        else if(cmd == "down") dep += units;
        else if(cmd == "up") dep -= units;
    }
    cout << (hor*dep) << "\n";
    return 0;
}