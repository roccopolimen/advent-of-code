#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    string line;
    cin >> n;
    getline(cin, line); // consume newline

    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 0; i < n; i++) {
        getline(cin, line);
        istringstream iss(line);
        int curr = 0, num;
        while(iss >> num) curr += num;
        pq.push(curr);
        if(pq.size() > 3) pq.pop();
    }

    // sum the elements in the priority queue
    long long best = 0;
    while(!pq.empty()) {
        best += pq.top();
        pq.pop();
    }
    cout << best << '\n';
    return 0;
}