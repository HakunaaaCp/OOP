#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class Node {
private:
    T val;
    Node* prev;
public:
    Node(T val) : val(val), prev(nullptr) {}
    void set(Node* prev) {
        this->prev = prev;
    } 
    T get_val() { return val; }
    Node* get_prev() { return prev; }
};

template <typename T>
class Stack {
private:
    Node<T>* tail;
public:
    Stack() : tail(nullptr) {}  
    void push(T val) {
        Node<T>* ptr = new Node<T>(val);
        ptr->set(tail);
        tail = ptr;
    }
    void pop() {
        if(tail == nullptr) return;
        Node<T>* tmp = tail;
        tail = tail->get_prev();
        delete tmp;
    }
    T top() {
        return tail->get_val();
    }
    bool empty() { return tail == nullptr; }
};

int main() {
    stack<int> st1;
    Stack<int> st2;
    int T = 1000, cnt = 0, cor = 0;
    while(T--) {
        int op = rand() % 3;
        // 0 = push, 1 = pop, 2 = top; 
        if(!op) {
            int t = rand() % 1000;
            st1.push(t), st2.push(t);
        } else if(op == 1) {
            if(!st1.empty()) st1.pop(), st2.pop();
        } else {
            cnt++;
            cor += (st1.empty() && st2.empty()) || (st1.top() == st2.top());
        }
    }
    cout << cor << " is correct out of " << cnt;
    return 0;
}