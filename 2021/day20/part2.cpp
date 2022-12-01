#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define LIGHT '#'
#define DARK  '.'
#define PADDING 2
#define ENHANCEMENTS 50
#define ull unsigned long long

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string enhancement_algo; cin >> enhancement_algo;
    int n; cin >> n;
    vector<vector<bool>> matrix(n);
    bool padder_value = false;
    for(int i = 0; i < n; ++i) {
        string tmp; cin >> tmp;
        matrix[i].resize(tmp.size());
        for(int j = 0, len = tmp.size(); j < len; ++j)
            matrix[i][j] = (tmp[j] == LIGHT);
    }

    auto pad = [&]() {
        for(auto &row : matrix) {
            row.insert(row.begin(), padder_value);
            row.push_back(padder_value);
        }
        vector<bool> new_row(matrix[0].size(), padder_value);
        matrix.insert(matrix.begin(), new_row);
        matrix.push_back(new_row);
    };

    auto enhance = [&]() {
        vector<vector<bool>> tmp_mat(matrix);
        int rows = matrix.size(), cols = matrix[0].size();
        for(int i = 1; i < rows-1; ++i)
            for(int j = 1; j < cols-1; ++j) {
                ostringstream binary;
                binary << matrix[i-1][j-1];
                binary << matrix[i-1][j];
                binary << matrix[i-1][j+1];
                binary << matrix[i][j-1];
                binary << matrix[i][j];
                binary << matrix[i][j+1];
                binary << matrix[i+1][j-1];
                binary << matrix[i+1][j];
                binary << matrix[i+1][j+1];
                int index = stoi(binary.str(), 0, 2);
                tmp_mat[i][j] = (enhancement_algo[index] == LIGHT);
            }
        matrix=tmp_mat;
    };

    auto step = [&]() {
        for(int i = 0; i < PADDING; ++i) pad();
        enhance();
        if(!padder_value && enhancement_algo[0] == LIGHT
        || padder_value && enhancement_algo[enhancement_algo.size()-1] == DARK) {
            padder_value = !padder_value;
            int rows = matrix.size(), cols = matrix[0].size();
            for(int i = 0; i < rows; ++i) {
                matrix[i][0] = padder_value;
                matrix[i][cols-1] = padder_value;
            }
            for(int i = 0; i < cols; ++i) {
                matrix[0][i] = padder_value;
                matrix[rows-1][i] = padder_value;
            }
        }
    };

    for(int i = 0; i < ENHANCEMENTS; ++i) step();
    ull ct = 0;
    int rows = matrix.size(), cols = matrix[0].size();
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            if(matrix[i][j]) ++ct;
    cout << ct << "\n";
    return 0;
}