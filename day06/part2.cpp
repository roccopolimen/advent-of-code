#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int freq[26] = {0};
    int n = s.size();
    for(int i = 0; i < 13; ++i) ++freq[s[i]-'a'];
    for(int i = 13; i < n; ++i) {
        ++freq[s[i]-'a'];
        bool ok = true;
        for(int j = 0; j < 26; ++j) if(freq[j] > 1) ok = false;
        if(ok) {
            cout << (i+1) << '\n';
            break;
        }
        --freq[s[i-13]-'a'];
    }

    return 0;
}