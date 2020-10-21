#include <iostream>

using namespace std;

struct Node {
    int key, height, diff;
    Node *left, *right;

    Node(int key, Node *left, Node *right) :
            key(key), height(1), diff(0), left(left), right(right) {}
};

void setHeight(Node *u) {
    if (u == nullptr) {
        return;
    }
    if (u->left == nullptr && u->right == nullptr) {
        u->height = 1;
        u->diff = 0;
    } else if (u->left == nullptr) {
        u->height = u->right->height + 1;
        u->diff = 0 - u->right->height;
    } else if (u->right == nullptr) {
        u->height = u->left->height + 1;
        u->diff = u->left->height;
    } else {
        u->height = max(u->left->height, u->right->height) + 1;
        u->diff = u->left->height - u->right->height;
    }
}

Node *rotateLeft(Node *u) {
    Node *v = u->right;
    if (v != nullptr) {
        u->right = v->left;
        v->left = u;
        setHeight(u);
        setHeight(v);
    }
    return v;
}

Node *rotateRight(Node *u) {
    Node *v = u->left;
    if (v != nullptr) {
        u->left = v->right;
        v->right = u;
        setHeight(u);
        setHeight(v);
    }
    return v;
}

Node *bigRotateLeft(Node *u) {
    u->right = rotateRight(u->right);
    return rotateLeft(u);
}

Node *bigRotateRight(Node *u) {
    u->left = rotateLeft(u->left);
    return rotateRight(u);
}

Node *changeTree(Node *u) {
    if (u == nullptr) {
        return nullptr;
    }
    if (u->diff == 2 && (u->left->diff == 1 || u->left->diff == 0)) {
        u = rotateRight(u);
    } else if (u->diff == 2 && u->left->diff == -1) {
        u = bigRotateRight(u);
    } else if (u->diff == -2 && (u->right->diff == -1 || u->right->diff == 0)) {
        u = rotateLeft(u);
    } else if (u->diff == -2 && u->right->diff == 1) {
        u = bigRotateLeft(u);
    }
    return u;
}

Node *next(Node *u, int key) {
    Node *cur = nullptr;
    while (u != nullptr) {
        if (u->key > key) {
            cur = u;
            u = u->left;
        } else {
            u = u->right;
        }
    }
    return cur;
}

Node *prev(Node *u, int key) {
    Node *cur = nullptr;
    while (u != nullptr) {
        if (u->key < key) {
            cur = u;
            u = u->right;
        } else {
            u = u->left;
        }
    }
    return cur;
}

Node *insert(Node *u, int key) {
    if (u == nullptr) {
        u = new Node(key, nullptr, nullptr);
    } else {
        if (u->key > key) {
            if (u->left == nullptr) {
                u->left = new Node(key, nullptr, nullptr);
            } else {
                u->left = insert(u->left, key);
            }
        } else if (u->key < key) {
            if (u->right == nullptr) {
                u->right = new Node(key, nullptr, nullptr);
            } else {
                u->right = insert(u->right, key);
            }
        }
    }
    setHeight(u);
    u = changeTree(u);
    return u;
}

Node *dlt(Node *u, int key, Node *root) {
    if (u != nullptr) {
        if (u->key == key) {
            if (u->left == nullptr && u->right == nullptr) {
                u = nullptr;
            } else if (u->right == nullptr) {
                u = u->left;
            } else if (u->left == nullptr) {
                u = u->right;
            } else {
                Node *v = prev(root, u->key);
                u->key = v->key;
                u->left = dlt(u->left, v->key, root);
            }
        } else if (u->key > key) {
            u->left = dlt(u->left, key, root);
        } else {
            u->right = dlt(u->right, key, root);
        }
    }
    setHeight(u);
    u = changeTree(u);
    return u;
}

bool exists(Node *u, int key) {
    if (u == nullptr) {
        return false;
    } else {
        if (u->key > key) {
            return exists(u->left, key);
        } else if (u->key < key) {
            return exists(u->right, key);
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
            tree = dlt(tree, x, tree);
        } else if (s == "exists") {
            cout << (exists(tree, x) ? "true" : "false") << endl;
        } else if (s == "next") {
            Node *u = next(tree, x);
            cout << (u != nullptr ? to_string(u->key) : "none") << endl;
        } else if (s == "prev") {
            Node *u = prev(tree, x);
            cout << (u != nullptr ? to_string(u->key) : "none") << endl;
        }
    }
    return 0;
}
