#include <bits/stdc++.h>

using namespace std;

long long solve(pair<int, int> arr [], int n) {
    long long counter = 0;
    for (int i = 0; i < n; i++) {
        counter += arr[i].second + 1;
        if ((arr[i].second + 2) % 3 == arr[i].first) counter += 6; // 6 points for winning the round
        else if ((arr[i].second + 1) % 3 != arr[i].first) counter += 3; // 3 points for drawing the round
        // 0 points for losing the round
    }
    return counter;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    char f, s;
    cin >> n;
    
    pair<int, int> a[n];
    for (int i = 0; i < n; i++) {
        cin >> f >> s;
        a[i].first = f - 'A';
        a[i].second = s - 'X';
    }

    cout << solve(a, n) << '\n';
}