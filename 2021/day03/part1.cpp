#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, major, len; cin >> n;
    major = (int)(n >> 1);
    string eps = "", gam = "";
    string temp; cin >> temp;

    vector<int> count(temp.begin(), temp.end());
    len = count.size();
    for(int i = 0; i < len; ++i) count[i] -= 48;
    for(int i = 1; i < n; ++i) {
        cin >> temp;
        for(int j = 0; j < len; ++j) count[j] += ((int)temp[j]-48);
    }
    for(int i = 0; i < len; ++i) {
        if(count[i] > major) {
            gam += "1";
            eps += "0";
        } else {
            gam += "0";
            eps += "1";
        }
    }
    cout << stoi(gam, 0, 2) * stoi(eps, 0, 2) << "\n";
    return 0;
}