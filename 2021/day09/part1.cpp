#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> mat(n);
    for(int i = 0; i < n; ++i) {
        string tmp; cin >> tmp;
        mat[i].resize(tmp.size());
        for(int j = 0, len = tmp.size(); j < len; ++j) mat[i][j] = tmp[j]-'0';
    }

    auto solver = [&]() {
        int ct = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0, len=mat[i].size(); j < len; ++j) {
                if(j && mat[i][j] >= mat[i][j-1]) continue;
                if(j != (len-1) && mat[i][j] >= mat[i][j+1]) continue;
                if(i && mat[i][j] >= mat[i-1][j]) continue;
                if(i != (n-1) && mat[i][j] >= mat[i+1][j]) continue;
                ct += mat[i][j]+1;
            }
        return ct;
    };
    cout << solver() << "\n";
    return 0;
}