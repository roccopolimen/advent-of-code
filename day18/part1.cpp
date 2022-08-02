#include <cmath>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

#define MAX_DEPTH 4

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    struct Node {
        int data; // -1 if not leaf
        Node *left, *right, *parent;
        Node(Node * parent, int data=-1) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = parent;
        }
    };
    Node *snailfish;

    auto make_tree = [&](string &s) {
        Node *root = new Node(nullptr);
        Node *cur = root;
        bool flag = false;
        for(char &c : s) {
            if(!flag) {flag = true; continue;}
            switch(c) {
                case '[':
                    cur = new Node(cur);
                    if(!cur->parent->left) cur->parent->left = cur;
                    else cur->parent->right = cur;
                    break;
                case ',': cur = cur->parent; break;
                case ']': cur = cur->parent; break;
                default:
                    cur = new Node(cur, (c-'0'));
                    if(!cur->parent->left) cur->parent->left = cur;
                    else cur->parent->right = cur;
                    break;
            }
        }
        return root;
    };

    auto add = [&](Node *next) {
        Node *new_root = new Node(nullptr);
        new_root->left = snailfish;
        new_root->right = next;
        snailfish->parent = new_root;
        next->parent = new_root;
        snailfish = new_root;
    };

    auto explode = [&](Node *cur) {
        Node *parent = cur;
        int left = parent->left->data;
        while(cur->parent != nullptr && cur->parent->left == cur)
            cur = cur->parent;
        if(cur->parent != nullptr) {
            cur = cur->parent->left;
            while(cur->data == -1) cur = cur->right;
            cur->data += left;
        }

        int right = parent->right->data;
        cur = parent;
        while(cur->parent != nullptr && cur->parent->right == cur)
            cur = cur->parent;
        if(cur->parent != nullptr) {
            cur = cur->parent->right;
            while(cur->data == -1) cur = cur->left;
            cur->data += right;
        }
        
        delete parent->left;
        delete parent->right;
        parent->left = nullptr;
        parent->right = nullptr;
        parent->data = 0;
    };

    function<bool(Node *,int)> check_explode = [&](Node *cur, int level) {
        if(cur == nullptr) return false;
        if(level == MAX_DEPTH && cur->data == -1) {
            explode(cur);
            return true;
        }
        if(cur->data == -1) {
            bool left = check_explode(cur->left, level+1);
            if(left) return true;
            return check_explode(cur->right, level+1);
        }
        return false;
    };

    auto split = [&](Node *cur) {
        int left = floor(1.0*(cur->data)/2);
        int right = ceil(1.0*(cur->data)/2);
        cur->data = -1;
        cur->left = new Node(cur, left);
        cur->right = new Node(cur, right);
    };

    function<bool(Node *)> check_split = [&](Node *cur) {
        if(cur == nullptr) return false;
        if(cur->data >= 10) {
            split(cur);
            return true;
        }
        if(cur->data == -1) {
            bool left = check_split(cur->left);
            if(left) return true;
            return check_split(cur->right);
        }
        return false;
    };

    auto reduce = [&]() {
        bool exploded = check_explode(snailfish, 0);
        if(exploded) return true;
        return check_split(snailfish);
    };

    function<int(Node *)> magnitude = [&](Node *cur) {
        if(cur == nullptr) return 0;
        if(cur->data != -1) return cur->data;
        return 3*magnitude(cur->left) + 2*magnitude(cur->right);
    };

    int n; cin >> n;
    string tmp; cin >> tmp;
    snailfish = make_tree(tmp);
    for(int i = 1; i < n; ++i) {
        cin >> tmp;
        Node *next = make_tree(tmp);
        add(next);
        while(reduce()) {}
    }
    cout << magnitude(snailfish) << "\n";
    function<void(Node *)> delete_tree = [&](Node *cur) {
        if(!cur) return;
        delete_tree(cur->left);
        delete_tree(cur->right);
        delete cur;
    };
    delete_tree(snailfish);
    return 0;
}