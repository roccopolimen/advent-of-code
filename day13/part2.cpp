#include <bits/stdc++.h>

using namespace std;

struct Node { virtual ~Node() {} };
struct LeafNode : Node { int value; };
struct InternalNode : Node { vector<Node *> children; };

Node* make_node(string &s, int &i) {
    if(s[i] == '[') {
        ++i;
        InternalNode *node = new InternalNode();
        while(i < s.size() && s[i] != ']') node->children.push_back(make_node(s, i));
        ++i;
        return node;
    }
    LeafNode *node = new LeafNode();
    node->value = 0;
    while(s[i] >= '0' && s[i] <= '9')
        node->value = node->value * 10 + (s[i++] - '0');
    ++i;
    return node;
}

// < 0 if left < right, 0 if left == right, > 0 if left > right
int compare(Node *left, Node *right) {
    if(LeafNode *l = dynamic_cast<LeafNode *>(left)) {
        if(LeafNode *r = dynamic_cast<LeafNode *>(right)) return l->value - r->value;
        else { // right is internal
            InternalNode *l2 = new InternalNode();
            l2->children.push_back(l);
            return compare(l2, right);
        }
    } else { // left is internal
        if(LeafNode *r = dynamic_cast<LeafNode *>(right)) {
            InternalNode *r2 = new InternalNode();
            r2->children.push_back(r);
            return compare(left, r2);
        } else { // right is internal
            InternalNode *l = dynamic_cast<InternalNode *>(left);
            InternalNode *r1 = dynamic_cast<InternalNode *>(right);
            int i = 0;
            while(i < l->children.size() && i < r1->children.size()) {
                int c = compare(l->children[i], r1->children[i]);
                if(c != 0) return c;
                ++i;
            }
            return l->children.size() - r1->children.size();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    vector<Node *> roots(2*(n+1));
    for(int i = 0; i < n; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        int i1 = 0, i2 = 0;
        roots[2*i] = make_node(s1, i1);
        roots[2*i+1] = make_node(s2, i2);
    }

    InternalNode *displacer1 = new InternalNode();
    displacer1->children.push_back(new LeafNode());
    dynamic_cast<LeafNode *>(displacer1->children[0])->value = 2;
    InternalNode *displacer2 = new InternalNode();
    displacer2->children.push_back(new LeafNode());
    dynamic_cast<LeafNode *>(displacer2->children[0])->value = 6;

    roots[2*n] = displacer1;
    roots[2*n+1] = displacer2;

    sort(roots.begin(), roots.end(), [](Node *a, Node *b) { return compare(a, b) < 0; });

    int i1 = -1, i2 = -1;
    for(int i = 0; i < roots.size(); ++i) {
        if(roots[i] == displacer1) i1 = i+1;
        if(roots[i] == displacer2) i2 = i+1;
    }

    cout << (i1 * i2) << '\n';
    return 0;
}