#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int r, c, ms;
    cin >> r >> c;
    cin.ignore();

    vector<string> crates(r);
    for (int i = 0; i < r; i++) getline(cin, crates[i]);

    vector<stack<char>> stacks(c);
    for(int i = 0; i < crates[r-1].size(); ++i) {
        if(crates[r-1][i] != ' ') {
            int stack_num = crates[r-1][i]-'1';
            for(int j = r-2; j >= 0; --j)
                if(crates[j][i] != ' ')
                    stacks[stack_num].push(crates[j][i]);
        }
    }

    cin >> ms;
    for(int i = 0; i < ms; ++i) {
        int m, f, t;
        cin >> m >> f >> t;
        stack<char> tmp;
        for(int j = 0; j < m; ++j) {
            tmp.push(stacks[f-1].top());
            stacks[f-1].pop();
        }
        for(int j = 0; j < m; ++j) {
            stacks[t-1].push(tmp.top());
            tmp.pop();
        }
    }

    ostringstream oss;
    for(int i = 0; i < c; ++i) oss << stacks[i].top();

    cout << oss.str() << '\n';
    return 0;
}