#include <iostream>

using namespace std;

struct node {
    int value;
    node *next;
};

node *head;

void push(int m) {
    node *temp = new node;
    temp->value = m;
    temp->next = head;
    head = temp;
}

int get() {
    if (head != nullptr) {
        return head->value;
    } else {
        return 0;
    }
}

void pop() {
    if (head != nullptr) {
        head = head->next;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
//    freopen("q.in", "r", stdin);
//    freopen("q.out", "w", stdout);
    string s = "";
    head = nullptr;
    while (cin >> s) {
        if (s == "+" || s == "*" || s == "-") {
            int a = get();
            pop();
            int b = get();
            pop();
            if (s == "+") {
                push(a + b);
            }
            if (s == "-") {
                push(b - a);
            }
            if (s == "*") {
                push(a * b);
            }
        } else {
            int l = 0;
            if (s[0] == '-') {
                for (unsigned int i = 1; i < s.length(); i++) {
                    l *= 10;
                    l += s[i] - '0';
                }
                l = -l;
            } else {
                for (unsigned int i = 0; i < s.length(); i++) {
                    l *= 10;
                    l += s[i] - '0';
                }
            }
            push(l);
        }
//        cout << get() << endl;
    }
    cout << get() << endl;
    return 0;
}

