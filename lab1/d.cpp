#include <iostream>

using namespace std;

struct node {
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
    node *tail = nullptr;
    int size = 0;
    for (int i = 0; i < n; i++) {
        cin >> c;
        if (c == '+') {
            cin >> m;
            node *temp = new node;
            temp->value = m;
            if (size == 0) {
                head = temp;
                tail = temp;
            } else {
                tail->next = temp;
                tail = temp;
            }
            size++;
        } else {
            cout << head->value << endl;
            node *cur = head;
            head = head->next;
            delete cur;
            size--;
        }
    }
    return 0;
}