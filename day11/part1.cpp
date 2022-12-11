#include <bits/stdc++.h>

using namespace std;

#define ROUNDS 20

struct Monkey {
    int inspections, divisible_test, divisible_test_pass, divisible_test_fail;
    vector<int> items;
    string operation;

    Monkey() {
        this->inspections = 0;
        this->divisible_test = 0;
        this->divisible_test_pass = 0;
        this->divisible_test_fail = 0;
        this->items = {};
        this->operation = "";
    }

    Monkey(int divisible_test,  // divisible test
           int divisible_test_pass,  // divisible test pass
           int divisible_test_fail,  // divisible test fail
           vector<int> items,  // items
           string operation) {  // operation
        this->inspections = 0;
        this->divisible_test = divisible_test;
        this->divisible_test_pass = divisible_test_pass;
        this->divisible_test_fail = divisible_test_fail;
        this->items = items;
        this->operation = operation;
    }

    void perform_operation(int i) {
        istringstream iss(this->operation);
        string left, op, right;
        iss >> left >> op >> right;
        int left_value, right_value;
        if(left == "old") left_value = this->items[i];
        else left_value = stoi(left);

        if(right == "old") right_value = this->items[i];
        else right_value = stoi(right);

        switch (op[0]) {
            case '+':
                this->items[i] = left_value + right_value;
                break;
            case '-':
                this->items[i] = left_value - right_value;
                break;
            case '*':
                this->items[i] = left_value * right_value;
                break;
            case '/':
                this->items[i] = left_value / right_value;
                break;
        }
    }

    pair<int, int> turn_i(int i) {
        pair<int, int> item_move;
        perform_operation(i);
        this->items[i] /= 3;
        if(!(this->items[i] % this->divisible_test))
            item_move = { this->items[i], this->divisible_test_pass };
        else
            item_move = { this->items[i], this->divisible_test_fail };
        return item_move;
    }

    vector<pair<int, int>> turn() {
        this->inspections += items.size();
        vector<pair<int, int>> item_moves;
        for(int i = 0; i < this->items.size(); i++)
            item_moves.push_back(turn_i(i));
        this->items.clear();
        return item_moves;
    }

};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    cin.ignore();

    vector<Monkey> monkeys(n);
    for(int i = 0; i < n; ++i) {
        string line, item;
        getline(cin, line); // nothing useful

        getline(cin, line); // list of starting items
        vector<int> items;
        istringstream iss(line);
        getline(iss, item, ':');
        while(getline(iss, item, ',')) items.push_back(stoi(item));
        
        getline(cin, line); // operation
        string operation;
        iss = istringstream(line);
        getline(iss, item, '=');
        getline(iss, operation); 

        getline(cin, line); // divisibility test
        int divisible_test, divisible_test_pass, divisible_test_fail;
        iss = istringstream(line);
        getline(iss, item, 'y');
        iss >> divisible_test;

        getline(cin, line); // divisibility test pass
        iss = istringstream(line);
        getline(iss, item, 'y');
        iss >> divisible_test_pass;

        getline(cin, line); // divisibility test fail
        iss = istringstream(line);
        getline(iss, item, 'y');
        iss >> divisible_test_fail;

        monkeys[i] = Monkey(divisible_test, divisible_test_pass, divisible_test_fail, items, operation);
    }

    for(int i = 0; i < ROUNDS; ++i) {
        for(auto &monkey : monkeys) {
            vector<pair<int, int>> item_moves = monkey.turn();
            for(const auto &item_move : item_moves)
                monkeys[item_move.second].items.push_back(item_move.first);
        }
    }

    sort(monkeys.begin(), monkeys.end(), [](const Monkey &a, const Monkey &b) {
        return a.inspections > b.inspections;
    });

    cout << (monkeys[0].inspections * monkeys[1].inspections) << '\n';
    return 0;
}