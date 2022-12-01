#include <bits/stdc++.h>

using namespace std;

long long solve(pair<int, int> arr [], int n) {
    long long counter = 0;
    for (int i = 0; i < n; i++) {
        counter += (arr[i].second * 3);
        counter += (arr[i].first + (arr[i].second + 2) % 3) % 3;
        ++counter;
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
    return 0;
}