#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    auto add = [&](Node *left, Node *right) {
        Node *new_root = new Node(nullptr);
        new_root->left = left;
        new_root->right = right;
        left->parent = new_root;
        right->parent = new_root;
        return new_root;
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

    auto reduce = [&](Node *cur) {
        bool exploded = check_explode(cur, 0);
        if(exploded) return true;
        return check_split(cur);
    };

    function<int(Node *)> magnitude = [&](Node *cur) {
        if(cur == nullptr) return 0;
        if(cur->data != -1) return cur->data;
        return 3*magnitude(cur->left) + 2*magnitude(cur->right);
    };

    function<void(Node *, ostringstream &)> print_tree_list = [&](Node *cur, ostringstream &oss) {
        if(!cur) return;
        if(cur->data == -1) {
            oss << "[";
            print_tree_list(cur->left, oss);
            oss << ",";
            print_tree_list(cur->right, oss);
            oss << "]";
        } else oss << cur->data;
    };

    function<void(Node *)> delete_tree = [&](Node *cur) {
        if(!cur) return;
        delete_tree(cur->left);
        delete_tree(cur->right);
        delete cur;
    };

    int n; cin >> n;
    vector<Node *> snailfishes(n);
    for(int i = 0; i < n; ++i) {
        string tmp; cin >> tmp;
        snailfishes[i] = make_tree(tmp);
        Node *next = make_tree(tmp);
    }

    int maximum_magnitude = -1;
    ostringstream oss;
    for(int i = 0; i < n; ++i) {
        for(int j = i+1; j < n; ++j) {
            print_tree_list(snailfishes[i], oss);
            string itree_str = oss.str();
            Node *itree = make_tree(itree_str);
            oss.str("");
            print_tree_list(snailfishes[j], oss);
            string jtree_str = oss.str();
            Node *jtree = make_tree(jtree_str);
            oss.str("");
            Node *cur = add(itree, jtree);
            while(reduce(cur)) {}
            maximum_magnitude = max(maximum_magnitude, magnitude(cur));
            delete_tree(cur);
            print_tree_list(snailfishes[i], oss);
            itree_str = oss.str();
            itree = make_tree(itree_str);
            oss.str("");
            print_tree_list(snailfishes[j], oss);
            jtree_str = oss.str();
            jtree = make_tree(jtree_str);
            oss.str("");
            cur = add(jtree, itree);
            while(reduce(cur)) {}
            maximum_magnitude = max(maximum_magnitude, magnitude(cur));
            delete_tree(cur);
        }
    }
    for(auto &node : snailfishes) delete_tree(node);
    cout << maximum_magnitude << "\n";
    return 0;
}