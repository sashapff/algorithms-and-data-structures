#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *left, *right, *prev;

    Node(int key, Node *left, Node *right, Node *prev) :
            key(key), left(left), right(right), prev(prev) {}
};

Node *next(Node *u, int key, Node *prev) {
    while (u != nullptr) {
        if (u->key > key) {
            prev = u;
            u = u->left;
        } else {
            u = u->right;
        }
    }
    return prev;
}

Node *prev(Node *u, int key, Node *prev) {
    while (u != nullptr) {
        if (u->key < key) {
            prev = u;
            u = u->right;
        } else {
            u = u->left;
        }
    }
    return prev;
}

Node *insert(Node *u, int key) {
    if (u == nullptr) {
        u = new Node(key, nullptr, nullptr, nullptr);
    } else {
        if (u->key > key) {
            if (u->left == nullptr) {
                u->left = new Node(key, nullptr, nullptr, u);
            } else {
                insert(u->left, key);
            }
        } else if (u->key < key) {
            if (u->right == nullptr) {
                u->right = new Node(key, nullptr, nullptr, u);
            } else {
                insert(u->right, key);
            }
        }
    }
    return u;
}

Node *dlt(Node *u, int key) {
    if (u != nullptr) {
        if (u->key == key) {
            if (u->left == nullptr && u->right == nullptr) {
                u = nullptr;
            } else if (u->right == nullptr) {
                u = u->left;
            } else if (u->left == nullptr) {
                u = u->right;
            } else {
                Node *v = next(u, u->key, nullptr);
                u = dlt(u, v->key);
                u->key = v->key;
            }
        } else if (u->key > key) {
            u->left = dlt(u->left, key);
        } else {
            u->right = dlt(u->right, key);
        }
    }
    return u;
}

bool exists(Node *u, int key) {
    if (u == nullptr) {
        return false;
    } else {
        if (u->key > key) {
            if (u->left == nullptr) {
                return false;
            } else {
                return exists(u->left, key);
            }
        } else if (u->key < key) {
            if (u->right == nullptr) {
                return false;
            } else {
                return exists(u->right, key);
            }
        } else {
            return true;
        }
    }
}

int main() {
    string s;
    int x;
    Node *tree = nullptr;
    while (cin >> s) {
        cin >> x;
        if (s == "insert") {
            tree = insert(tree, x);
        } else if (s == "delete") {
            tree = dlt(tree, x);
        } else if (s == "exists") {
            cout << (exists(tree, x) ? "true" : "false") << endl;
        } else if (s == "next") {
            Node *u = next(tree, x, nullptr);
            cout << (u != nullptr ? to_string(u->key) : "none") << endl;
        } else if (s == "prev") {
            Node *u = prev(tree, x, nullptr);
            cout << (u != nullptr ? to_string(u->key) : "none") << endl;
        }
    }
    return 0;
}
