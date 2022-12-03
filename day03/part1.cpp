#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    
    vector<string> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    long long ans =  0;
    for(const auto &s: v) {
        unordered_set<char> st;
        for(int i = 0, halflen = s.size() / 2; i < halflen; i++)
            st.insert(s[i]);
        for(int i = s.size()/2; i < s.size(); i++)
            if(st.find(s[i]) != st.end()) {
                ans += (s[i] >= 'a' ? s[i] - 'a' + 1 : s[i] - 'A' + 27);
                break;
            }
    }

    cout << ans << '\n';
    return 0;
}