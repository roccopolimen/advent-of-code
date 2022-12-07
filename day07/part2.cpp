#include <bits/stdc++.h>

using namespace std;

#define AVAILABLE_DISK 70000000
#define SPACE_FOR_UPDATE 30000000

struct dir;
struct file {
    string name;
    int size;
    dir *parent;

    file(string name, int size, dir *parent=nullptr) {
        this->name = name;
        this->size = size;
        this->parent = parent;
    }
};

struct dir {
    string name;
    vector<file *> files;
    vector<dir *> dirs;
    dir *parent;

    dir(string name, dir *parent=nullptr) {
        this->name = name;
        this->parent = parent;
    }
};

int get_size(dir *d) {
    int size = 0;
    for (auto f : d->files) size += f->size;
    for (auto d : d->dirs) size += get_size(d);
    return size;
}

void solve(dir *d, set<int> &sizes, int space_to_free) {
    int sz = get_size(d);
    if(sz >= space_to_free) sizes.insert(sz);
    for (auto d : d->dirs) solve(d, sizes, space_to_free);
}

int main() {

    dir *root = new dir("/"), *cur;
    cur = root;

    string line;
    getline(cin,  line);

    while(true) {
        istringstream iss(line);
        string prompt, command, arg;
        iss >> prompt >> command;

        if(command == "cd") {
            iss >> arg;
            if(arg == "/") cur = root;
            else if(arg == "..") cur = cur->parent;
            else {
                for (auto d : cur->dirs) {
                    if(d->name == arg) {
                        cur = d;
                        goto found1;
                    }
                }
                cur->dirs.push_back(new dir(arg, cur));
                cur = cur->dirs.back();
                found1:;
            }

            if(!getline(cin, line)) break;
        } else if(command == "ls") {
            string ls;
            while(getline(cin, line)) {
                if(line[0] == '$') goto next;
                else {
                    string first, last;
                    istringstream iss(line);
                    iss >> first >> last;
                    if(first == "dir") {
                        for (auto &d : cur->dirs)
                            if(d->name == last)
                                goto found2;
                        cur->dirs.push_back(new dir(last, cur));
                        found2:;
                    } else {
                        for (auto &f : cur->files)
                            if(f->name == last)
                                goto found3;
                        cur->files.push_back(new file(last, stoi(first), cur));
                        found3:;
                    }
                }
            }
            break;
            next:;
        }
    }

    int unused_space = AVAILABLE_DISK - get_size(root);
    int space_to_free = SPACE_FOR_UPDATE - unused_space;
    set<int> sizes;
    solve(root, sizes, space_to_free);
    cout << *sizes.begin() << '\n';
    return 0;
}