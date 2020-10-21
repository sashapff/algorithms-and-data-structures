#include <iostream>

using namespace std;

struct node {
    char value;
    node *next;
};

node *head;

void push(char m) {
    node *temp = new node;
    temp->value = m;
    temp->next = head;
    head = temp;
}

char get() {
    if (head != nullptr) {
        return head->value;
    } else {
        return '_';
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
    string s = "";
    while (cin >> s) {
        bool isCorrect = true;
        head = nullptr;
        for (unsigned int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '[') {
                push(s[i]);
            } else {
                if (s[i] == ')' && get() != '(') {
                    isCorrect = false;
                }
                if (s[i] == ']' && get() != '[') {
                    isCorrect = false;
                }
                pop();
            }
        }
        if (isCorrect && head == nullptr) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}