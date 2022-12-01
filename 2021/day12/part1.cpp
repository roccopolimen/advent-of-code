#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define START "start"
#define END "end"

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    unordered_map<string, bool> lc_visited;
    unordered_map<string, vector<string>> adj;
    vector<pair<string, string>> relations(n);
    unordered_set<string> unique_v;
    vector<string> vertices;
    
    auto little_cave = [&](string cave) {
        return (cave[0] - 'a') >= 0 && (cave[0] - 'a') <= 25;
    };

    for(int i = 0; i < n; ++i) {
        string tmp1, tmp2; cin >> tmp1 >> tmp2;
        relations[i] = make_pair(tmp1, tmp2);
        unique_v.insert(tmp1); unique_v.insert(tmp2);
    }
    copy(unique_v.begin(), unique_v.end(), back_inserter(vertices));
    for(int i = 0, len = vertices.size(); i < len; ++i)
        if(little_cave(vertices[i])) lc_visited[vertices[i]] = false;
    for(int i = 0; i < n; ++i) {
        string v1 = relations[i].first, v2 = relations[i].second;
        adj[v1].push_back(v2); adj[v2].push_back(v1);
    }

    function<int(string)> solver = [&](string current) {
        if(current == END) return 1;
        int ct = 0;
        for(string &neighbor : adj[current]) {
            if(little_cave(neighbor)) {
                if(lc_visited[neighbor]) continue;
                lc_visited[neighbor] = true;
                ct += solver(neighbor); 
                lc_visited[neighbor] = false;
            } else
                ct += solver(neighbor);
        }
        return ct;
    };

    auto solver_wrapper = [&]() {
        lc_visited[START] = true;
        return solver(START);
    };
    cout << solver_wrapper() << "\n";
    return 0;
}