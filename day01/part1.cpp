#include <iostream>
#include <sstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    string line;
    cin >> n;
    getline(cin, line); // consume newline

    long long best = 0;
    for(int i = 0; i < n; i++) {
        getline(cin, line);
        istringstream iss(line);
        int curr = 0, num;
        while(iss >> num) curr += num;
        if(curr > best) best = curr;
    }

    cout << best << '\n';
    return 0;
}