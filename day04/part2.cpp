#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, ct = 0;
    cin >> n;

    for(int i = 0; i < n; ++i) {
        int s1, e1, s2, e2;
        cin >> s1 >> e1 >> s2 >> e2;
        if(s1 <= e2 && s2 <= e1) ++ct;
    }

    cout << ct << '\n';
    return 0;
}