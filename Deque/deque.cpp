/**
 *    author:  Hakunaaa
 *    created: 03.05.2026 18:48:45
**/
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Node {
    Node(T val) : val(val) {
        prev = next = nullptr;
    }
    T val;
    Node* prev;
    Node* next;
};

template<typename T>
Node<T>* newNode(T val) {
    Node<T>* node = new Node(val);
    return node;
}

template<typename T>
struct Deque {
    Node<T> *head, *tail; 
    size_t size = 0;
    Deque() { head = tail = nullptr; }
    void push_front(T val) {
        size++;
        Node<T>* node = newNode(val);
        if(head == nullptr) {
            head = node;
            return;
        }
        head->prev = node;
        node->next = head;
        head = node;
    }
    void push_back(T val) {
        size++;
        Node<T>* node = newNode(val);
        if(tail == nullptr) {
            tail = node;
            return;
        }
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    void pop_front() {
        if(head == nullptr) return;
        auto next = head->next;
        delete[] head;
        head = next;
        size--;
    }
    void pop_back() {
        if(tail == nullptr) return;
        auto prev = tail->prev;
        delete[] tail;
        tail = prev;
        size--;
    }
    T front() {
        if(head == nullptr) return T();
        return head->val;
    }
    T back() {
        if(tail == nullptr) return T();
        return tail->val; 
    }
    size_t get_size() { return size; }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    Deque<int> st;
    st.push_back(1);
    st.push_front(10);
    assert(st.get_size() == 2 && st.front() == 10);
    st.pop_front();
    assert(st.get_size() == 1 && st.back() == 1);
    cout << "All good!";
    return 0;
}