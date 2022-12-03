#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    
    vector<string> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    long long ans =  0;
    for(int i = 0; i < n; i += 3) {
        vector<vector<bool>> vis(3, vector<bool>(52, false));
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < v[i+j].size(); k++)
                vis[j][v[i+j][k] >= 'a' ? v[i+j][k] - 'a' : v[i+j][k] - 'A' + 26] = true;
        for(int j = 0; j < 52; j++)
            if(vis[0][j] && vis[1][j] && vis[2][j])
                ans += j + 1;
    }

    cout << ans << '\n';
    return 0;
}