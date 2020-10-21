#include <iostream>

using namespace std;

struct node{
    int value;
    node *next;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    char c;
    cin >> n;
    node *head = nullptr;
    for (int i = 0; i < n; i++) {
        cin >> c;
        if (c == '+') {
            cin >> m;
            node *temp = new node;
            temp->value = m;
            temp->next = head;
            head = temp;
        } else {
            cout << head->value << endl;
            head = head->next;
        }
    }
    return 0;
}